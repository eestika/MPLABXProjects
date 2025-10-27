#ifndef UART4_UTIL_H
#define UART4_UTIL_H

#include <stdint.h>
#include <stddef.h>

void UART4_WriteBlocking(const uint8_t* data, size_t length);

#endif
