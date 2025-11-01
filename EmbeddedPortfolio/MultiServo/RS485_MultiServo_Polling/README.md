# RS485 MultiServo (Polling Version)

## 🇮🇹 Descrizione generale

Questo progetto realizza un sistema **Master/Slave via RS-485** tra un **Raspberry Pi** e uno o più microcontrollori **PIC32MX**.  
Il master (Raspberry) invia comandi binari tramite un adattatore USB–RS485; gli slave (PIC32) ricevono i frame, li interpretano e muovono servomotori **MG90S** via PWM.

Attualmente il progetto implementa:
- **Versione in polling** (UART5 del PIC senza interrupt)
- **Un solo slave (PIC32)**
- **Comunicazione half-duplex RS-485 a 2 fili**
- **Protocollo binario proprietario** con checksum

In sviluppo:
- Versione **interrupt-driven** per maggiore robustezza  
- Gestione **multi-slave** con indirizzamento RS-485 condiviso

---

## ⚙️ Architettura del sistema

   ┌──────────────────────┐
   │ Raspberry Pi (Master)│
   │  • C++ program        │
   │  • USB ↔ RS485 adapter│
   └──────────┬───────────┘
              │  (A+/B−)
              ▼
   ┌──────────────────────┐
   │  MIKROE-2821 RS485   │
   │  transceiver (3.3V)  │
   └──────────┬───────────┘
              │ UART5 (RF12/RF13)
              ▼
   ┌──────────────────────┐
   │  PIC32MX795F512L     │
   │  RS485_Servo_Slave   │
   │  OC1 → RD0 → MG90S   │
   └──────────────────────┘

---

## 🔸 Raspberry Master

📁 **Percorso:** `EmbeddedPortfolio/MultiServo/RS485_MultiServo_Polling/Raspberry_Master/master_rs485.cpp`

### Funzioni principali
- Configura la porta seriale `/dev/ttyUSB0` tramite API **POSIX** (`termios`) a 115200 bps, 8N1.  
- Costruisce frame binarie del tipo:

AA 55 | LEN | CMD | DELTA | CRC

Dove:
- `AA 55` = header (start of frame)
- `LEN` = lunghezza payload (2)
- `CMD` = comando (0x10 = movimento incrementale)
- `DELTA` = spostamento angolare (signed, +dx / -sx)
- `CRC` = somma (LEN + CMD + DELTA) & 0xFF

### Esecuzione
```bash
g++ master_rs485.cpp -o master_rs485
sudo ./master_rs485

Esempio di sessione:
In quale direzione vuoi spostare il servo? (dx/sx): dx
Di quanto vuoi muovere il servo (gradi 1..90)? 15
TX: AA 55 02 10 0F 21  (delta=15)

PIC32 Slave

📁 Percorso: EmbeddedPortfolio/MultiServo/RS485_MultiServo_Polling/RS485_MultiServo_Polling.X

Funzioni principali

Ricezione UART5 in polling (RF12 = RX, RF13 = TX).

Parser dei frame binari nel modulo rs485_rx.c.

PWM su OC1/RD0 per controllo di un servo MG90S.

Funzione di delay basata su _CP0_GET_COUNT().

Calibrazione iniziale del servo (90° al reset).

Protocollo interpretato

Quando riceve una frame valida AA 55 02 10 Δ CRC,
il PIC calcola:
nuovo_angolo = angolo_corrente + Δ
🧩 Hardware utilizzato
Componente	Ruolo	Note
Raspberry Pi 4	Master	C++ con API POSIX
Adattatore USB↔RS485/422 (Waveshare)	Interfaccia RS-485	Collegamento half-duplex 2 fili (A+/B−)
MIKROE-2821 (RS485 3 Click)	Transceiver 3.3V	Collegato a UART5 del PIC
PIC32MX795F512L	Slave	80 MHz, OC1 su RD0
Servo MG90S	Attuatore	5 V, GND comune
📘 Note tecniche

RS-485 configurato a 115200 bps, 8N1, senza controllo di flusso.

DE/RE del MIKROE mantenuti a livello logico basso (ricezione sempre attiva).

GND comune tra Raspberry, MIKROE e PIC.

Servo alimentato separatamente a 5V con massa comune.

👨‍💻 Autore

Daniele Perez – Perez Dynamics OÜ