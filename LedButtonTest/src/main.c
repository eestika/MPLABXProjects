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



// Definiamo maschere per leggibilità
#define LED_RE3 (1 << 3)
#define BUTTON_RE6 (1 << 6)

int main(void)
{
    SYS_Initialize(NULL);  // Inizializza periferiche e clock

    TRISECLR = LED_RE3;    // Imposta RE3 come OUTPUT ? TRIS = 0
    TRISESET = BUTTON_RE6; // Imposta RE6 come INPUT ? TRIS = 1

    LATESET = LED_RE3;     // All'inizio LED spento ? RE3 HIGH (sinking)

    while (1)
    {
        if (!(PORTE & BUTTON_RE6))   // Se RE6 è LOW (pulsante premuto)
        {
            LATECLR = LED_RE3;       // LED acceso (RE3 LOW)
        }
        else                         // Se RE6 è HIGH (pulsante rilasciato)
        {
            LATESET = LED_RE3;       // LED spento (RE3 HIGH)
        }
    }

    return 0;
}
 


/*******************************************************************************
 End of File
*/

