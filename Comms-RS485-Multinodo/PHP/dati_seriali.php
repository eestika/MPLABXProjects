<?php
// Connessione al database
$host = "localhost";
$user = "root";
$password = ""; // ← Inserisci la tua password se esiste
$database = "rs485log";

$conn = new mysqli($host, $user, $password, $database);

// Verifica connessione
if ($conn->connect_error) {
    die("Connessione fallita: " . $conn->connect_error);
}

// Query dei dati
$sql = "SELECT * FROM dati ORDER BY id DESC LIMIT 100";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <title>Dati ricevuti via RS485</title>
    <style>
        body { font-family: Arial; margin: 20px; }
        table { border-collapse: collapse; width: 60%; }
        th, td { border: 1px solid #888; padding: 8px; text-align: center; }
        th { background-color: #f0f0f0; }
    </style>
</head>
<body>
    <h2>Ultimi dati ricevuti</h2>
    <table>
        <tr>
            <th>ID</th>
            <th>Valore</th>
            <th>Timestamp</th>
        </tr>

        <?php
        if ($result && $result->num_rows > 0) {
            while($row = $result->fetch_assoc()) {
                echo "<tr>
                        <td>{$row['id']}</td>
                        <td>{$row['valore']}</td>
                        <td>{$row['timestamp']}</td>
                      </tr>";
            }
        } else {
            echo "<tr><td colspan='3'>Nessun dato disponibile</td></tr>";
        }
        $conn->close();
        ?>
    </table>
</body>
</html>
