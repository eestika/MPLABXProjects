#include "rs485_rx.h"
#include "servo_pwm.h"
#include <stdint.h>
#include <stdbool.h>

/*
 * Frame (binaria) attesa:
 *   [0] 0xAA
 *   [1] 0x55
 *   [2] LEN = 0x02          // numero byte payload
 *   [3] CMD = 0x10          // "muovi di delta gradi"
 *   [4] DELTA (int8_t)      // dx=+N, sx=-N   (consigliato -90..+90)
 *   [5] CRC = (LEN+CMD+DELTA) & 0xFF
 */

static uint8_t  s_state      = 0;
static uint8_t  s_len        = 0;
static uint8_t  s_cmd        = 0;
static int8_t   s_delta      = 0;
static uint16_t s_sum        = 0;
static uint8_t  s_angleDeg   = 90;   // 0..180

static inline uint8_t clamp_u8(int v, int lo, int hi)
{
    if (v < lo) v = lo;
    if (v > hi) v = hi;
    return (uint8_t)v;
}

void RS485RX_Init(uint8_t startAngle)
{
    s_state    = 0;
    s_angleDeg = clamp_u8((int)startAngle, 0, 180);
    ServoPWM_SetAngleDeg(s_angleDeg);
}

uint8_t RS485RX_CurrentAngle(void)
{
    return s_angleDeg;
}

void RS485RX_OnByte(uint8_t b)
{
    switch (s_state)
    {
        case 0: // SOF1
            if (b == 0xAA) s_state = 1;
            break;

        case 1: // SOF2
            if (b == 0x55) s_state = 2;
            else           s_state = 0;
            break;

        case 2: // LEN
            s_len = b;
            s_sum = s_len;
            s_state = 3;
            break;

        case 3: // CMD
            s_cmd = b;
            s_sum += s_cmd;
            s_state = 4;
            break;

        case 4: // PAYLOAD (qui atteso: DELTA perché LEN=2)
            if (s_len == 0x02) {
                s_delta = (int8_t)b;
                s_sum  += (uint8_t)s_delta;
                s_state = 5;
            } else {
                s_state = 0; // formato inatteso
            }
            break;

        case 5: // CRC
        {
            uint8_t crc = b;
            if ( ((s_sum & 0xFFu) == crc) && (s_cmd == 0x10u) )
            {
                int next = (int)s_angleDeg + (int)s_delta;
                s_angleDeg = clamp_u8(next, 0, 180);
                ServoPWM_SetAngleDeg(s_angleDeg);
            }
            s_state = 0;
            break;
        }

        default:
            s_state = 0;
            break;
    }
}
