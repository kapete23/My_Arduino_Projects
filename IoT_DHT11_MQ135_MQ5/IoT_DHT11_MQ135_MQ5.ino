#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include "MQ135.h"
#define DHTPIN 14
#define DHTTYPE DHT11
#define pinSensor A0
#define FIREBASE_HOST "https://iot-dht11-mq135-mq5.firebaseio.com/"
#define FIREBASE_AUTH "WW1f4YEWfSn02UipwReJS3fuXLZgQetIVsHZX0QP"
#define WIFI_SSID "bvsh"
#define WIFI_PASSWORD "123456789"

int pinIC_4051_[3] = {12,13,15};
int measurementsSent = 0;

MQ135 gasSensor = MQ135(pinSensor);
DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) pinMode(pinIC_4051_[i], OUTPUT);
  pinMode(pinSensor, INPUT);
  dht.begin();
  
  // Menghubungkan ke wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Terhubung ke ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

int n = 0;

void loop() {
  if (WiFi.status() != WL_CONNECTED ) {
    Serial.println("Mencoba lagi menghubungkan NodeMCU ke WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Menghubungkan ");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print("*");
      delay(500);
    }
    Serial.println();
    Serial.print("Terhubung ke ");
    Serial.println(WiFi.localIP());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
  }
  
  //Baca data semua sensor
  //Baca sensor suhu dan kelembaban
  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();
  if (isnan(kelembapan) || isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  delay(10);
  //Baca sensor kualitas udara
  for (int j = 0; j < 3; j++) digitalWrite(pinIC_4051_[j], LOW);
  float co2ppm = gasSensor.getPPM();
  delay(10);
  //Baca sensor gas LPG
  digitalWrite(pinIC_4051_[0], HIGH);
  digitalWrite(pinIC_4051_[1], LOW);
  digitalWrite(pinIC_4051_[2], LOW);
  float Nilai_Gas = analogRead(pinSensor);
  delay(10);
  
  //Cetak hasil sensor ke serial monitor
  Serial.print("Nilai Gas : ");
  Serial.println(Nilai_Gas);   
  Serial.print(F("CO2ppm "));
  Serial.println(co2ppm);
  Serial.print("Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %\t");
  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.println(" *C ");
  Serial.println();

  //Kirim data ke firebase
  // set value
  Firebase.setFloat(firebaseData,"Suhu", suhu);
  Firebase.setFloat(firebaseData,"Kelembapan", kelembapan);
  Firebase.setFloat(firebaseData,"CO2_PPM", co2ppm);
  Firebase.setFloat(firebaseData,"Gas_Sensor", Nilai_Gas);
  Firebase.setInt(firebaseData,"Tombol1", 1);
  Serial.println ("Data suhu, kelembapan, gas CO2 dan nilai gas LPG sukses terkirim ke Firebase");
  delay(1000);
}
