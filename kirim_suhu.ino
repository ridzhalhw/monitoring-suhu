// Include library yang diperlukan
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

// Gunakan serial sebagai monitor
#define DHTPIN 5 //define pin dht 
#define DHTTYPE DHT11 //memilih tipe dht bisa diubah dht22, dht21 dll

DHT dht(DHTPIN,DHTTYPE); //setting pin dan tipe dht

// Buat object Wifi
ESP8266WiFiMulti WiFiMulti;

// Buat object http
HTTPClient http;

//init var suhu
float suhu;
String payload;

//alamat
String url = "http://192.168.43.124/suhu/simpandata.php?suhu=";

void setup() {
  Serial.begin(115200); //komunikasi serial dengan komputer
  Serial.setDebugOutput(false);
  Serial.print("Setup Wait for second. . ")
  for (uint8_t t = 1; t < 10; t++){
    Serial.print(". ");
    Serial.flush();
    delay(1000);
    }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Pusgiono", "rizal123"); //sesuaikan ssid dan password
  dht.begin(); //kominikasi dht dengan arduino
}

void loop() {
  //read suhu
  suhu = dht.readTemperature();

  if ((WiFiMulti.run() == WL_CONNECTED)) {
    //Tambahkan nili suatu suhu pada URL yg sudah dibuat diatas
    Serial.print("[HTTP] Memulai...\n");
    http.begin (url + (String) suhu);

    //mulai koneksi dengan metode get
    Serial.print("[HTTP] Melakukan GET ke server...\n");
    int httpCode = http.GET();

    // Periksa httpCode, akan bernilai negatif kalau error
        if(httpCode > 0) {
            
            // Tampilkan response http
            Serial.printf("[HTTP] kode response GET: %d\n", httpCode);
 
            // Bila koneksi berhasil, baca data response dari server
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                Serial.println(payload);
            }
 
        } else {
 
            Serial.printf("[HTTP] GET gagal, error: %s\n", http.errorToString(httpCode).c_str());
        }
 
        http.end();
    }
    delay (5000);
}
