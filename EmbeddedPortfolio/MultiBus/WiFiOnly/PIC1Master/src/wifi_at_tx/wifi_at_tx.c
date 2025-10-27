#include "wifi_at_tx.h"
#include "definitions.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <device.h>

// === Wi-Fi ===
#define WIFI_SSID   "Laboratory"
#define WIFI_PASS   "Cleopatra"

// LED (sinking su PORTE)
#define LED_BIANCO_ON()   LATECLR = (1u << 2)
#define LED_BIANCO_OFF()  LATESET  = (1u << 2)
#define LED_ROSSO_ON()    LATECLR  = (1u << 1)
#define LED_ROSSO_OFF()   LATESET  = (1u << 1)

static inline void blink_white_twice(void){
    for (int i = 0; i < 2; i++){ LED_BIANCO_ON(); DelayMs(120); LED_BIANCO_OFF(); DelayMs(120); }
}

/* ---------- UART4 utils: polling + clear error ---------- */

// azzera OERR e drena eventuale spazzatura
static void U4_ErrorClearRegs(void)
{
    if (U4STA & _U4STA_OERR_MASK) { U4STACLR = _U4STA_OERR_MASK; }
    volatile uint8_t dump;
    while (U4STA & _U4STA_URXDA_MASK) { dump = (uint8_t)U4RXREG; }
    (void)dump;
}

static bool U4_ReadByte(uint8_t* out, uint32_t timeout_ms)
{
    uint32_t elapsed = 0;
    while (elapsed < timeout_ms) {
        if (U4STA & _U4STA_OERR_MASK) U4_ErrorClearRegs();      // sblocca RX
        if (U4STA & _U4STA_URXDA_MASK) { *out = (uint8_t)U4RXREG; return true; }
        DelayMs(1); elapsed += 1;
    }
    return false;
}

static void U4_FlushRx(void)
{
    U4_ErrorClearRegs();
    int idle_ms = 0; uint8_t d;
    while (idle_ms < 5) {
        if (U4STA & _U4STA_URXDA_MASK) { d = (uint8_t)U4RXREG; (void)d; idle_ms = 0; }
        else { DelayMs(1); idle_ms++; }
    }
}

static void U4_SendLine(const char* s)   // invia s + CRLF via registri
{
    char line[128];
    size_t n = snprintf(line, sizeof line, "%s\r\n", s);
    for (size_t i = 0; i < n; i++) { while (U4STA & _U4STA_UTXBF_MASK){} U4TXREG = line[i]; }
    while ((U4STA & _U4STA_TRMT_MASK) == 0){} // shift reg vuoto
}

static bool U4_WaitOK(uint32_t timeout_ms)
{
    char buf[256]; size_t idx=0; uint32_t elapsed=0; buf[0]='\0';
    while (elapsed < timeout_ms) {
        uint8_t c;
        if (U4_ReadByte(&c, 1)) {
            if (idx < sizeof(buf)-1) buf[idx++] = (char)c; buf[idx] = '\0';
            if (strstr(buf, "OK"))                           return true;
            if (strstr(buf, "ERROR") || strstr(buf, "FAIL")) return false;
        } else { DelayMs(1); elapsed += 1; }
    }
    return false; // timeout
}

/* ----------------------- Sequenza AT (run-once) ----------------------- */
void WiFi_AT_Initialize(void)
{
    static bool already_run = false;
    if (already_run) return;          // evita rilanci multipli in main
    already_run = true;

    LED_BIANCO_OFF();
    LED_ROSSO_OFF();

    DelayMs(3000);                    // boot ESP
    U4_FlushRx();

    // 1) AT
    U4_SendLine("AT");
    DelayMs(50);
    if (!U4_WaitOK(4000)) { LED_ROSSO_ON(); return; }
    blink_white_twice();

    // 2) CWMODE=1
    U4_FlushRx();
    U4_SendLine("AT+CWMODE=1");
    DelayMs(50);
    if (!U4_WaitOK(4000)) { LED_ROSSO_ON(); return; }
    blink_white_twice();

    // 3) Join AP (nessun blink dopo questo comando)
    char cmd[160];
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"", WIFI_SSID, WIFI_PASS);
    U4_FlushRx();
    U4_SendLine(cmd);
    if (!U4_WaitOK(30000)) { LED_ROSSO_ON(); return; }

    // STOP qui per questa fase
}
