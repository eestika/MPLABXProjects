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

#define SYS_CLK_FREQ 80000000UL

void DelayMs(unsigned int ms)
{
    unsigned long tWait = (SYS_CLK_FREQ / 2000) * ms;
    unsigned long tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL);  // Inizializza il sistema e UART5

    while (1)
    {
        const char comando = '1';

        // Attendi che la UART sia libera e invia il byte
        while (UART5_WriteIsBusy());
        UART5_Write((void*)&comando, 1);

        DelayMs(2000);  // Aspetta 2 secondi prima di inviare di nuovo
    }

    return (EXIT_FAILURE); // In teoria non viene mai raggiunto
}





/*******************************************************************************
 End of File
*/

