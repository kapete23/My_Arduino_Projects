const int pinLED = 8;

void setup() {
  pinMode(pinLED, OUTPUT);

}

void loop() {
  digitalWrite(pinLED, HIGH);
  delay(5000);
  digitalWrite(pinLED, LOW);
  delay(5000);
}
