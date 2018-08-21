<?php 

//init database
$host = "localhost"; 
$user = "root";
$pass = "";   
$dbname = "test"; 

//baca parameter get   /simpandata.php?suhu=x <----
$suhu = $_GET["suhu"];

//buat koneksi ke database
$conn = new mysqli($host, $user, $pass, $dbname);

//periksa koneksi
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Perintah SQL untuk menyimpan data suhu ke tabel sensor
$sql = "INSERT INTO sensor (suhu) VALUES ('$suhu')";
 
// Jalankan dan periksa apakah perintah berhasil dijalankan
if ($conn->query($sql) === TRUE) {
    echo "Sukses - Tersimpan: ".$suhu;
} else {
    echo "Error: ". $conn->error;
}
 
$conn->close();
?>