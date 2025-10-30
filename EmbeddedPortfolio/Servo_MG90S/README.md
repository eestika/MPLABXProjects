# PIC32 – Servo PWM via OCMP1 (Timer2) – MG90S Demo  
**Versione:** 1.0 · **Data:** Ottobre 2025  

---

## 🇮🇹 Descrizione  
Questo progetto dimostra il controllo di un servomotore **MG90S** tramite il modulo **OCMP1** del microcontrollore **PIC32MX795F512L**, utilizzando **Timer2** come base temporale.  
Il segnale PWM ha un periodo di **20 ms (50 Hz)** e impulsi variabili da **1.0 ms (0°)** a **2.0 ms (180°)**.  

Il codice è stato reso **modulare**:  
- `servo_pwm.c/.h` gestisce la generazione del PWM e l’impostazione dell’angolo.  
- `delay_ms.c/.h` fornisce un ritardo software basato su `TMR2_CounterGet()`.  
- `main.c` dimostra un movimento continuo da 0° a 180° e ritorno.  

Progetto generato con **MPLAB X IDE v6.20** + **MCC** (Timer2 e OCMP1 configurati da MCC).

---

### 🔧 Wiring
| Componente | Pin MCU | Descrizione |
|-------------|----------|-------------|
| Servo MG90S – Segnale | RD0 / OC1 | Impulso PWM |
| Servo MG90S – VCC | +5 V esterno | Non alimentare dal 3V3 del PIC |
| Servo MG90S – GND | GND comune | Stesso GND della scheda MCU |

---

### 🧩 File principali
| File | Descrizione |
|------|--------------|
| `main.c` | Programma principale: sweep da 0° a 180°. |
| `servo_pwm.c/.h` | Driver PWM per servomotore, con configurazione flessibile. |
| `delay_ms.c/.h` | Funzione di ritardo basata su Timer2. |

---

### ⚙️ API del modulo `servo_pwm`
```c
void ServoPWM_Init(const ServoPwmConfig_t *cfg);
void ServoPWM_SetPulseUS(uint16_t us);
void ServoPWM_SetAngleDeg(uint8_t deg);
