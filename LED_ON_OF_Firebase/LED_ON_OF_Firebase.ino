#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#define FIREBASE_HOST "https://led-on-off-c3555.firebaseio.com/"
#define FIREBASE_AUTH "18DdTjVDUrvYBiBLamG0iJlIkXjOsqcb9YiKXATB"
#define WIFI_SSID "AndroidAP12"
#define WIFI_PASSWORD "inin1055"

String firestate;

FirebaseData firebaseData;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
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
  Firebase.setString(firebaseData,"Led_Status", "off");
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

  Firebase.getString(firebaseData,"Led_Status");
  firestate = firebaseData.stringData();
  Serial.println(firestate);
  if (firestate == "on")
  {
    digitalWrite(LED_BUILTIN, LOW);
  }

  else if (firestate == "off")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}
