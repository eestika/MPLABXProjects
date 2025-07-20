#include "canbus.h"
#include "definitions.h" // Include CAN1 PLIB e tipi Microchip

#define CAN_NODE_ID_PIC2 0x123 // Identificatore CAN destinato al PIC2
#define CAN_FIFO_TX      0     // FIFO 0 come TX

void CANBUS_Initialize(void)
{
    CAN1_Initialize();
}

void CANBUS_SendTemperature(float temperature)
{
    uint8_t data[4];
    uint8_t* p = (uint8_t*)&temperature;

    // Copia byte a byte nel buffer
    for (int i = 0; i < 4; i++) {
        data[i] = p[i];
    }

    // Invia i 4 byte come CAN frame standard
    CAN1_MessageTransmit(CAN_NODE_ID_PIC2, 4, data, CAN_FIFO_TX, CAN_MSG_TX_DATA_FRAME);
}
