#include <Servo.h> 

// pwm servo di pin 3
// output potensi di pin A0 
const byte PIN_SERVO = 3;
const byte PIN_POTENSIO = A0; 

// objeck untuk class servo 
Servo myservo;
 
// sudut servo dan sudut maksimum
int posisi = 0; 
int SERVO_MAX = 180;
 
void setup() {
    // siapkan servo
    myservo.attach(PIN_SERVO);
} 

void loop() { 
    // posisikan servo sesuai data potensio
    int data = analogRead(PIN_POTENSIO); 
    // normalisasi data potensio sesuai sudut servo
    posisi = map( data, 0, 1024, 0, 180 ); 
    // kontrol servo
    myservo.write(posisi); 
} 
