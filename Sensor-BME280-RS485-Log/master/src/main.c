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

#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <sys/attribs.h>
#include "definitions.h"

#define SYS_CLK_FREQ 80000000UL
#define BME280_ADDRESS 0x76

// Registro dati misurazioni (da 0xF7 per 8 byte)
static const uint8_t BME280_DATA_START = 0xF7;
// Registro dati di calibrazione (da 0x88 per 26 byte)
static const uint8_t BME280_CALIB_START = 0x88;

uint8_t bme_data[8];
uint8_t calib_data[26];

void DelayMs(unsigned int msec)
{
    uint32_t tWait = (SYS_CLK_FREQ / 2000) * msec;
    uint32_t tStart = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - tStart) < tWait);
}

bool bme280_init()
{
    bool success = true;
    uint8_t ctrl_hum[2] = {0xF2, 0x01};  // Humidity oversampling x1
    uint8_t ctrl_meas[2] = {0xF4, 0x27}; // Temp/Press oversampling x1, mode = normal
    uint8_t config[2] = {0xF5, 0xA0};    // Standby time 1000ms, filter off

    success &= I2C2_Write(BME280_ADDRESS, ctrl_hum, 2);
    while (I2C2_IsBusy());
    DelayMs(2);

    success &= I2C2_Write(BME280_ADDRESS, ctrl_meas, 2);
    while (I2C2_IsBusy());
    DelayMs(2);

    success &= I2C2_Write(BME280_ADDRESS, config, 2);
    while (I2C2_IsBusy());
    DelayMs(2);

    return success;
}

bool read_bme280_raw_data()
{
    // Lettura dei dati di misura
    if (!I2C2_WriteRead(BME280_ADDRESS, (uint8_t*)&BME280_DATA_START, 1, bme_data, 8))
        return false;
    while (I2C2_IsBusy());

    // Lettura dei dati di calibrazione
    if (!I2C2_WriteRead(BME280_ADDRESS, (uint8_t*)&BME280_CALIB_START, 1, calib_data, 26))
        return false;
    while (I2C2_IsBusy());

    return true;
}

void send_uart_data()
{
    // Invia 8 byte di dati misurazione + 26 byte di calibrazione
    UART5_Write(bme_data, sizeof(bme_data));
    while (UART5_WriteIsBusy());

    UART5_Write(calib_data, sizeof(calib_data));
    while (UART5_WriteIsBusy());
}

int main(void)
{
    SYS_Initialize(NULL);

    if (!bme280_init()) {
        while (1); // errore inizializzazione sensore
    }

    TRISESET = (1 << 6); // RE6 come input (USER BUTTON)
    bool statoPrecedente = 1;

    while (1)
    {
        bool statoCorrente = (PORTE & (1 << 6)) != 0; // Legge lo stato RE6

        if (statoPrecedente == 1 && statoCorrente == 0) // Pressione tasto USER
        {
            if (read_bme280_raw_data())
            {
                send_uart_data();
            }
            DelayMs(300); // debounce
        }

        statoPrecedente = statoCorrente;
    }

    return 0;
}


/*******************************************************************************
 End of File
*/

