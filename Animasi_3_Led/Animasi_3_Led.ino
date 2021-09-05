const int LED_1 = 9;

const int LED_2 = 8;

const int LED_3 = 6;

const int Button_1 = 2;

const int Button_2 = 4;

const int Button_3 = 12;

const int Pot = A3;

int KontrasLED1 = 0;

int KontrasLED3 = 0;

int Sensor = 0;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  
  pinMode(Button_1, INPUT);
  pinMode(Button_2, INPUT);
  pinMode(Button_3, INPUT);

  digitalWrite(Button_1, HIGH);
  digitalWrite(Button_2, HIGH);
  digitalWrite(Button_3, HIGH);
}

void loop() {
  if(digitalRead(Button_1) == LOW) {
    KontrasLED1++;
  }

  else if(digitalRead(Button_3) == LOW) {
    KontrasLED1--;
  }

  KontrasLED1 = constrain(KontrasLED1, 0, 255);

  analogWrite(LED_1, KontrasLED1);
  delay(10);

  Sensor = analogRead(Pot);

  KontrasLED3 = map(Sensor, 0, 1023, 0, 255);

  analogWrite(LED_3, KontrasLED3);
}

