/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// Frequenza del clock di sistema (definita anche in MCC di solito)
#define SYS_CLK_FREQ 80000000UL

// Definizione per il controllo manuale del Chip Select su RF12
#define CS_LAT LATFbits.LATF12
#define CS_TRIS TRISFbits.TRISF12

// Funzione di delay in millisecondi usando Core Timer
void delay_ms(unsigned int ms) {
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < (ms * (SYS_CLK_FREQ / 2000)));
}

// Inizializza il pin CS
void MAX31855_Init(void) {
    CS_TRIS = 0;  // Imposta RF12 come output
    CS_LAT = 1;   // Deselect iniziale del sensore (CS alto)
}

// Funzione per leggere la temperatura dal MAX31855
int16_t Read_Thermocouple_Temperature(void) {
    uint8_t dummyTx[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t rxData[4];

    CS_LAT = 0;
    delay_ms(1);

    SPI4_WriteRead(dummyTx, 4, rxData, 4);

    CS_LAT = 1;

    // Test di debug: ritorna il primo byte ricevuto per vedere se SPI risponde
    return rxData[0];
}

int main(void) {
    SYS_Initialize(NULL); // richiede un parametro!
    MAX31855_Init();

    uint8_t dummyTx[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t rxData[4];

    CS_LAT = 0;
    delay_ms(1);
    SPI4_WriteRead(dummyTx, 4, rxData, 4);
    CS_LAT = 1;

    // ? BREAKPOINT QUI
    volatile uint8_t b0 = rxData[0];
    volatile uint8_t b1 = rxData[1];
    volatile uint8_t b2 = rxData[2];
    volatile uint8_t b3 = rxData[3];
    
    // Evita warning "unused variable"
    (void)b0;
    (void)b1;
    (void)b2;
    (void)b3;
    
    while (1);
    return 0;
}




/*******************************************************************************
 End of File
*/

