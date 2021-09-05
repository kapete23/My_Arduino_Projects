#include <EEPROM.h>
#define ON 0
#define OFF 1

const int relay1 = 2;
const int relay2 = 3;
const int relay3 = 4;
const int relay4 = 5;
const int relay5 = 6;
const int relay6 = 7;
const int relay7 = 8;
const int relay8 = 9;
byte State1 = 1;
byte State2 = 1;
byte State3 = 1;
byte State4 = 1;
byte State5 = 1;
byte State6 = 1;
byte State7 = 1;
byte State8 = 1;
char input;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println(F("Control 8 Channel relay via Bluetooth"));
 
 pinMode(relay1,OUTPUT);digitalWrite (relay1,OFF); 
 pinMode(relay2,OUTPUT);digitalWrite (relay2,OFF); 
 pinMode(relay3,OUTPUT);digitalWrite (relay3,OFF); 
 pinMode(relay4,OUTPUT);digitalWrite (relay4,OFF);
 pinMode(relay5,OUTPUT);digitalWrite (relay5,OFF); 
 pinMode(relay6,OUTPUT);digitalWrite (relay6,OFF);
 pinMode(relay7,OUTPUT);digitalWrite (relay7,OFF);
 pinMode(relay8,OUTPUT);digitalWrite (relay8,OFF);

 ReadEEPROM ();
 
}

void loop() {
  // put your main code here, to run repeatedly:
bluetooth();
}

void bluetooth() {
  if (Serial.available()>0)
  {
    input= Serial.read();
    
    if (input == 'A') {
      digitalWrite (relay1,ON); 
      EEPROM.write(1, 0);
        Serial.println("relay 1 ON by Bluetooth");}
    if (input == 'a') {
      digitalWrite (relay1,OFF);
      EEPROM.write(1, 1);
        Serial.println("relay 1 OFF by Bluetooth");}

    if (input == 'B') {
      digitalWrite (relay2,ON); 
      EEPROM.write(2, 0);
        Serial.println("relay 2 ON by Bluetooth");}
    if (input == 'b') {
      digitalWrite (relay2,OFF);
      EEPROM.write(2, 1);
        Serial.println("relay 2 OFF by Bluetooth");}

    if (input == 'C') {
     digitalWrite (relay3,ON);
     EEPROM.write(3, 0); 
        Serial.println("relay 3 ON by Bluetooth");}
    if (input == 'c') {
     digitalWrite (relay3,OFF);
     EEPROM.write(3, 1);
        Serial.println("relay 3 OFF by Bluetooth");}

    if (input == 'D') {
      digitalWrite (relay4,ON); 
      EEPROM.write(4, 0);
        Serial.println("relay 4 ON by Bluetooth");}
    if (input == 'd') {
      digitalWrite (relay4,OFF);
      EEPROM.write(4, 1);
        Serial.println("relay 4 OFF by Bluetooth");}

    if (input == 'E') {
      digitalWrite (relay5,ON); 
      EEPROM.write(5, 0);
        Serial.println("relay 5 ON by Bluetooth");}
    if (input == 'e') {
      digitalWrite (relay5,OFF);
      EEPROM.write(5, 1);
        Serial.println("relay 5 OFF by Bluetooth");}

    if (input == 'F') {
      digitalWrite (relay6,ON); 
      EEPROM.write(6, 0);
        Serial.println("relay 6 ON by Bluetooth");}
    if (input == 'f') {
      digitalWrite (relay6,OFF);
      EEPROM.write(6, 1);
        Serial.println("relay 6 OFF by Bluetooth");}

    if (input == 'G') {
      digitalWrite (relay7,ON); 
      EEPROM.write(7, 0);
        Serial.println("relay 7 ON by Bluetooth");}
    if (input == 'g') {
      digitalWrite (relay7,OFF);
      EEPROM.write(7, 1);
        Serial.println("relay 7 OFF by Bluetooth");}

    if (input == 'H') {
      digitalWrite (relay8,ON); 
      EEPROM.write(8, 0);
        Serial.println("relay 8 ON by Bluetooth");}
    if (input == 'h') {
      digitalWrite (relay8,OFF); 
      EEPROM.write(8, 1);
        Serial.println("relay 8 OFF by Bluetooth");}

}
}

void ReadEEPROM (){
  State1 = EEPROM.read(1);
  State2 = EEPROM.read(2);
  State3 = EEPROM.read(3);
  State4 = EEPROM.read(4);
  State5 = EEPROM.read(5);
  State6 = EEPROM.read(6);
  State7 = EEPROM.read(7);
  State8 = EEPROM.read(8);
  digitalWrite(relay1,State1);
  Serial.print(F("Posisi Terakhir relay1 = "));
  if(State1==0){Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay2,State2);
  Serial.print(F("Posisi Terakhir relay2 = "));
  if(State2==0){Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay3,State3);
  Serial.print(F("Posisi Terakhir relay3 = "));
  if(State3==0){Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay4,State4);
  Serial.print(F("Posisi Terakhir relay4 = "));
  if(State4==0){Serial.println("ON");} else {Serial.println("OFF");}

  digitalWrite(relay5,State5);
  Serial.print(F("Posisi Terakhir relay5 = "));
  if(State5==0){Serial.println("ON");} else {Serial.println("OFF");}
  
  digitalWrite(relay6,State6);
  Serial.print(F("Posisi Terakhir relay6 = "));
  if(State6==0){Serial.println("ON");} else {Serial.println("OFF");}
  
  digitalWrite(relay7,State7);
  Serial.print(F("Posisi Terakhir relay7 = "));
  if(State7==0){Serial.println("ON");} else {Serial.println("OFF");}
  
  digitalWrite(relay8,State8);
  Serial.print(F("Posisi Terakhir relay8 = "));
  if(State8==0){Serial.println("ON");} else {Serial.println("OFF");}
}

void relayON (uint8_t r) {
  digitalWrite (r+1,ON); 
      EEPROM.write(r, 1);
        Serial.print("Relay ");
        Serial.print(r);
        Serial.println(" ON by Bluetooth");
}

void relayOFF (uint8_t r) {
  digitalWrite (r+1,OFF); 
      EEPROM.write(r, 0);
        Serial.print("Relay ");
        Serial.print(r);
        Serial.println(" OFF by Bluetooth");
}
