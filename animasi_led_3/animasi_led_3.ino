const int PinLED = 8;

int timeDelay = 1000;

void setup() {
  pinMode(PinLED, OUTPUT); 
}

void loop() {
  while(timeDelay > 0) {
    digitalWrite(PinLED, HIGH);
    delay(100);
    digitalWrite(PinLED, LOW);
    delay(100);

    timeDelay = timeDelay - 100;
  }
  while(timeDelay < 1000) {
    digitalWrite(PinLED, HIGH);
    delay(1000);
    digitalWrite(PinLED, LOW);
    delay(1000);

    timeDelay = timeDelay + 100;
  }

}
