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

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "definitions.h"

#define OLED_ADDR  0x3C
#define OLED_CMD   0x00
#define OLED_DATA  0x40

typedef struct {
    uint8_t statoLED;   // 1 per LED ON, 0 per LED OFF
    uint8_t comandoID;  // ID comando
} LedCommand;

// Font minimalista per lettere usate in "LED ON" e "LED OFF"
const uint8_t font_L[] = {0x7F, 0x40, 0x40, 0x40, 0x40}; // L
const uint8_t font_E[] = {0x7F, 0x49, 0x49, 0x49, 0x41}; // E
const uint8_t font_D[] = {0x7F, 0x41, 0x41, 0x22, 0x1C}; // D
const uint8_t font_O[] = {0x3E, 0x41, 0x41, 0x41, 0x3E}; // O
const uint8_t font_F[] = {0x7F, 0x09, 0x09, 0x09, 0x01}; // F
const uint8_t font_N[] = {0x7F, 0x02, 0x04, 0x08, 0x7F}; // N
const uint8_t font_space[] = {0x00, 0x00, 0x00, 0x00, 0x00}; // spazio

void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < (ms * 5000); i++) {
        __asm("nop");
    }
}

bool OLED_Command(uint8_t command) {
    uint8_t writeBuffer[2] = {OLED_CMD, command};
    while(I2C2_IsBusy());
    return I2C2_Write(OLED_ADDR, writeBuffer, 2);
}

bool OLED_Data(uint8_t data) {
    uint8_t writeBuffer[2] = {OLED_DATA, data};
    while(I2C2_IsBusy());
    return I2C2_Write(OLED_ADDR, writeBuffer, 2);
}

bool OLED_Init(void) {
    delay_ms(100);
    if (!OLED_Command(0xAE)) return false;
    if (!OLED_Command(0xD5)) return false;
    if (!OLED_Command(0x80)) return false;
    if (!OLED_Command(0xA8)) return false;
    if (!OLED_Command(0x3F)) return false;
    if (!OLED_Command(0xD3)) return false;
    if (!OLED_Command(0x00)) return false;
    if (!OLED_Command(0x40)) return false;
    if (!OLED_Command(0x8D)) return false;
    if (!OLED_Command(0x14)) return false;
    if (!OLED_Command(0x20)) return false;
    if (!OLED_Command(0x00)) return false;
    if (!OLED_Command(0xA1)) return false;
    if (!OLED_Command(0xC8)) return false;
    if (!OLED_Command(0xDA)) return false;
    if (!OLED_Command(0x12)) return false;
    if (!OLED_Command(0x81)) return false;
    if (!OLED_Command(0x5F)) return false;
    if (!OLED_Command(0xD9)) return false;
    if (!OLED_Command(0xF1)) return false;
    if (!OLED_Command(0xDB)) return false;
    if (!OLED_Command(0x40)) return false;
    if (!OLED_Command(0xA4)) return false;
    if (!OLED_Command(0xA6)) return false;
    delay_ms(100);
    return OLED_Command(0xAF);
}

void OLED_Clear(void) {
    for (uint8_t page = 0; page < 8; page++) {
        OLED_Command(0xB0 | page);
        OLED_Command(0x00);
        OLED_Command(0x10);
        for (uint8_t col = 0; col < 128; col++) {
            OLED_Data(0x00);  // Cancella i pixel
        }
    }
}

void OLED_DrawChar(uint8_t page, uint8_t col, const uint8_t *character) {
    OLED_Command(0xB0 | page);  // Seleziona la pagina
    OLED_Command(col & 0x0F);    // Colonna bassa
    OLED_Command(0x10 | (col >> 4)); // Colonna alta
    for (uint8_t i = 0; i < 5; i++) {
        OLED_Data(character[i]);
    }
    OLED_Data(0x00);  // Spazio tra i caratteri
}

const uint8_t* GetCharBitmap(char c) {
    switch (c) {
        case 'L': return font_L;
        case 'E': return font_E;
        case 'D': return font_D;
        case 'O': return font_O;
        case 'F': return font_F;
        case 'N': return font_N;
        case ' ': return font_space;
        default:  return font_space;
    }
}

void OLED_DrawString(uint8_t page, uint8_t col, const char *str) {
    while (*str) {
        OLED_DrawChar(page, col, GetCharBitmap(*str));
        col += 6;  // Spazio tra i caratteri
        str++;
    }
}

int main(void) {
    SYS_Initialize(NULL);
    delay_ms(200);

    I2C_TRANSFER_SETUP setup;
    setup.clkSpeed = 100000;
    while(I2C2_IsBusy());
    I2C2_TransferSetup(&setup, 0);

    if (!OLED_Init()) while(1);  // Errore durante l'inizializzazione

    OLED_Clear();

    while (true) {
        uint8_t buffer[2];
        LedCommand ricevuto;

        // Leggi i dati dalla UART
        if (UART1_Read(buffer, sizeof(LedCommand))) {
            memcpy(&ricevuto, buffer, sizeof(LedCommand));
            OLED_Clear();

            // A seconda del comando ricevuto, mostra "LED ON" o "LED OFF"
            if (ricevuto.statoLED == 1) {
                OLED_Clear();
                OLED_DrawString(0, 0, "LED ON");
                
            } else {
                OLED_Clear();
                OLED_DrawString(0, 0, "LED OFF");
                
            }
        }
    }

    return 0;
}


  
/*******************************************************************************
 End of File
*/

