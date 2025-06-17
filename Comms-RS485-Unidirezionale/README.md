# Comunicazione RS485 unidirezionale – PIC32MX

Questo progetto dimostra una **comunicazione RS485 unidirezionale** tra due microcontrollori **PIC32MX795F512L**, utilizzando due moduli **MIKROE-2821**.

## 🔧 Descrizione

- Il **Master** invia un comando (toggle) alla pressione del tasto `USER` (RE6).
- Lo **Slave** riceve il comando tramite UART5 e accende o spegne il LED collegato al pin `RE3`, configurato in modalità **sinking**.

## 📡 Collegamenti

I moduli MIKROE-2821 sono collegati così:

- **TX+ (Master)** → **RX+ (Slave)**
- **TX− (Master)** → **RX− (Slave)**
- **GND** ↔ **GND**

⚠️ Nota: i moduli **non supportano comunicazione bidirezionale**, perché non hanno gestione di direzione `DE/RE`.

## 📁 Struttura

```
Comms-RS485-Unidirezionale/
├── Master_RS485.X/
├── Slave_RS485.X/
└── README.md
```

## 📘 Note

- I moduli usano il chip **SP485E**.
- È una **comunicazione RS485 vera**, ma **solo unidirezionale**.
- Ideale per topologie **Master → Slave**.