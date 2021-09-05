const int LED1 = 8;

const int LED2 = 7;

int timeDelay = 1000;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  while(timeDelay > 100) {
    digitalWrite(LED1, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    delay(200);
    timeDelay = timeDelay - 100;
  }

  digitalWrite(LED2, HIGH);
  delay(5000);

  while(timeDelay < 1000) {
    digitalWrite(LED2, HIGH);
    delay(100);
    digitalWrite(LED2, LOW);
    delay(100);

    timeDelay = timeDelay + 100;
  }
  
  digitalWrite(LED1, HIGH);
  delay(5000);
}
