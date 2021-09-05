#include <LiquidCrystal_I2C.h>
#include <L298N.h>

#define EN1 3
#define IN1 4
#define IN2 5
#define IN3 7
#define IN4 8
#define EN2 9

const int Pot = A0;
const int Tombol_Kiri  = 10;
const int Tombol_Kanan = 11;
const int Tombol_Stop  = 12;

L298N dinamo_kanan(EN1, IN1, IN2);
L298N dinamo_kiri(EN2, IN3, IN4);

LiquidCrystal_I2C layar(0x27,16,2);

void setup() {
  layar.init();
  layar.backlight();
  pinMode(Pot, INPUT);
  pinMode(Tombol_Kanan, INPUT_PULLUP);
  pinMode(Tombol_Kiri, INPUT_PULLUP);
  pinMode(Tombol_Stop, INPUT_PULLUP);
}

void loop() {
  String Arah;
  int sensor = analogRead(Pot);
  int kecepatan = map(sensor, 0, 1023, 0, 255);
  if (digitalRead(Tombol_Kanan) == HIGH) {
    dinamo_kanan.setSpeed(kecepatan);
    dinamo_kiri.forward();
    Arah = "Kanan";
  }
  else if (digitalRead(Tombol_Kiri) == HIGH) {
    dinamo_kanan.setSpeed(kecepatan);
    dinamo_kiri.backward();
     Arah = "Kiri";
  }
  else if (digitalRead(Tombol_Stop) == HIGH) dinamo_kiri.stop();
  layar.init();
  layar.setCursor(0,0);
  layar.print("Set_V = ");
  layar.setCursor(8,0);
  layar.print(kecepatan);
  layar.setCursor(0,1);
  layar.print("A_Putar : ");
  layar.setCursor(10,1);
  layar.print(Arah);
}
