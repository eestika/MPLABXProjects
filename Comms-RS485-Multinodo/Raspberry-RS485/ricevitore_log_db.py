import serial
import mariadb
import time

# --- Configura porta seriale
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # attesa per stabilizzazione della porta

# --- Connessione al database MariaDB
try:
    conn = mariadb.connect(
        user="root",
        password="TUAPASSWORDQUI",  # Inserisci la tua password
        host="localhost",
        database="rs485log"
    )
    cursor = conn.cursor()
except mariadb.Error as e:
    print(f"Errore di connessione a MariaDB: {e}")
    exit(1)

# --- Chiede se iniziare da zero
scelta = input("Vuoi iniziare da zero? (s/N): ").strip().lower()
if scelta == "s":
    try:
        cursor.execute("TRUNCATE TABLE dati")
        conn.commit()
        print("✅ Tabella 'dati' azzerata completamente.")
    except mariadb.Error as e:
        print(f"Errore nel reset della tabella: {e}")
        conn.close()
        exit(1)

print("In ascolto sulla porta seriale...\n")

try:
    while True:
        if ser.in_waiting > 0:
            valore = ser.read(1).decode('utf-8', errors='ignore').strip()
            if valore in ['0', '1']:
                print(f"Ricevuto: {valore}")
                try:
                    cursor.execute("INSERT INTO dati (valore) VALUES (?)", (valore,))
                    conn.commit()
                except mariadb.Error as e:
                    print(f"Errore nell'inserimento: {e}")
            else:
                print("Dato ricevuto non valido, ignorato.")
except KeyboardInterrupt:
    print("\nInterrotto da tastiera. Chiusura...")
finally:
    ser.close()
    conn.close()
