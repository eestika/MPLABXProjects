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
#include <xc.h>


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_FREQ 80000000
#define DELAY_MS(ms) DelayMs(ms)

void DelayMs(unsigned int msec)
{
    uint32_t tWait = (SYS_CLK_FREQ / 2000) * msec;
    uint32_t tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL);

    // Assicura che il LED USER sia configurato come input (RE6)
    TRISESET = (1 << 6); // RE6 come input

    bool statoPrecedente = 1;

    while (1)
    {
        bool statoCorrente = (PORTE & (1 << 6)) != 0; // Legge stato del pulsante

        if (!statoCorrente && statoPrecedente)
        {
            // Rilevato fronte di discesa ? pulsante premuto

            static bool statoLed = false;
            statoLed = !statoLed;

            char comando = statoLed ? '1' : '0';
            UART5_Write(&comando, 1);

            DELAY_MS(200); // debounce
        }

        statoPrecedente = statoCorrente;
    }

    return 0;
}


/*******************************************************************************
 End of File
*/

