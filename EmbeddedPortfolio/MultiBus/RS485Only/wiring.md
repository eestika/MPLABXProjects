# Wiring – RS485Only (25/10/2025)

Documentazione collegamenti tra PIC1, PIC2 e moduli RS485 Mikroe.  
Setup fotografato e salvato in `Photo/`.

---

## PIC1 (Master)
- **UART5 TX (RF13)** → `RX` modulo RS485 Mikroe (sinistra)
- **UART5 RX (RF12)** → `TX` modulo RS485 Mikroe (sinistra)
- **I2C2 RA3 (SDA2)** → SDA sensore BME280
- **I2C2 RA2 (SCL2)** → SCL sensore BME280
- **Alimentazione**:  
  - 3.3V → VCC modulo RS485 e BME280  
  - GND → GND modulo RS485, BME280 e breadboard comune

---

## PIC2 (Slave)
- **UART5 TX (RF13)** → `RX` modulo RS485 Mikroe (destra)
- **UART5 RX (RF12)** → `TX` modulo RS485 Mikroe (destra)
- **Alimentazione**:  
  - 3.3V → VCC modulo RS485  
  - GND → GND modulo RS485 e breadboard comune

---

## Moduli RS485 Mikroe
- **Alimentazione**:  
  - VCC → 3.3V  
  - GND → comune
- **Connessioni UART**:  
  - TX/RX collegati alle rispettive UART5 dei PIC
- **Linee RS485**:  
  - TX+ → linea bus condivisa (cavo giallo)  
  - TX- → linea bus condivisa (cavo arancione)  
  - GND → linea comune (cavo nero)  
  (collegate anche al convertitore USB ↔ RS485 esterno)

---

## Nodo centrale
- Breadboard piccola usata come nodo per unire linee:  
  - TX+ ↔ TX+ ↔ TX+  
  - TX- ↔ TX- ↔ TX-  
  - GND comune

---

## Converter USB ↔ RS485
- A- → TX+ linea bus condivisa (cavo giallo)  
- B+ → TX- linea bus condivisa (cavo arancione)  
- PE → GND linea comune (cavo nero)

---

## Note
- Tutto il bus lavora a **3.3V**, nessun level shifter necessario.  
- Foto complete in `Photo/2025-10-25/`.  
- Wiring corrispondente al setup prima dello smontaggio del 25/10/2025.
