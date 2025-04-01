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


// Delay software temporaneo
void delay_software(unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main(void)

{
    SYS_Initialize(NULL); // Inizializza clock, PPS, UART1, ecc.

    uint8_t message[] = "Hello UART!\r\n";

    while (1)
    {
        UART1_Write(message, sizeof(message));
        delay_software(100); // Circa 1 secondo di ritardo
    }
}



/*******************************************************************************
 End of File
*/

