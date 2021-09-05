#include <SoftwareSerial.h>
#include <PZEM004Tv30.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#define FIREBASE_HOST "https://sistem-iot-kw-mater.firebaseio.com/"
#define FIREBASE_AUTH "JSNrM5FxuiMnFjTFETetlFY2ByzvHEom8GCna8hN"
#define WIFI_SSID "Oppo A3s"
#define WIFI_PASSWORD "12345678"

FirebaseData firebaseData;
LiquidCrystal_I2C lcd (0x3F, 16, 4);
//SoftwareSerial PZEM-004T (13, 15, false, 256);
PZEM004Tv30 pzem (12,14); //Pin RX & TX untuk PZEM-004T

void setup() {
  Serial.begin(9600);
  Wire.begin(5,4);
  lcd.init();                     
  lcd.backlight();
  
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

  //Membaca data dari firebase untuk mereset counter KWh meter ke nol
  Firebase.get(firebaseData,"Reset_KWh_Status");
  String firestate = firebaseData.stringData();
  if (firestate == "1")
  {
    pzem.resetEnergy();
    Firebase.setString(firebaseData,"Reset_KWh_Status", "0");
  }
  
  //Baca data sensor PZEM-004T 100 Ampere dan tampilkan data di serial monitor
  float tegangan = pzem.voltage();
    if( !isnan(tegangan) ){
        Serial.print("Voltage: "); Serial.print(tegangan); Serial.println("V");
    } else {
        Serial.println("Error reading voltage");
    }

  float arus = pzem.current();
    if( !isnan(arus) ){
        Serial.print("Current: "); Serial.print(arus); Serial.println("A");
    } else {
        Serial.println("Error reading current");
    }

  float daya = pzem.power();
    if( !isnan(daya) ){
        Serial.print("Power: "); Serial.print(daya); Serial.println("W");
    } else {
        Serial.println("Error reading power");
    }

  float energi = pzem.energy();
    if( !isnan(energi) ){
        Serial.print("Energy: "); Serial.print(energi,3); Serial.println("kWh");
    } else {
        Serial.println("Error reading energy");
    }

  float frekuensi = pzem.frequency();
    if( !isnan(frekuensi) ){
        Serial.print("Frequency: "); Serial.print(frekuensi, 1); Serial.println("Hz");
    } else {
        Serial.println("Error reading frequency");
    }
    
  //Cetak hasil sensor ke LCD 16 x 04
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:" + String(tegangan,1) + "V");
  lcd.setCursor(9, 0);
  lcd.print("I:" + String(arus) + "A");
  lcd.setCursor(0, 1);
  lcd.print("Energi : " + String(energi) + " KWh");

  //Kirim data ke firebase
  Firebase.setFloat(firebaseData,"Tegangan", tegangan);
  Firebase.setFloat(firebaseData,"Arus", arus);
  Firebase.setFloat(firebaseData,"Daya", daya);
  Firebase.setFloat(firebaseData,"Energi", energi);
  Firebase.setFloat(firebaseData,"Frekuensi", frekuensi);
  delay(2000);
}
