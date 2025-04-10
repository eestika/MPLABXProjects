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

#define LED_RE3     (1 << 3)
#define BUTTON_RE6  (1 << 6)

void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms * 1000; i++) {
        asm volatile("nop");  // istruzione vuota per rallentare (NON precisissima)
    }
}

int main(void)
{
    SYS_Initialize(NULL);

    TRISECLR = LED_RE3;    // RE3 = output
    TRISESET = BUTTON_RE6; // RE6 = input

    LATESET = LED_RE3;     // LED spento inizialmente

    bool previous_state = 1;  // Tiene traccia del vecchio stato (rilasciato)

    while (1)
    {
        bool current = PORTE & BUTTON_RE6;  // legge stato RE6

        if (previous_state && !current)  // transizione: HIGH ? LOW (premuto)
        {
            delay_ms(30);  // debounce

            if (!(PORTE & BUTTON_RE6))  // è ancora premuto?
            {
                LATEINV = LED_RE3;  // inverti stato LED
            }
        }

        previous_state = current;  // aggiorna stato per il prossimo ciclo
    }

    return 0;
}



/*******************************************************************************
 End of File
*/

