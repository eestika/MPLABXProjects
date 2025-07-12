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

// Main Bme280 Uart (attuale codice valido da flashare su PIC2)

#define SYS_CLK_FREQ 80000000UL

void DelayMs(unsigned int msec)
{
    uint32_t tWait = (SYS_CLK_FREQ / 2000) * msec;
    uint32_t tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

int main(void)
{
    SYS_Initialize(NULL);

    // Stato iniziale: LED spenti
    LATESET = (1 << 1); // LED rosso OFF (RE1)
    LATESET = (1 << 3); // LED verde OFF (RE3)

    uint8_t buffer[34];

    while (1)
    {
        if (!UART5_ReadIsBusy())
        {
            if (UART5_Read(buffer, sizeof(buffer)))
            {
                while (UART5_ReadIsBusy()); // Aspetta fine ricezione

                // Estrai dati temperatura grezzi (corretto offset)
                uint32_t adc_T = ((uint32_t)buffer[3] << 12) | ((uint32_t)buffer[4] << 4) | (buffer[5] >> 4);

                // Calibrazione (corretto offset)
                uint16_t dig_T1 = (uint16_t)(buffer[8] | (buffer[9] << 8));
                int16_t dig_T2  = (int16_t)(buffer[10] | (buffer[11] << 8));
                int16_t dig_T3  = (int16_t)(buffer[12] | (buffer[13] << 8));

                int32_t var1, var2, t_fine, T;
                var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
                var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
                t_fine = var1 + var2;
                T = (t_fine * 5 + 128) >> 8;

                float temperatura = T / 100.0f;

                if (temperatura < 25.0f)
                {
                    LATECLR = (1 << 3);   // Verde ON
                    LATESET = (1 << 1);   // Rosso OFF
                }
                else
                {
                    LATECLR = (1 << 1);   // Rosso ON
                    LATESET = (1 << 3);   // Verde OFF
                }

                DelayMs(1000); // visibilità LED

                // Spegni entrambi i LED dopo 1 secondo
                LATESET = (1 << 1); // Rosso OFF
                LATESET = (1 << 3); // Verde OFF
            }
        }
    }

    return 0;
}

/*******************************************************************************
 End of File
*/

