#include <ACS712.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#define pinSensor A0
#define FIREBASE_HOST "https://sensor-volt-ampere-herz-iot.firebaseio.com/"
#define FIREBASE_AUTH "oSofhrIF18cDGNFsovkH4fxeSOjFt9gQebVdcmXE"
#define WIFI_SSID "Anonymous"
#define WIFI_PASSWORD "namaabang"

int input = 0;
const int pinRelay = 14;
String firestate;
int high_time;
int low_time;
int nilai_adc= 0;        
float voltage_ac= 0;
int pinIC_4051_[3] = {12,13,15};
float time_period;
float frequency;
double temp_amp=0.0; //gunakan tipe data double pada penampung penjumlahan arus sensor
float temps, adcVolt, cal_value;
unsigned long calTime=0, time_cal=600;
boolean on_calibrasi=false;

ACS712 sensorArus(ACS712_05B, pinSensor);
FirebaseData firebaseData;
LiquidCrystal_I2C lcd (0x27,20,4);

void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  Wire.begin(5,4);
  lcd.init();                     
  lcd.backlight();
  for (int i = 0; i < 3; i++) pinMode(pinIC_4051_[i], OUTPUT);
  pinMode(pinSensor, INPUT);
  pinMode(pinRelay, OUTPUT);
  for (int j = 0; j < 3; j++) digitalWrite(pinIC_4051_[j], HIGH);
  sensorArus.calibrate();
  
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
  //Baca data semua sensor
  //Baca sensor tegangan (ZMPT101B)
  digitalWrite(pinIC_4051_[0], HIGH);
  digitalWrite(pinIC_4051_[1], LOW);
  digitalWrite(pinIC_4051_[2], HIGH);
  nilai_adc = analogRead(pinSensor);      
  voltage_ac = map(nilai_adc, 0,695,0,220);
  delay(10);
  
  //Baca sensor arus (ACS712)
  for (int j = 0; j < 3; j++) digitalWrite(pinIC_4051_[j], HIGH);
  float I = sensorArus.getCurrentAC();
  delay(10);
  
  //Baca sensor frekuensi
  high_time = pulseIn(input, HIGH);
  low_time = pulseIn(input, LOW);

  time_period = high_time + low_time;
  time_period = time_period / 1000;
  frequency = 1000 / time_period;
  delay(10);
  
  //Cetak hasil sensor ke LCD 20 x 04
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V : " + String(voltage_ac) + " Volt");
  lcd.setCursor(0, 1);
  lcd.print("A : " + String(I) + " A");
  lcd.setCursor(0, 2);
  lcd.print("F : " + String(frequency, 2) + " Hz");

  //Membaca data dari firebase untuk kontrol relay
  Firebase.get(firebaseData,"Relay_Status");
  firestate = firebaseData.stringData();
  if (firestate == "1")
  {
    digitalWrite(pinRelay, HIGH);
  }

  else if (firestate == "0")
  {
    digitalWrite(pinRelay, LOW);
  }
  //Kirim data ke firebase
  Firebase.setFloat(firebaseData,"Tegangan", voltage_ac);
  Firebase.setFloat(firebaseData,"Arus", I);
  Firebase.setFloat(firebaseData,"Frekuensi", frequency);
  delay(1000);
}
