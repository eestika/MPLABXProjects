import serial

# Configura la porta seriale (modifica se serve)
porta_seriale = '/dev/ttyUSB0'
baudrate = 115200

try:
    ser = serial.Serial(porta_seriale, baudrate, timeout=1)
    print(f"🟢 Connessione seriale aperta su {porta_seriale} a {baudrate} bps")
except serial.SerialException as e:
    print(f"🔴 Errore apertura porta seriale: {e}")
    exit()

print("📡 In ascolto dei dati in arrivo (Ctrl+C per uscire)...\n")

try:
    while True:
        dato = ser.read().decode('utf-8', errors='ignore')
        if dato:
            print(f"➡️  Ricevuto: {dato}")
except KeyboardInterrupt:
    print("\n⏹️ Uscita richiesta. Chiudo porta seriale.")
finally:
    ser.close()
