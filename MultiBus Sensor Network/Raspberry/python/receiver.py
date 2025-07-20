import serial
import struct
import mariadb

# Apertura porta seriale (modifica se serve)
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=2)

# Connessione al database MariaDB
db = mariadb.connect(
    host="localhost",
    user="root",
    password="",  # Metti qui la tua password se c'è
    database="sensordata"
)
cursor = db.cursor()

print("🟢 In ascolto su /dev/ttyUSB0 a 115200 baud...")

while True:
    try:
        # Legge 12 byte: 3 float da 4 byte ciascuno
        data = ser.read(12)

        if len(data) == 12:
            temp, press, hum = struct.unpack('<fff', data)
            print(f"🌡️ Temp: {temp:.2f} °C | 🧱 Press: {press:.2f} hPa | 💧 Hum: {hum:.2f} %")

            # Inserisce nel DB
            cursor.execute(
                "INSERT INTO readings (temperature, pressure, humidity) VALUES (?, ?, ?)",
                (temp, press, hum)
            )
            db.commit()
            print("✅ Dati salvati su MariaDB!\n")

    except Exception as e:
        print(f"❌ Errore: {e}")

