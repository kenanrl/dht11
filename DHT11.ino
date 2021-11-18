#define BLYNK_PRINT Serial

#include <DHT.h>
#include <ESP8266WiFi.h> // file untuk modul wifi
#include <BlynkSimpleEsp8266.h> // file untuk blynk

char auth[] = "AJtGgCm5LLxPqFRXuKXPsjPWWCMbfcPv";
char ssid[] = "AndroidAPdcd2";
char pass[] = "hotspot12";

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity(); // h = humidity
  float t = dht.readTemperature(); // t = Temperature

  if (isnan(h) || isnan(t)) {  // isnan = non number -- // mengecek kondisi apabila suhu dan kelembapan tidak ada
    Serial.println("Failed to read temp and humidity");
    return;
  }

  Blynk.virtualWrite(V1, t); // setting virtual suhu di blynk
  Blynk.virtualWrite(V2, h); // setting virtual humidity di blynk

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin(); //sensor mulai membaca suhu(t) dan kelembapan(h)
  timer.setInterval(1000, sendSensor); // Interval = berulangan/loop tapi berwaktu -- // waktu untuk mengirim data
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();  
}
