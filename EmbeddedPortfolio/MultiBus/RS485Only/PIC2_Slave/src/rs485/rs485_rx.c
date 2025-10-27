#include "rs485_rx.h"
#include "definitions.h"
#include "sensordata.h"
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Legge esattamente n byte da UART5 (bloccante).
 * 
 * @param dst buffer di destinazione
 * @param n   numero di byte da leggere
 * @return true se letti con successo, false se errore UART
 */
bool RS485_ReadExact(uint8_t* dst, size_t n)
{
    // attende che non ci sia un’operazione in corso
    while (UART5_ReadIsBusy()) { }

    // avvia la lettura di n byte
    if (!UART5_Read(dst, n))
        return false;

    // attende fine lettura
    while (UART5_ReadIsBusy()) { }

    return true;
}

/**
 * @brief Variante compatibile con vecchio codice:
 *        riceve 12 byte e popola direttamente la struct SensorData_t.
 * 
 * @param data puntatore alla struttura dati
 * @return true se i dati sono stati ricevuti e copiati, false altrimenti
 */
bool RS485_ReceiveSensorData(SensorData_t* data)
{
    if (data == NULL)
        return false;

    uint8_t buffer[12];

    // esegue la lettura completa (bloccante)
    if (!RS485_ReadExact(buffer, sizeof(buffer)))
        return false;

    memcpy(&(data->temperature), &buffer[0], 4);
    memcpy(&(data->pressure),    &buffer[4], 4);
    memcpy(&(data->humidity),    &buffer[8], 4);

    return true;
}

