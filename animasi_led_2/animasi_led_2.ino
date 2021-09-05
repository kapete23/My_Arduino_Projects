const int pinLED = 8;

int timeDelay = 1000;

void setup() {
  pinMode(pinLED, OUTPUT);
}

void loop() {
  timeDelay = timeDelay - 100;

  if(timeDelay <= 100) {
    delay(5000);
    timeDelay = 1000;
  }
  else {
    timeDelay = timeDelay - 100;
  }

  digitalWrite(pinLED, HIGH);
  delay(timeDelay);
  digitalWrite(pinLED, LOW);
  delay(timeDelay);

}
