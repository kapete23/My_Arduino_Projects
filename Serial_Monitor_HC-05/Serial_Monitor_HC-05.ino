#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial module_bluetooth (0, 1); // Rx | Tx
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin (38400); //Komunikasi serial menggunakan software IDE pada baudrate 9600
  module_bluetooth.begin (38400); //Baudrate module bluetooth
}

void loop() {
  //Membaca terhubungnya koneksi HC-05 dengan Arduino pada Serial Monitor
  if (module_bluetooth.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (module_bluetooth.available() > 0) {
      // display each character to the LCD
      lcd.write(module_bluetooth.read());
    }
  }
}
