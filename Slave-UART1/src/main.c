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


void spegniTuttiLED(void)
{
    LATESET = 0x0008; // spegne RE3 (modalità sinking ? 1 = spento)
}

void accendiLED(char comando)
{
    if (comando == 0)    // Se premuto (active low), accendi
        LATECLR = 0x0008;
    else                 // Se rilasciato, spegni
        LATESET = 0x0008;
}

int main(void)
{
    SYS_Initialize(NULL);
    spegniTuttiLED();

    while (true)
    {
        if (U1STA & _U1STA_URXDA_MASK)  // Se dati disponibili
        {
            char comando = U1RXREG;
            accendiLED(comando);
        }
    }

    return 0;
}





/*******************************************************************************
 End of File
*/

