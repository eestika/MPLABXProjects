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

#include <stdint.h>

const uint8_t font5x7[96][5] = {
    // 0x20 (spazio) fino a 0x7F (tilde)
    // [0] = 0x20 = ' '
    {0x00, 0x00, 0x00, 0x00, 0x00}, // ' '
    // ...
    // H = 0x48 = index 72 - 32 = 40
    [40] = {0x7F, 0x08, 0x08, 0x08, 0x7F}, // 'H'
    [37] = {0x3E, 0x41, 0x41, 0x41, 0x22}, // 'E'
    [44] = {0x00, 0x41, 0x7F, 0x41, 0x00}, // 'L'
    [47] = {0x3E, 0x41, 0x41, 0x41, 0x3E}, // 'O'
    // ...
};



/* *****************************************************************************
 End of File
 */
