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

#define SYS_CLK_FREQ 80000000  // 80 MHz clock di sistema
#define DELAY_MS(ms) DelayMs(ms)

void DelayMs(unsigned int msec)
{
    uint32_t tWait = (SYS_CLK_FREQ / 2000) * msec;
    uint32_t tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL); // Inizializzazione tramite MCC

    char comando;
    char flush;

    // Svuota eventuali caratteri residui in RX
    while (UART5_Read(&flush, 1)) { }

    while (1)
    {
        if (UART5_Read(&comando, 1))
        {
            if (comando == '1')
            {
                // LED ON (in modalità sinking ? porta a 0)
                LATECLR = (1 << 3);
            }
            else if (comando == '0')
            {
                // LED OFF (porta a 1)
                LATESET = (1 << 3);
            }

            DELAY_MS(200); // debounce
        }
    }

    return 0;
}

/*******************************************************************************
 End of File
*/

