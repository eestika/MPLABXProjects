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
#include "pwm.h"
#include "adc_control.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************



int main(void)
{
    SYS_Initialize(NULL);

    PWM_Init();       // avvia TMR2+OC1 e mette subito 1000 us
    ADCCTL_Init();    // abilita ADC e seleziona AN4

    // --- Arming ESC: resta a 1000 us per ~1s ---
    for (volatile uint32_t d = 0; d < 4000000u; ++d) { __asm__ volatile("nop"); }

    // Prima lettura: inizializza il filtro con un valore "reale"
    uint16_t first = ADCCTL_ReadRaw();     // 0..1023
    uint16_t filt  = first;

    while (1)
    {
        uint16_t adc = ADCCTL_ReadRaw();

        // filtro morbido: 80% vecchio + 20% nuovo
        filt = ADCCTL_FilterEMA(filt, adc, 4, 5);

        // (opzionale) deadband anti-rumore attorno allo zero
        if (filt < 10) filt = 0;

        uint16_t us = PWM_MapAdcToUS(filt);  // 1000..2000 us
        PWM_SetUS(us);
    }
}




/*******************************************************************************
 End of File
*/

