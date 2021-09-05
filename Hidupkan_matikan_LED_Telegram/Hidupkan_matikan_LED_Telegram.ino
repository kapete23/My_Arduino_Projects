#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>
#define WIFI_SSID "AndroidAP12"
#define WIFI_PASSWORD "inin1055"

// Initialize Telegram BOT 
const char BotToken[] = "1049877828:AAHzClbdIXD8Iru8igZl-7HcolCLMkSwdFY";
const int relay = 2; 

WiFiClientSecure net_ssl; 
TelegramBot bot (BotToken, net_ssl); 
// the number of the LED pin 
  
void setup() {   
  Serial.begin(115200);      
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menghubungkan");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Terhubung ke ");
  Serial.println(WiFi.localIP());   
  bot.begin();   
  pinMode(relay, OUTPUT);   
}
   
void loop() {   
  message m = bot.getUpdates(); // Read new messages   
  if (m.text.equals("on"))  
  {   
    digitalWrite(relay, HIGH);  
    bot.sendMessage(m.chat_id, "The Led is now ON");  
  }   
  else if (m.text.equals("off"))  
  {   
    digitalWrite(relay, LOW); 
    bot.sendMessage(m.chat_id, "The Led is now OFF");   
  }   
}   
