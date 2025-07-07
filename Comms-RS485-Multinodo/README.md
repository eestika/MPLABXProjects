# Comms‑RS485‑Multinodo 📡

Demo di comunicazione RS485 unidirezionale tra due microcontrollori PIC32MX e un'interfaccia USB-RS485 collegata a Raspberry Pi (o PC) tramite adattatore Waveshare.

## 🔹 Architettura del sistema

```
[ PIC1 Master ] --(RS485 bus)--+--> [ PIC2 Slave ]
                               |
                               +--> [ Raspberry Pi / Minicom / Python script ]
```

- **PIC1 (Master)**: invia caratteri ASCII '0' e '1' alla pressione del tasto USER.
- **PIC2 (Slave)**: riceve i caratteri e accende/spegne un LED in base al valore ricevuto.
- **Raspberry Pi**: riceve i dati e li mostra via `minicom` oppure tramite uno script Python (in sviluppo).



## 🛀 Collegamenti hardware

- Collegamento via morsettiera RS485 con linee differenziali:
  - **TA (TX+)** da PIC1 verso **RA (RX+)** su PIC2 e A+ sull'adattatore Waveshare
  - **TB (TX-)** da PIC1 verso **RB (RX-)** su PIC2 e B+ sull'adattatore Waveshare
  - **GND** in comune tra tutti i dispositivi

Le comunicazioni sono unidirezionali (solo da Master verso Slave e Raspberry).

## 📚 Contenuto della cartella

- `/master`  ➔ contiene il codice MPLAB X per il PIC1 Master
- `/slave`   ➔ contiene il codice MPLAB X per il PIC2 Slave
- `/raspberry` ➔ contiene lo script Python `serial_logger.py` per ricezione dati su Raspberry Pi


## 🚀 Funzionamento previsto

- Alla pressione del pulsante USER sul PIC1, viene trasmesso il carattere ASCII `'0'`
- Al rilascio del pulsante viene trasmesso `'1'`
- Il PIC2 riceve questi valori e accende il LED (con `'1'`) o lo spegne (con `'0'`)
- Il Raspberry Pi collegato via USB e adattatore Waveshare visualizza su `minicom` oppure registra i dati via Python

## 🐍 Script Python su Raspberry Pi

Lo script `serial_logger.py` (presente nella cartella `/raspberry`) legge la porta seriale `/dev/ttyUSB0` e stampa su terminale i caratteri ricevuti:

Esempio di output:
Ricevuto: 1
Ricevuto: 0
Ricevuto: 1

## 🔧 Tool e configurazioni

- **Microcontrollori:** PIC32MX, programmati con MPLAB X IDE 6.20 e compilatore XC32
- **Comunicazione:** UART a 115200 baud, 8 bit, no parity, 1 stop bit (8N1)
- **Transceiver:** 2 moduli MIKROE RS485 Click, collegati a un nodo centrale su breadboard
- **Adattatore:** USB → RS485 Waveshare
- **Raspberry Pi:** ricezione dati tramite porta `/dev/ttyUSB0`

## 📝 Estensione futura con Python

Prevediamo di sviluppare uno script Python che:

- Legga in tempo reale dalla porta seriale `/dev/ttyUSB0`
- Stampi i dati su console
- Eventualmente registri i valori su file CSV o database

---

> Progetto realizzato nell'ambito dello studio della comunicazione embedded con RS485. Tutto il codice sorgente è incluso nelle sottocartelle `master/` e `slave/`.

