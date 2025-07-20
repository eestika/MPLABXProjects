// *****************************************************************************
// Main Source File per PIC2
//
// Company:
//     Perez Dynamics OÜ
//
// File Name:
//     main.c
//
// Summary:
//     Ricezione dati da CAN (e fallback RS485), valutazione temperatura e accensione LED
//
// Description:
//     PIC2 si mette in ascolto sul bus CAN. Se riceve un valore valido di temperatura,
//     valuta se accendere LED verde o rosso. In caso di errore sul CAN, attiva backup
//     su UART5 (RS485) per ricevere anche pressione e umidità e usa LED giallo per segnalare errore CAN.
// *****************************************************************************

#include "definitions.h"
#include "utils.h"
#include "sensordata.h"
#include "logica.h"
#include "rs485_rx.h"

int main(void)
{
    SYS_Initialize(NULL);

    // Spegni LED iniziali
    LATESET = (1 << 1);  // RE1 = rosso OFF
    LATESET = (1 << 3);  // RE3 = verde OFF

    SensorData_t data;

    while (1)
    {
        if (RS485_ReceiveSensorData(&data))
        {
            LOGIC_HandleTemperature(data.temperature);

            DelayMs(1000); // Tempo visibile
            LATESET = (1 << 1);  // rosso OFF
            LATESET = (1 << 3);  // verde OFF
        }
    }

    return 0;
}
