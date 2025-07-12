# Sensor-BME280-RS485-Log

Questo progetto dimostrativo è stato realizzato per acquisire i dati ambientali (temperatura, pressione e umidità) da un sensore **BME280** tramite un microcontrollore **PIC32MX**, e inviarli attraverso **RS485 UART** sia a un altro PIC32 slave che a un **Raspberry Pi 4**, il quale li salva su un database **MariaDB** e li visualizza via **interfaccia web PHP**.

## 📦 Architettura del sistema

- **PIC1 (Master)**:
  - Legge i dati dal sensore BME280 via I2C.
  - Costruisce un pacchetto dati binario di 34 byte.
  - Invia i dati via UART (RS485) sia al Raspberry Pi che a PIC2.

- **PIC2 (Slave)**:
  - Riceve i dati via UART (RS485).
  - Estrae la temperatura dal pacchetto.
  - In base alla soglia (es. 24.5°C), accende un LED rosso o verde.

- **Raspberry Pi 4**:
  - Ascolta via porta seriale.
  - Decodifica i dati binari.
  - Salva i dati su un database MariaDB.
  - Li visualizza in una pagina PHP.

## 📁 Struttura delle cartelle

```
Sensor-BME280-RS485-Log/
├── master/                  → codice MPLAB X IDE del PIC1 (Master)
├── slave/                   → codice MPLAB X IDE del PIC2 (Slave)
├── raspberry/
│   └── serial_logger_bme280_decoder.py → script Python per acquisizione e logging
├── php/
│   └── bme280.php           → pagina web per mostrare i dati
└── README.md
```

## 🛠️ Requisiti

### Firmware
- MPLAB X IDE 6.20
- XC32 Compiler
- MCC con supporto UART, OCMP, Timer2
- PIC32MX795F512L

### Hardware
- 2× PIC32MX (es. Clicker o dev board compatibile)
- 2× Moduli RS485 Mikroe-2821
- Sensore BME280
- Raspberry Pi 4 (con MariaDB e PHP installati)

### Raspberry: Installazione pacchetti richiesti
```bash
sudo apt update
sudo apt install mariadb-server php python3-pip
pip3 install mariadb pyserial
```

## 🧪 Database MariaDB

Creare il database con:

```sql
CREATE DATABASE bme280log;

USE bme280log;

CREATE TABLE misure (
    id INT AUTO_INCREMENT PRIMARY KEY,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    temperatura FLOAT,
    pressione FLOAT,
    umidita FLOAT
);
```

## 🐍 Codice Python (serial_logger_bme280_decoder.py)

Lo script riceve il pacchetto binario, lo decodifica e salva i dati nel database.

## 🌐 Frontend PHP

Visualizza gli ultimi 10 dati ambientali con una tabella HTML.

## 📌 Note

Attualmente il servomotore non è stato integrato in modo definitivo. Il comportamento viene espresso tramite accensione di LED per semplicità e stabilità del sistema.