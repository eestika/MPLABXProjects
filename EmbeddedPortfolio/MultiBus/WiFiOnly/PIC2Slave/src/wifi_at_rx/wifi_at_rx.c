#include "wifi_at_rx.h"
#include "definitions.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define WIFI_UART_ReadByte(b) UART4_Read((uint8_t*)(b), 1)
#define WIFI_UART_ReadIsBusy() UART4_ReadIsBusy()

static char rx_buffer[512];
static int rx_index = 0;

// Parsing del JSON ricevuto
static bool parse_json(const char* json, SensorData_t* out) {
    if (json == NULL || out == NULL) return false;

    float t, p, h;
    int parsed = sscanf(json, "{\"t\":%f,\"p\":%f,\"h\":%f}", &t, &p, &h);

    if (parsed == 3) {
        out->temperature = t;
        out->pressure = p;
        out->humidity = h;
        return true;
    }
    return false;
}

// Riceve una riga terminata da \n
static bool receive_line(char* line, size_t max_len) {
    char c;
    while (!WIFI_UART_ReadIsBusy()) {
        if (WIFI_UART_ReadByte(&c)) {
            if (rx_index < max_len - 1) {
                rx_buffer[rx_index++] = c;
                if (c == '\n') {
                    rx_buffer[rx_index] = '\0';
                    strcpy(line, rx_buffer);
                    rx_index = 0;
                    return true;
                }
            } else {
                rx_index = 0;
            }
        }
    }
    return false;
}

void WiFi_AT_Initialize(void)
{
    UART4_Write((uint8_t*)"AT+CWMODE=2\r\n", 13);
    DelayMs(1000);

    UART4_Write((uint8_t*)"AT+CIPAP=\"192.168.4.2\"\r\n", 24);
    DelayMs(1000);

    UART4_Write((uint8_t*)"AT+CIPMUX=1\r\n", 13);
    DelayMs(1000);

    UART4_Write((uint8_t*)"AT+CIPSERVER=1,5000\r\n", 22);
    DelayMs(2000);

    // Attendi messaggio "CONNECT"
    char line[256];
    unsigned long timeout = 10000; // 10 secondi max
    unsigned long start = _CP0_GET_COUNT();
    unsigned long ticks = ( SYS_FREQ / 2 / 1000) * timeout;

    while ((_CP0_GET_COUNT() - start) < ticks) {
        if (receive_line(line, sizeof(line))) {
            if (strstr(line, "CONNECT")) {
                break; // handshake OK
            }
        }
    }
}

bool WiFi_AT_ReceiveSensorData(SensorData_t* data) 
{
    static char json[256];
    int index = 0;
    char byte;

    while (!WIFI_UART_ReadIsBusy()) {
        if (WIFI_UART_ReadByte(&byte)) {
            if (index < sizeof(json) - 1) {
                json[index++] = byte;
                if (byte == '}') {
                    json[index] = '\0';
                    return parse_json(json, data);
                }
            } else {
                index = 0;
            }
        }
    }

    return false;
}
