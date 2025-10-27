// *****************************************************************************
// Main Source File - Versione WiFiOnly
//
// Company:
//     Perez Dynamics OÜ
//
// File Name:
//     main.c
//
// Summary:
//     Punto di ingresso principale per il progetto WiFiOnly.
//
// Description:
//     Questo codice inizializza il sistema e monitora il tasto USER (RE6).
//     Alla pressione, legge i dati dal sensore BME280, li elabora e li invia
//     via WiFi al server TCP tramite comandi AT.
// *****************************************************************************

#include <stdlib.h>
#include "definitions.h"
#include "input.h"
#include "utils.h"
#include <string.h>
#include "bme280.h"
#include "parser.h"
#include "utils.h"
#include "wifi_at_tx.h"


int main(void)
{
    SYS_Initialize(NULL);
    WiFi_AT_Initialize();  // Test solo AT

    while (true)
    {
        // Vuoto per test: resta acceso LED verde o rosso
    }

    return 0;
}
