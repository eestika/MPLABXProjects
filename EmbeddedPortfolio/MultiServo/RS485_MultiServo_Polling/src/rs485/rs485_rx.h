#ifndef RS485_RX_H
#define RS485_RX_H

#include <stdint.h>

/* Inizializza lo stato del parser RS485 e imposta l'angolo iniziale del servo */
void RS485RX_Init(uint8_t startAngle);

/* Da chiamare per ogni byte ricevuto da UART5 */
void RS485RX_OnByte(uint8_t b);

/* (facoltativo) Recupera l'angolo corrente */
uint8_t RS485RX_CurrentAngle(void);

#endif /* RS485_RX_H */
