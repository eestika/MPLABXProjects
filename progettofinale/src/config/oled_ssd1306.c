/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include "oled_ssd1306.h"
#include "definitions.h"
#include "font5x7.h"

#define CONTROL_BYTE_CMD_SINGLE 0x80
#define CONTROL_BYTE_CMD_STREAM 0x00
#define CONTROL_BYTE_DATA_STREAM 0x40

void OLED_Command(uint8_t command)
{
    uint8_t data[2];
    data[0] = CONTROL_BYTE_CMD_SINGLE;
    data[1] = command;
    I2C2_Write(OLED_I2C_ADDRESS, data, 2);
}

void OLED_Init(void)
{
    uint8_t init_sequence[] = {
        0xAE, 0xD5, 0x80, 0xA8, 0x3F,
        0xD3, 0x00, 0x40, 0x8D, 0x14,
        0x20, 0x00, 0xA1, 0xC8, 0xDA,
        0x12, 0x81, 0xCF, 0xD9, 0xF1,
        0xDB, 0x40, 0xA4, 0xA6, 0xAF
    };
    for (size_t i = 0; i < sizeof(init_sequence); i++)
    {
        OLED_Command(init_sequence[i]);
    }
}

void OLED_Clear(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        OLED_Command(0xB0 + page);
        OLED_Command(0x00);
        OLED_Command(0x10);

        for (uint8_t col = 0; col < OLED_WIDTH; col++)
        {
            uint8_t data[2] = { CONTROL_BYTE_DATA_STREAM, 0x00 };
            I2C2_Write(OLED_I2C_ADDRESS, data, 2);
        }
    }
}

void OLED_SetCursor(uint8_t x, uint8_t y)
{
    OLED_Command(0xB0 + y);
    OLED_Command(0x00 + (x & 0x0F));
    OLED_Command(0x10 + ((x >> 4) & 0x0F));
}

void OLED_PrintChar(char c)
{
    uint8_t data[6];
    data[0] = CONTROL_BYTE_DATA_STREAM;
    for (uint8_t i = 0; i < 5; i++)
    {
        data[i + 1] = font5x7[(c - 32) * 5 + i];
    }
    I2C2_Write(OLED_I2C_ADDRESS, data, 6);
}

void OLED_PrintString(const char* str)
{
    while (*str)
    {
        OLED_PrintChar(*str++);
    }
}

void OLED_Fill(uint8_t pattern)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        OLED_Command(0xB0 + page);
        OLED_Command(0x00);
        OLED_Command(0x10);
        for (uint8_t col = 0; col < OLED_WIDTH; col++)
        {
            uint8_t data[2] = { CONTROL_BYTE_DATA_STREAM, pattern };
            I2C2_Write(OLED_I2C_ADDRESS, data, 2);
        }
    }
}





/* *****************************************************************************
 End of File
 */
