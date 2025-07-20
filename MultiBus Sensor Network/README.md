# 🛠️ MultiBus Sensor Network

**Evoluzione da codice monolitico a piattaforma modulare con comunicazione RS‑485 (e futura integrazione Wi‑Fi)**

---

## 🇮🇹 Descrizione del Progetto

Questo progetto è una **versione evoluta** rispetto al precedente sistema monolitico. È strutturato ora in modo modulare:

- **PIC1 – Master (C, MPLAB X IDE)**: legge dati da sensore (temperatura, pressione, umidità) e li trasmette via RS‑485.
- **PIC2 – Slave (C, MPLAB X IDE)**: riceve i dati, confronta la temperatura rispetto a una soglia e gestisce due LED (verde/rosso).
- **Raspberry PI (Python)**: riceve gli stessi dati via RS‑485, li visualizza a console e li salva in MariaDB.

📌 *Nelle versioni successive verrà aggiunto il supporto Wi‑Fi come canale principale, mantenendo RS‑485 come fallback.*

---

## 🇬🇧 Project Overview

This project is an **evolved** version of the previous monolithic system, now organized into a modular architecture:

- **PIC1 – Master (C, MPLAB X IDE)**: reads sensor data (temperature, pressure, humidity) and sends it over RS‑485.
- **PIC2 – Slave (C, MPLAB X IDE)**: receives data, compares temperature to a threshold, and controls two LEDs (green/red).
- **Raspberry PI (Python)**: reads the same data over RS‑485, prints it on console, and stores it in MariaDB.

📌 *Future versions will introduce Wi‑Fi as the main communication channel, with RS‑485 as a fallback.*

---

## 📁 Struttura del Repository

[ PIC1 Master (C) ]
↓ RS‑485
[ PIC2 Slave (C) ] → LED (verde/rosso)
↓ RS‑485
[ Raspberry PI (Python) ] → console + MariaDB


---

## ✅ Funzionalità Attuali

- ✅ Comunicazione bi‑direzionale RS‑485 tra PIC e Raspberry
- ✅ Invio e ricezione di 3 valori float: temperatura, pressione, umidità
- ✅ Valutazione soglia termica su PIC2 → LED rosso/verdi
- ✅ Visualizzazione console e salvataggio in DB su Raspberry

---

## 🚀 Prossimi Obiettivi

1. Implementare **Wi‑Fi** su PIC1 e PIC2  
2. Gestire fallback robusto su RS‑485 e timeout  
3. Pubblicare foto, wiring diagram e demo nel repo  
4. Documentare l'installazione e l’uso del BME280 e la calibrazione

---

## 📸 Demo & Foto (in arrivo)

Presto aggiornerò con:
- Foto dei collegamenti HW
- Diagrammi a blocchi e cablaggio
- Video / GIF demo del sistema in funzione

---


