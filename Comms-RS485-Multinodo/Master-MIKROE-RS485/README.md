# PIC1 – Master RS485

Invia valori `0` o `1` su RS485 alla pressione del bottone `USER`.

## Funzionamento

- Usa `UART2` @115200 baud  
- Quando `USER` è premuto, trasmette `'0'`; al rilascio, trasmette `'1'`
- Transceiver RS485 attiva la linea per 10 ms

## Pin

- `USER` → input (interruttore)  
- `TX2` → RS485 Transmit  