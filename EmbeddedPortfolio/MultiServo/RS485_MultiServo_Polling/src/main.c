/*******************************************************************************
  Main Source File

  Company:
 Perez Dynamics OU

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
#include "rs485_rx.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

/* Nota:
 * La PLIB generata disabilita gli interrupt di UART5.
 * Usiamo quindi un semplice polling dei registri U5STA/U5RXREG.
 */

int main(void)
{
    SYS_Initialize(NULL);

    // Config PWM servo (Timer2 + OC1 già configurati via MCC)
    const ServoPwmConfig_t cfg = {
        .min_us    = 1000,   // 1.0 ms
        .mid_us    = 1500,   // 1.5 ms
        .max_us    = 2000,   // 2.0 ms
        .period_us = 20000   // 20 ms (50 Hz)
    };
    ServoPWM_Init(&cfg);

    // Parser RS485: parti dal centro
    RS485RX_Init(90);

    // Loop principale: polling RX su UART5
    while (true)
    {
        // Se c'è almeno un byte nella FIFO RX, leggilo e passalo al parser
        while ( (U5STA & _U5STA_URXDA_MASK) != 0U )
        {
            uint8_t b = (uint8_t)U5RXREG;
            RS485RX_OnByte(b);
        }

        // Qui puoi aggiungere eventuale housekeeping non bloccante
        // (es. watchdog kick, LED heartbeat, ecc.)
    }

    // Mai raggiunto
    // return 0;
}

/*******************************************************************************
 End of File
*/

