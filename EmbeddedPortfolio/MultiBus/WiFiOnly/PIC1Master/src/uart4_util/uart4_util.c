#include "definitions.h"
#include "uart4_util.h"

void UART4_WriteBlocking(const uint8_t* data, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        while (U4STAbits.UTXBF); // Attendi se buffer pieno
        U4TXREG = data[i];
    }

    while (!UART4_TransmitComplete()); // Attendi fine trasmissione
}
