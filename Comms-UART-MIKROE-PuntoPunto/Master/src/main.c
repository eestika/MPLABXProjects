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

#define USER_PORT PORTEbits.RE6
#define USER_TRIS TRISEbits.TRISE6

void DelayMs(unsigned int ms) {
    volatile int i;
    while(ms--) {
        for(i = 0; i < 40000; i++);
    }
}

int main(void) {
    SYS_Initialize(NULL);

    USER_TRIS = 1;  // RE6 come input
    uint8_t prevState = 1;

    while (1) {
        uint8_t currState = USER_PORT;
        if (currState != prevState) {
            while (UART5_WriteIsBusy());
            UART5_Write(&currState, 1);
            prevState = currState;
        }
        DelayMs(10);
    }

    return (EXIT_FAILURE);
}



/*******************************************************************************
 End of File
*/

