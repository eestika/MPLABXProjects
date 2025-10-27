#include "parser.h"
#include <stdint.h>

/*
 * Atteso:
 *  raw[0..7]   = 0xF7..0xFE (P[19:12],P[11:4],P[3:0]|T[19:16],T[19:12],T[11:4],H[15:8],H[7:0])
 *  calib[0..25]= 0x88..0xA1 (T/P calib + H1 in calib[25])
 *  calib[26..32]=0xE1..0xE7 (H2..H6)
 * Nota: assicurati che bme280.c riempia 33 byte in calib.
 */

void PARSER_ProcessData(const uint8_t* raw, const uint8_t* calib, SensorData_t* result)
{
    // --- ADC grezzi ---
    uint32_t adc_P = ((uint32_t)raw[0] << 12) | ((uint32_t)raw[1] << 4) | (raw[2] >> 4);
    uint32_t adc_T = ((uint32_t)raw[3] << 12) | ((uint32_t)raw[4] << 4) | (raw[5] >> 4);
    uint32_t adc_H = ((uint32_t)raw[6] << 8)  | raw[7];

    // --- Calibrazione T/P (datasheet Bosch) ---
    uint16_t dig_T1 = (uint16_t)(calib[0] | (calib[1] << 8));
    int16_t  dig_T2 = (int16_t)(calib[2] | (calib[3] << 8));
    int16_t  dig_T3 = (int16_t)(calib[4] | (calib[5] << 8));

    uint16_t dig_P1 = (uint16_t)(calib[6] | (calib[7] << 8));
    int16_t  dig_P2 = (int16_t)(calib[8] | (calib[9] << 8));
    int16_t  dig_P3 = (int16_t)(calib[10] | (calib[11] << 8));
    int16_t  dig_P4 = (int16_t)(calib[12] | (calib[13] << 8));
    int16_t  dig_P5 = (int16_t)(calib[14] | (calib[15] << 8));
    int16_t  dig_P6 = (int16_t)(calib[16] | (calib[17] << 8));
    int16_t  dig_P7 = (int16_t)(calib[18] | (calib[19] << 8));
    int16_t  dig_P8 = (int16_t)(calib[20] | (calib[21] << 8));
    int16_t  dig_P9 = (int16_t)(calib[22] | (calib[23] << 8));

    // --- Calibrazione umidità ---
    // H1 è a 0xA1 (== calib[25])
    uint8_t  dig_H1 = calib[25];

    // H2..H6 sono a 0xE1..0xE7 (== calib[26..32])
    int16_t  dig_H2 = (int16_t)( (calib[27] << 8) | calib[26] );       // little-endian
    uint8_t  dig_H3 = calib[28];

    // H4 e H5 sono valori 12-bit SIGNED con bit packing particolare:
    // H4 = (E4 << 4) | (E5 & 0x0F), con sign a 12 bit
    // H5 = (E6 << 4) | (E5 >> 4),   con sign a 12 bit
    int16_t dig_H4 = (int16_t)((((int16_t)((int8_t)calib[29])) << 4) | (calib[30] & 0x0F));
    int16_t dig_H5 = (int16_t)((((int16_t)((int8_t)calib[31])) << 4) | (calib[30] >> 4));

    int8_t   dig_H6 = (int8_t)calib[32];

    // --- Temperatura (t_fine) ---
    int32_t var1 = ((((int32_t)adc_T >> 3) - ((int32_t)dig_T1 << 1)) * (int32_t)dig_T2) >> 11;
    int32_t var2 = (((((int32_t)adc_T >> 4) - (int32_t)dig_T1) * (((int32_t)adc_T >> 4) - (int32_t)dig_T1)) >> 12) * (int32_t)dig_T3 >> 14;
    int32_t t_fine = var1 + var2;

    // °C in float
    result->temperature = ((t_fine * 5 + 128) >> 8) / 100.0f;

    // --- Pressione ---
    // Protezione: dig_P1 non deve essere 0
    float pressure_hPa = 0.0f;
    if (dig_P1 != 0)
    {
        int64_t pvar1 = ((int64_t)t_fine) - 128000;
        int64_t pvar2 = pvar1 * pvar1 * (int64_t)dig_P6;
        pvar2 = pvar2 + ((pvar1 * (int64_t)dig_P5) << 17);
        pvar2 = pvar2 + (((int64_t)dig_P4) << 35);
        pvar1 = ((pvar1 * pvar1 * (int64_t)dig_P3) >> 8) + ((pvar1 * (int64_t)dig_P2) << 12);
        pvar1 = (((((int64_t)1) << 47) + pvar1) * (int64_t)dig_P1) >> 33;

        if (pvar1 != 0)
        {
            int64_t p = 1048576 - adc_P;
            p = (((p << 31) - pvar2) * 3125) / pvar1;
            int64_t pvar1_2 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
            int64_t pvar2_2 = (((int64_t)dig_P8) * p) >> 19;
            p = ((p + pvar1_2 + pvar2_2) >> 8) + (((int64_t)dig_P7) << 4);
            pressure_hPa = (float)p / 25600.0f;   // Pa/100 ? hPa
        }
    }
    result->pressure = pressure_hPa;

// --- Umidità relativa (%RH) ---
int32_t v_x1_u32r = t_fine - ((int32_t)76800);

v_x1_u32r =
    (((((adc_H << 14)
        - (((int32_t)dig_H4) << 20)
        - (((int32_t)dig_H5) * v_x1_u32r))
       + 16384) >> 15)
     * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10)
            * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + 32768)) >> 10)
          + 2097152) * ((int32_t)dig_H2) + 8192) >> 14));

v_x1_u32r = v_x1_u32r
            - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7)
                 * ((int32_t)dig_H1)) >> 4);

if (v_x1_u32r < 0) v_x1_u32r = 0;
if (v_x1_u32r > 419430400) v_x1_u32r = 419430400;

result->humidity = (float)(v_x1_u32r >> 12) / 1024.0f;
if (result->humidity < 0.0f)   result->humidity = 0.0f;
if (result->humidity > 100.0f) result->humidity = 100.0f;
}