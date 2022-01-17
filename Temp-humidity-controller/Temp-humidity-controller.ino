#include <Wire.h>
#include "DHT.h"
#include <menu.h>                                 //menu macros and objects
#include <LiquidCrystal_I2C.h>                    //F. Malpartida LCD's driver
#include <NoDelay.h>                              //library (class) delay non-blocking menggunakan millis()

//Library sistem menu di download disini : https://github.com/neu-rah/ArduinoMenu
#include <menuIO/keyIn.h>                         //keyboard driver and fake stream (for the encoder button)
//#include <menuIO/serialIn.h>
//#include <menuIO/serialOut.h>
#include <menuIO/encoderIn.h>                     //quadrature encoder driver and fake stream
#include <menuIO/chainStream.h>                   //concatenate multiple input streams (this allows adding a button to the encoder)
#include <menuIO/lcdOut.h>                        //malpartidas lcd menu output
#include <EEPROM.h>                               //Library untuk mengatur EEPROM
#include "inisialisasi_I2C-LCD_rotaryEncoder.h"
#include "deklarasi_Variabel.h"

using namespace Menu;

// Setting humidity atau kelembaban
MENU(Hum,"Set Kelembapan",doNothing,noEvent,noStyle
  ,FIELD(dataSet.humi[0],"H1"," %",20,90,10,1,saveData,exitEvent,wrapStyle)
  ,FIELD(dataSet.humi[1],"H2"," %",20,90,10,1,saveData,exitEvent,wrapStyle)
  ,EXIT("< Kembali")
);

// Setting temperatur dalam derajat celsius
MENU(Temp,"Set Suhu",doNothing,noEvent,noStyle
  ,altFIELD(decPlaces<2>::menuField,dataSet.temp[0],"T1"," \xDF\x43",0,50,1,0.01,saveData,exitEvent,wrapStyle)
  ,altFIELD(decPlaces<2>::menuField,dataSet.temp[1],"T2"," \xDF\x43",0,50,1,0.01,saveData,exitEvent,wrapStyle)
  ,EXIT("< Kembali")
);



/*************************** Menu Utama ***************************/

MENU(menuUtama,"Menu Utama",doNothing,noEvent,wrapStyle
  ,SUBMENU(Temp)   // Set Temperatur
  ,SUBMENU(Hum)    // Set Humidity
  ,FIELD(dataSet.tunda,"tSensor","ms",250,5000,10,1,saveData,exitEvent,wrapStyle)
  ,EXIT("< Kembali")
);

/******************************************************************/

DHT dht(4, DHT11); //(DHT_PIN, DHT_TYPE)

NAVROOT(nav,menuUtama,MAX_DEPTH,in,out); //the navigation root object

//'\x08'-> Alamat karakter pada LCD2002 untuk Cursor  
config myOptions('\x08','-',defaultNavCodes,true);

void setup() {
  //Serial.begin(115200);
  //Serial.begin(9600);
  dht.begin();
  byte charRam[8];
  pinMode(encBtn,INPUT_PULLUP);
  encoder.begin();
  lcd.begin(16,2);
  EEPROM.get(0, dataSet);
  for(byte b = 0; b < 4; b++) {
    lcd.createChar(b, (byte*)charCustom[b]);
  }
  dsPtr = &dataSet;   //Akses data dengan pointer
  options=&myOptions; //can customize options
  nav.showTitle=false;
  nav.useUpdateEvent = false;
  nav.idleOn();
}

void loop() {
  nav.poll();  //Panggil sistem menu
  if(!nav.sleepTask) { //Membuat scroll bar
    lcd.setCursor(15,0);
    lcd.write(nav.node().sel==0?byte(1):byte(2));
    lcd.setCursor(15,1);
    lcd.write((nav.node().sel<(nav.node().sz()-1))?byte(2):byte(3));
  }

  currentMillis = millis();
  if (currentMillis - previousMillis >= (*dsPtr).tunda) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if(nav.sleepTask) TSensor();
  }

  delay(90);

  //Serial.println(nav.node().target->dirty);
  //Serial.println(nav.lastChanged);
  //Serial.println(nav.idleChanged);
  //Serial.println(nav.canExit);
  //nav.node().target->style();
  //nav.node().root->navFocus;
  //Serial.println(nav.node().target->events());
}

void TSensor(){
  //Input data sensor DHT11
  float tempe = dht.readTemperature(); //Dalam derajat celsius
  int hmdty = dht.readHumidity();

  //Clear display and set position cursor
  lcd.clear();
  lcd.home();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(hmdty) || isnan(tempe)) {
    lcd.print("Sensor longgar");
    lcd.setCursor(0, 1);
    lcd.print("Tidak terpasang");
  } else {
    lcd.print("T : " + String(tempe) + " \xDF\x43");
    lcd.setCursor(0, 1);
    lcd.print("H : " + String(hmdty) + " %");
  }
/*
  if (t <= 37.5 || h >= 60)
  {
    digitalWrite(2, LOW);
  }
  if (t >= 39.5 || h <= 50)
  {
    digitalWrite(3, HIGH);
  }
  */
  //if (a >= (*dsPtr).temp[1]) digitalWrite(LED_BUILTIN, HIGH);
  //else digitalWrite(LED_BUILTIN, LOW);
}
