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

#define SYS_CLK_FREQ 80000000

void DelayMs(unsigned int ms) {
    unsigned long int tWait = (SYS_CLK_FREQ / 2000) * ms;
    unsigned long int tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void) {
    SYS_Initialize(NULL);

    USER_TRIS = 1;  // Imposta RE6 come input

    DelayMs(1000);  // Aspetta 1 secondo per stabilizzare il sistema

    uint8_t prevState = USER_PORT;  // Legge lo stato iniziale del pulsante

    while (1) {
        uint8_t currState = USER_PORT;

        if (currState != prevState) {
            while (UART1_WriteIsBusy());
            UART1_Write(&currState, 1);
            prevState = currState;
        }

        DelayMs(10);  // Polling lento per evitare invii multipli
    }

    return 0;
}



/*******************************************************************************
 End of File
*/

