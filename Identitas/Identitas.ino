#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 9, 10, 11, 12);

void setup() {
  lcd.begin(16,2);

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Kevin P Tambunan");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("TEKNIK ELEKTRO");
  delay(1000);
}
