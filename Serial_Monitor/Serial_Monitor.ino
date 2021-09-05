void setup() {
  Serial.begin(9600);
  Serial.println("With elangsakti.com :");
}

int number = 0;
void loop() {
  Serial.print("Hello World! ");
  Serial.println( number++ );
  delay(1000);
} 
