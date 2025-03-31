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


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


uint32_t luce = 0;

void readLightSensor(void)
{
    // Seleziona AN3 come ingresso positivo, VREFL come negativo (default)
    AD1CHSbits.CH0SA = 3; // AN3
    AD1CHSbits.CH0NA = 0; // VREF- (default)

    // Avvia campionamento
    ADC_SamplingStart();

    // Avvia conversione
    ADC_ConversionStart();

    // Attendi che sia pronto
    while (!ADC_ResultIsReady());

    // Leggi il valore ADC
    luce = ADC_ResultGet(ADC_RESULT_BUFFER_0);
}

int main(void)
{
    SYS_Initialize(NULL);  // Inizializza tutti i moduli configurati da MCC

    while (true)
    {
        readLightSensor();

        // Qui puoi usare il valore "luce", ad esempio per accendere LED o inviarlo via UART
        // Per ora lo manteniamo solo in memoria per test

        for (volatile int i = 0; i < 100000; i++); // pausa grezza per evitare letture troppo ravvicinate
    }

    return 0;
}


