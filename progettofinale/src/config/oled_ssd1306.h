/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
 oled_ssd1306.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C


void OLED_Init(void);
void OLED_Command(uint8_t cmd);
void OLED_Data(uint8_t* data, uint16_t size);
void OLED_Clear(void);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_PrintChar(char c);
void OLED_PrintString(const char* str);
void OLED_Fill(uint8_t pattern);

#endif // OLED_SSD1306_H


  


/* *****************************************************************************
 End of File
 */
