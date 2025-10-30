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
#include "servo_pwm.h"
#include "delay_ms.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    SYS_Initialize(NULL);

    const ServoPwmConfig_t cfg = {
        .min_us    = 1000,   // calibra se il tuo MG90S richiede correzioni
        .mid_us    = 1500,
        .max_us    = 2000,
        .period_us = 20000
    };

    ServoPWM_Init(&cfg);

    // Sweep dimostrativo
    while (1) {
        for (uint8_t a = 0; a <= 180; a += 10) {
            ServoPWM_SetAngleDeg(a);
            DelayMs(500);
        }
        for (int a = 180; a >= 0; a -= 10) {
            ServoPWM_SetAngleDeg((uint8_t)a);
            DelayMs(500);
        }
    }
    // return 0;  // mai raggiunto
}


/*******************************************************************************
 End of File
*/

