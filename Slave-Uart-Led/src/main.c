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

// Spegne tutti i LED (HIGH = spento in logica sinking)
void spegniTuttiLED(void)
{
    LATESET = 0x000F; // Setta a 1 i bit da 0 a 3 ? LED spenti
}

// Accende il LED richiesto dal comando
void accendiLED(char comando)
{
    spegniTuttiLED();
    switch (comando)
    {
        case '1': LATECLR = (1 << 0); break;
        case '2': LATECLR = (1 << 1); break;
        case '3': LATECLR = (1 << 2); break;
        case '4': LATECLR = (1 << 3); break;
        default: break;
    }

    // Ritardo per vedere il lampeggio
    for (volatile int i = 0; i < 1000000; i++);
    spegniTuttiLED();
}

int main(void)
{
    SYS_Initialize(NULL);
    spegniTuttiLED();

    while (true)
    {
        if (U1STA & _U1STA_URXDA_MASK)
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

