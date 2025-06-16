# Comunicazione UART punto-punto con moduli RS485 MIKROE

Questo progetto dimostra una comunicazione UART **punto-punto half-duplex** tra due microcontrollori **PIC32MX795F512L**, utilizzando i moduli **RS485 3.3V click (MIKROE-2821)** di MikroElektronika.

## 📦 Struttura del progetto

Comms-UART-MIKROE-PuntoPunto/
├── Master/
│ └── Master_UART_MIKROE.X/
└── Slave/
└── Slave_UART_MIKROE.X/


- `Master/`: alla pressione del pulsante **USER** (RE6), invia un carattere via UART.
- `Slave/`: riceve il carattere e accende il **LED verde su RE3** in logica sinking.

## 🔧 Dettagli tecnici

- **UART utilizzata**: UART5 (TX = RF13, RX = RF12)
- **Velocità di trasmissione**: 115200 baud
- **Logica LED**: modalità sinking (LOW = acceso)
- **Bottoni**: USER (RE6) con logica attiva bassa

## 🔌 Collegamenti RS485

| PIC1 (Master) | ↔︎ | MIKROE-2821 | ↔︎ | MIKROE-2821 | ↔︎ | PIC2 (Slave) |
|---------------|----|-------------|----|-------------|----|----------------|
| RF13 (TX)     | →  | RX          |    | TX          | →  | RF12 (RX)     |
| RF12 (RX)     | ←  | TX          |    | RX          | ←  | RF13 (TX)     |
| GND           | —  | GND         |    | GND         | —  | GND           |

- ⚠️ I moduli devono essere collegati **TX+ → RX+** e **TX− → RX−**, **non TX+ → TX+**.
- I morsetti a vite si usano solo per collegare i canali RS485.

## ✅ Requisiti

- MPLAB X IDE v6.20
- XC32 Compiler
- 2 moduli MIKROE RS485 3.3V Click (MIKROE-2821)
- Alimentazione 3.3V
- Breadboard e cavetteria jumper

## 🧪 Stato del progetto

✔️ Comprovato funzionamento in entrambe le direzioni  
✔️ Testato sia in modalità diretta che con moduli RS485  
✔️ Pronto per espansione con **terzo nodo (es: Raspberry Pi)**

---

