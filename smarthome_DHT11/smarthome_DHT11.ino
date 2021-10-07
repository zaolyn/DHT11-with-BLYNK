
#define BLYNK_PRINT Serial
#include <DHT.h>
#include <ESP8266WiFi.h> // file untuk modul wifi
#include <BlynkSimpleEsp8266.h> // file untuk blynk nya

char auth[] = "v1ptuxzC8t_P4PzXvqW-ilHRYOVFU_TB"; //token yang dikirim dari blynk ke email masing masing
char ssid[] = "HAU";
char pass[] = "88888888";

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t))// isnan itu is not a number
  {
    Serial.println("Failed to read temp and humidity");
    return;
  }
  Blynk.virtualWrite(V1, t); //setting pin virtual suhu di Blynk
  Blynk.virtualWrite(V2, h); // setting pin Virtual kelembaban di Blynk
}
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, pass, ssid);
  dht.begin(); //sensor mulai membaca
  timer.setInterval(1000L, sendSensor); //waktu untuk mengirimkan data dalam setiap sedetik sekali
}

void loop() {
  Blynk.run();
  timer.run();

}
