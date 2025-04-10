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

#define SYS_CLK_FREQ 80000000

void DelayMs(unsigned int msec) {
    unsigned long int tWait, tStart;
    tWait = (SYS_CLK_FREQ / 2000) * msec;
    tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL);

    while (1)
    {
        const char comando = '1';
        while (UART1_WriteIsBusy());
        UART1_Write((void*)&comando, 1);

        DelayMs(2000);  // 2 secondi
    }

    return (EXIT_FAILURE);
}


/*******************************************************************************
 End of File
*/

