void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(3)) Serial.println("ON");
}
