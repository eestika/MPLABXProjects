# Comms‑RS485‑Multinodo 📡

Demo di comunicazione RS485 unidirezionale tra due microcontrollori PIC32MX e un'interfaccia USB-RS485 collegata a Raspberry Pi. I dati vengono registrati in un database MariaDB e visualizzati tramite una pagina web PHP.

## 🔹 Architettura del sistema

```
[ PIC1 Master ] --(RS485 bus)--+--> [ PIC2 Slave ]
                               |
                               +--> [ Raspberry Pi → MariaDB + PHP ]
```

- **PIC1 (Master)**: invia caratteri ASCII '0' e '1' alla pressione del tasto USER.
- **PIC2 (Slave)**: riceve i caratteri e accende/spegne un LED.
- **Raspberry Pi**: registra i dati su MariaDB tramite uno script Python e li visualizza su web con PHP.

## 🛠️ Funzionalità attuali

✅ Acquisizione dati via RS485  
✅ Logging automatico su database MariaDB  
✅ Scelta all’avvio dello script se **azzerare** o **accodare** i dati  
✅ Visualizzazione dati via browser con `dati_seriali.php`

## 🖧 Comunicazione hardware

- Collegamenti RS485 differenziali:
  - `TX+` Master → `RX+` Slave e `A+` adattatore USB
  - `TX-` Master → `RX-` Slave e `B+` adattatore USB
  - `GND` in comune

- Protocollo UART: **115200 baud**, 8N1

## 📂 Contenuto della cartella

- `/master` ➔ codice sorgente MPLAB X per il PIC Master
- `/slave` ➔ codice sorgente MPLAB X per il PIC Slave
- `/raspberry/ricevitore_log_db.py` ➔ script Python per loggare su MariaDB
- `/php/dati_seriali.php` ➔ pagina web per visualizzare i dati registrati

## 🐍 Script Python: `ricevitore_log_db.py`

Lo script Python riceve e registra i dati RS485:

- Porta seriale: `/dev/ttyUSB0`
- Baud rate: 115200
- Salvataggio automatico su MariaDB
- A ogni avvio chiede: **Vuoi iniziare da zero? (s/N)**  
  - `s` ➔ TRUNCATE TABLE = reset totale  
  - `N` ➔ accoda i dati

Esempio:

```
Vuoi iniziare da zero? (s/N): s
In ascolto sulla porta seriale...
Ricevuto: 1
Ricevuto: 0
```

## 🌐 Visualizzazione dati via browser

La pagina `dati_seriali.php` mostra gli ultimi dati ricevuti:

- Collegarsi a: `http://192.168.1.122/dati_seriali.php`
- Tabella ordinata per ID decrescente (ultimi in cima)
- Accessibile solo in rete locale

⚠️ Per ora la pagina **non è accessibile dall’esterno**, ma può essere mostrata via screenshot.

## 🧰 Requisiti software

- **MPLAB X IDE 6.20** + XC32 per i microcontrollori
- **MariaDB** installato su Raspberry Pi
- **Apache + PHP + phpMyAdmin** per la dashboard
- Python 3.11 con `mariadb` e `pyserial` installati

## 📝 Sviluppi futuri

- Logging parallelo su file CSV
- Accesso remoto via VPN o tunnel per PHP
- Dashboard in tempo reale con grafici

---

> Progetto didattico e sperimentale per lo studio delle comunicazioni embedded con RS485.
