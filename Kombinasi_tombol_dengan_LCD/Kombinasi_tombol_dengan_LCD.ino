#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

const int Tombol_[3] = {2, 3, 4};

const char Nama_[14] = {'K', 'e', 'v', 'i', 'n', 'P', 'T', 'a', 'm', 'b', 'u', 'n', 'a', 'n'};

const char Prodi_[13] = {'T', 'E', 'K', 'N', 'I', 'K', 'E', 'L', 'E', 'K', 'T', 'R', 'O'};
                                                                       
void setup() {
  lcd.begin(16,2);
  for(int i = 0; i < 3; i++) {
    digitalWrite(Tombol_[i], HIGH);
  }
}

void loop() {
if (digitalRead(Tombol_[0]) == LOW) {
  lcd.clear();
  delay(500);
  lcd.setCursor(0,0);
  lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);

  for (int j = 0; j < 5; j++) {
    lcd.setCursor(j,0);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
    lcd.print(Nama_[j]);
    lcd.setCursor((j+1),0);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }

  lcd.setCursor(6,0);
  lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);
  lcd.print(Nama_[5]);
  lcd.setCursor(7,0);
  lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);

  for (int k = 0; k < 8; k++) {
    lcd.setCursor((k+8),0);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
    lcd.print(Nama_[k+6]);
    lcd.setCursor((k+9),0);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }
  for (int m = 0; m < 6; m++) {
    lcd.setCursor((m+1),1);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
    lcd.print(Prodi_[m]);
    lcd.setCursor((m+2),1);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }

  for (int n = 0; n < 7; n++) {
    lcd.setCursor((n+8),1);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
    lcd.print(Prodi_[n+6]);
    lcd.setCursor((n+9),1);
    lcd.cursor();
    delay(500);
    lcd.noCursor();
    delay(500);
  }
}

else if (digitalRead(Tombol_[1]) == LOW) {
  lcd.clear();
  delay(500);
  lcd.setCursor(15,1);
  lcd.blink();
  delay(500);
  lcd.noBlink();
  delay(500);

  for (int p = 12; p > 5; p--) {
    lcd.setCursor((p+2),1);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
    lcd.print(Prodi_[p]);
    lcd.setCursor((p+1),1);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
  }

  for (int q = 6; q > 0; q--) {
    lcd.setCursor(q,1);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
    lcd.print(Prodi_[q-1]);
    lcd.setCursor((q-1),1);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
  }
  
  for (int r = 13; r > 5; r--) {
    lcd.setCursor((r+2),0);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
    lcd.print(Nama_[r]);
    lcd.setCursor((r+1),0);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
  }

  lcd.setCursor(6,0);
  lcd.blink();
  delay(500);
  lcd.noBlink();
  delay(500);
  lcd.print(Nama_[5]);
  lcd.setCursor(5,0);
  lcd.blink();
  delay(500);
  lcd.noBlink();
  delay(500);

  for (int s = 5; s > 0; s--) {
    lcd.setCursor((s-1),0);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
    lcd.print(Nama_[s-1]);
    lcd.setCursor((s-2),0);
    lcd.blink();
    delay(500);
    lcd.noBlink();
    delay(500);
  }
  
}

else if (digitalRead(Tombol_[2]) == LOW) {
  lcd.clear();
  delay(500);
}
}
