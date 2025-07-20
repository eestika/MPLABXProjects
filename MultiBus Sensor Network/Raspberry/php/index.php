<?php
$host = "localhost";
$user = "root";
$password = "";  // Inserisci se c'è una password
$database = "sensordata";

// Connessione
$conn = new mysqli($host, $user, $password, $database);
if ($conn->connect_error) {
    die("❌ Connessione fallita: " . $conn->connect_error);
}

// Query ultimi 10 valori
$sql = "SELECT * FROM readings ORDER BY timestamp DESC LIMIT 10";
$result = $conn->query($sql);

// HTML
echo "<h2>🌡️ Ultimi Dati BME280</h2>";
echo "<table border='1' cellpadding='5'>";
echo "<tr><th>🕒 Timestamp</th><th>🌡️ Temp (°C)</th><th>🧱 Press (hPa)</th><th>💧 Hum (%)</th></tr>";

while ($row = $result->fetch_assoc()) {
    echo "<tr>";
    echo "<td>{$row['timestamp']}</td>";
    echo "<td>{$row['temperature']}</td>";
    echo "<td>{$row['pressure']}</td>";
    echo "<td>{$row['humidity']}</td>";
    echo "</tr>";
}

echo "</table>";
$conn->close();
?>
