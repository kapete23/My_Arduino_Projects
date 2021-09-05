#include "timer.h"
#include <NoDelay.h>                              //library (class) delay non-blocking menggunakan millis()
#include <SoftwareSerial.h>
#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
//#include <LiquidCrystal_I2C.h>
#define FIREBASE_HOST "https://iot-control-arah-putaran-motor-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "yJLiz9UCQqNtmivTYgrjEfbmsLsbX0hgMMy33yNK"
#define WIFI_SSID "ESP8266"
#define WIFI_PASSWORD "16samai0"

FirebaseData firebaseData;
//LiquidCrystal_I2C lcd (0x27, 4, 5);

const byte Relay_A = 5;
const byte Relay_B = 4;
const byte Relay_C = 0;
const byte Relay_D = 2;
String MAJU1, MUNDUR1;
String MAJU2, MUNDUR2;

bool sign1 = true;
bool sign2 = true;

noDelay time_tanpa_delay(150);

//Timer object
Timer waktu1,waktu2;

void Matikan_motor1() {
  digitalWrite (Relay_A, LOW);
  digitalWrite (Relay_B, LOW);
  Firebase.setString(firebaseData, "Keadaan_Motor", "Diam");
  sign1 = true;
}

void Matikan_motor2() {
  digitalWrite (Relay_C, LOW);
  digitalWrite (Relay_D, LOW);
  Firebase.setString(firebaseData, "Keadaan_Motor", "Diam");
  sign2 = true;
}

void setup() {
  Serial.begin(9600);
  /*Wire.begin(5, 4);
    lcd.init();
    lcd.backlight();*/

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
  pinMode(Relay_A, OUTPUT);
  pinMode(Relay_B, OUTPUT);
  pinMode (Relay_C, OUTPUT);
  pinMode (Relay_D, OUTPUT);

  //Set Logic awal untuk Relay
  digitalWrite (Relay_A , LOW);
  digitalWrite (Relay_B, LOW);
  digitalWrite (Relay_C, LOW);
  digitalWrite (Relay_D, LOW);

  Firebase.setString(firebaseData, "Maju1", "0");
  Firebase.setString(firebaseData, "Mundur1", "0");
  Firebase.setString(firebaseData, "Maju2", "0");
  Firebase.setString(firebaseData, "Mundur2", "0");

  waktu1.setTimeout(3000); // untuk motor 1 lama waktu fungsi dipanggil sekali eksekusi
  waktu2.setTimeout(3000); // untuk motor 2 lama waktu fungsi dipanggil sekali eksekusi

  //Set our callback function
  waktu1.setCallback(Matikan_motor1);
  waktu2.setCallback(Matikan_motor2);
}

void loop() {
if (time_tanpa_delay.update()) {
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
  Firebase.get(firebaseData, "Maju1");
  MAJU1 = firebaseData.stringData();
  Firebase.get(firebaseData, "Mundur1");
  MUNDUR1 = firebaseData.stringData();
  if ((MAJU1 == "1") && (MUNDUR1 == "0")&&(sign1)) //Maju
  {
    digitalWrite (Relay_A, HIGH);
    digitalWrite (Relay_B, LOW);
    Firebase.setString(firebaseData, "Maju1", "0");
    Firebase.setString(firebaseData, "Keadaan_Motor", "Bergerak (Maju1)");
    sign1 = false;
    waktu1.start();
  }
  else if ((MUNDUR1 == "1") && (MAJU1 == "0")&&(sign1)) //Mundur
  {
    digitalWrite (Relay_A, LOW);
    digitalWrite (Relay_B, HIGH);
    Firebase.setString(firebaseData, "Mundur1", "0");
    Firebase.setString(firebaseData, "Keadaan_Motor", "Bergerak (Mundur1)");
    sign1 = false;
    waktu1.start();
  }


  Firebase.get(firebaseData, "Maju2");
  MAJU2 = firebaseData.stringData();
  Firebase.get(firebaseData, "Mundur2");
  MUNDUR2 = firebaseData.stringData();
  if ((MAJU2 == "1") && (MUNDUR2 == "0")&&(sign2)) //Maju
  {
    digitalWrite (Relay_C, HIGH);
    digitalWrite (Relay_D, LOW);
    Firebase.setString(firebaseData, "Maju2", "0");
    Firebase.setString(firebaseData, "Keadaan_Motor", "Bergerak (Maju2)");
    sign2 = false;
    waktu2.start();
  }
  else if ((MUNDUR2 == "1") && (MAJU2 == "0")&&(sign2)) //Mundur
  {
    digitalWrite (Relay_C, LOW);
    digitalWrite (Relay_D, HIGH);
    Firebase.setString(firebaseData, "Mundur2", "0");
    Firebase.setString(firebaseData, "Keadaan_Motor", "Bergerak (Mundur2)");
    sign2 = false;
    waktu2.start();
  }
}
  /*  //Cetak hasil sensor ke LCD 16 x 04
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DR:" + String(da, 1) + "Var");
    lcd.setCursor(0, 1);
    lcd.print("DS:" + String(ds) + "VA");
    lcd.setCursor(0, 2);
    lcd.print("DA : " + String(daya) + " W");
  */

  waktu1.update();
  waktu2.update();
}
