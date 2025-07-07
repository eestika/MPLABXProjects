# PIC2 – Slave RS485

Riceve `0` o `1` via RS485. Accende o spegne LED su `LED1`.

## Funzionamento

- Usa `UART2` @115200 baud in modalità ascolto continua  
- Se riceve `'0'`, spegne LED; se `'1'`, lo accende

## Pin

- `RX2` ← RS485 Receive  
- `LED1` → output digitale (LED)  