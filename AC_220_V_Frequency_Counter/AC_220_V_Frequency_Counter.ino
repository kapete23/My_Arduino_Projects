#include <LiquidCrystal_I2C.h>

int input = 0;
int high_time;
int low_time;
float time_period;
float frequency;

LiquidCrystal_I2C lcd (0x27,20,4);

void setup() {
  pinMode(input, INPUT);
  Wire.begin(5,4);
  lcd.init();
  lcd.backlight();
}

void loop() {
  high_time = pulseIn(input, HIGH);
  low_time = pulseIn(input, LOW);

  time_period = high_time + low_time;
  time_period = time_period / 1000;
  frequency = 1000 / time_period;
  
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("F = " + String(frequency, 2) + " Hz");
  delay(500);
}
