// *****************************************************************************
// Main Source File per PIC2 - solo ricezione WiFi
//
// Company:
//     Perez Dynamics OÜ
//
// File Name:
//     main.c
//
// Summary:
//     Ricezione dati JSON da ESP8266 via UART4, analisi temperatura, accensione LED
//
// Description:
//     PIC2 riceve via WiFi (ESP8266 in modalità AP) una stringa JSON contenente
//     temperatura, pressione e umidità. Analizza solo la temperatura per decidere
//     se accendere il LED rosso o verde (modalità sinking).
// *****************************************************************************

#include "definitions.h"
#include "utils.h"
#include "sensordata.h"
#include "logica.h"
#include "wifi_at_rx.h"

int main(void)
{
    SYS_Initialize(NULL);
    DelayMs(2000);  // Attesa stabilizzazione sistema

    // Inizializza il modulo ESP8266 come Access Point e TCP server
    WiFi_AT_Initialize();

    // Configura i LED come OUTPUT
    TRISECLR = (1 << 1); // RE1 = output (LED rosso)
    TRISECLR = (1 << 3); // RE3 = output (LED verde)

    // Spegni entrambi i LED (HIGH = spento in modalità sinking)
    LATESET = (1 << 1);  // RE1 HIGH ? LED rosso spento
    LATESET = (1 << 3);  // RE3 HIGH ? LED verde spento

    // Dati ricevuti dal master via JSON
    SensorData_t wifiData;

    while (1)
    {
        // Ricezione stringa JSON da ESP (UART4)
        if (WiFi_AT_ReceiveSensorData(&wifiData))
        {
            // Analizza temperatura e accende LED appropriato
            Logica_ProcessData(&wifiData);
        }

        // Piccolo delay per evitare polling aggressivo
        DelayMs(200);
    }

    // In teoria non si arriva mai qui
    return 0;
}
