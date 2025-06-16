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


void spegniTuttiLED(void) {
    LATESET = 0x000F; // Spegne i LED (RE0-RE3)
}

void accendiLED(void) {
    LATECLR = (1 << 3); // Accende solo RE3
}

int main(void) {
    SYS_Initialize(NULL);
    spegniTuttiLED();

    while (1) {
        if (U5STA & _U5STA_URXDA_MASK) {
            char comando = U5RXREG;
            if (comando == 0)
                accendiLED();
            else
                spegniTuttiLED();
        }
    }

    return (EXIT_FAILURE);
}



/*******************************************************************************
 End of File
*/

