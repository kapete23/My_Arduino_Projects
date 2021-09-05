const int pinPot = A0;
const int pinLED = 9;
int sensor = 0;
int brightness = 0;

void setup() {
  pinMode(pinPot, INPUT);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  sensor = analogRead(pinPot);
  // konversi nilai 0-1023 (Analog) menjadi 0-255 (PWM)
  brightness = map(sensor, 0, 1023, 0, 255);
  analogWrite(pinLED, brightness);
}
