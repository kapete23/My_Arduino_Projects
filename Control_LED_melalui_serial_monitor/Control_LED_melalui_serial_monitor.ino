#include <SoftwareSerial.h>

SoftwareSerial SerialKu (6, 7);

const byte LED = 12;
void setup() {
  SerialKu.begin(9600);
  pinMode(LED, OUTPUT);
  while (!SerialKu) {
    //Tunggu arduiono terhubung ke PC
  }
}

void loop() {
  if (SerialKu.available()) {
    char msk = SerialKu.read();
    if (msk == 'a') digitalWrite(LED, HIGH);
    if (msk == 'b') digitalWrite(LED, LOW);
  }
}
