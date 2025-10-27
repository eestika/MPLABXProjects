// *****************************************************************************
// PIC2 ? RS485 ONLY (ricezione 3 float: T, P, RH) + LED con isteresi
// *****************************************************************************

#include "definitions.h"   // MCC: SYSTEM_Initialize, UART5, GPIO init
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "sensordata.h"    // struct { float temperature, pressure, humidity; }
#include "rs485_rx.h"      // bool RS485_ReadExact(uint8_t* dst, size_t n)

// Pin (sinking): 0 = LED ON, 1 = LED OFF
#define LED_RED_MASK    (1u << 1)   // RE1
#define LED_GREEN_MASK  (1u << 3)   // RE3

// Soglie con isteresi
#ifndef TEMP_HIGH_C
#define TEMP_HIGH_C  27.0f
#endif
#ifndef TEMP_LOW_C
#define TEMP_LOW_C   26.0f
#endif

static void LED_Init(void)
{
    // Assicurati che siano output e spenti (HIGH) all'avvio
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE3 = 0;
    LATESET = (LED_RED_MASK | LED_GREEN_MASK);   // OFF (sinking)
}

static void LED_Red_On(void)    { LATECLR = LED_RED_MASK; }
static void LED_Red_Off(void)   { LATESET = LED_RED_MASK; }
static void LED_Green_On(void)  { LATECLR = LED_GREEN_MASK; }
static void LED_Green_Off(void) { LATESET = LED_GREEN_MASK; }

int main(void)
{
    SYS_Initialize(NULL);
    LED_Init();

    uint8_t buf[12];
    SensorData_t s;
    bool hot_state = false;   // true = sopra soglia (rosso), false = sotto (verde)

    for (;;)
    {
        // Ricevi esattamente 12 byte dal Master (3 float IEEE754 LE)
        RS485_ReadExact(buf, sizeof buf);

        // Decodifica sicura
        memcpy(&s.temperature, &buf[0], 4);
        memcpy(&s.pressure,    &buf[4], 4);
        memcpy(&s.humidity,    &buf[8], 4);

        // Plausibility check (coerente con fix BME280 lato Master)
        bool ok = (s.humidity    >= 0.0f   && s.humidity    <= 100.0f) &&
                  (s.pressure    >= 800.0f && s.pressure    <= 1100.0f) &&
                  (s.temperature >  -40.0f && s.temperature <   85.0f);

        if (!ok) {
            // Dati spuri ? spegni entrambi i LED e torna ?freddo?
            LED_Red_Off();
            LED_Green_Off();
            hot_state = false;
            continue;
        }

        // Isteresi sulla temperatura
        if (!hot_state && s.temperature >= TEMP_HIGH_C) {
            hot_state = true;
            LED_Red_On();
            LED_Green_Off();
        } else if (hot_state && s.temperature <= TEMP_LOW_C) {
            hot_state = false;
            LED_Red_Off();
            LED_Green_On();
        }
        // In mezzo alle soglie mantiene lo stato (niente sfarfallio)
    }
    // return EXIT_FAILURE; // non si arriva mai qui
}


