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
#define USER_BUTTON_PORT   PORTEbits.RE6
#define DEBOUNCE_DELAY_MS  200

typedef struct {
    uint8_t statoLED;
    uint8_t comandoID;
} LedCommand;

void DelayMs(unsigned int ms)
{
    uint32_t tStart = _CP0_GET_COUNT();
    uint32_t tWait = (SYS_CLK_FREQ / 2000) * ms;
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL);

    bool stato = false;

    while (1)
    {
        if (USER_BUTTON_PORT == 0)  // pulsante premuto
        {
            LedCommand cmd;
            cmd.statoLED = stato ? 1 : 0;
            cmd.comandoID = 0xAA;  // codice identificativo fisso

            UART1_Write(&cmd, sizeof(LedCommand));  // invia la struct

            stato = !stato;

            DelayMs(DEBOUNCE_DELAY_MS);
            while (USER_BUTTON_PORT == 0);
            DelayMs(DEBOUNCE_DELAY_MS);
        }
    }

    return 0;
}





/*******************************************************************************
 End of File
*/

