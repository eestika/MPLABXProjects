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




void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < ms * 2000; i++)
    {
        __asm__ volatile("nop");
    }
}

int main(void)
{
    SYS_Initialize(NULL);     // Init MCC, TMR2 e OCMP1

    OCMP1_Enable();           // Abilita modulo OC1
    TMR2_Start();             // Avvia Timer2

    while (1)
    {
        // Posizione 0° (~1ms HIGH)
        OCMP1_CompareSecondaryValueSet(1250); // 1ms = 1250 @1.25MHz
        delay_ms(1000);

        // Posizione 90° (~1.5ms HIGH)
        OCMP1_CompareSecondaryValueSet(1875); // 1.5ms = 1875 @1.25MHz
        delay_ms(1000);

        // Posizione 180° (~2ms HIGH)
        OCMP1_CompareSecondaryValueSet(2500); // 2ms = 2500 @1.25MHz
        delay_ms(1000);
    }

    return (EXIT_FAILURE); // Mai raggiunto
}



/*******************************************************************************
 End of File
*/

