const byte pinDigital_Out_[2] = {7,6};
const byte pinDigital_In = 8;
uint8_t i, j;
uint8_t Nilai_Masuk = 0;
uint8_t Nilai_Keluar_A = B11011010;
uint8_t Nilai_Keluar_B = B10010011;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  delay(1000);
  for (j = 0; j < 2; j++) pinMode(pinDigital_Out_[j], OUTPUT);
  pinMode(pinDigital_In, INPUT);
  for (i = 0; i < 8; i++)  {
    //LSBFIRST
      digitalWrite(pinDigital_Out_[0], !!(Nilai_Keluar_A & (1 << i))); //Shift Out
      digitalWrite(pinDigital_Out_[1], !!(Nilai_Keluar_B & (1 << i))); //Shift Out   
      Nilai_Masuk |= digitalRead(pinDigital_In) << i;            //Shift In
  }
  delay(1000);
  Serial.println("Data yang dikirim  (D7) : " + String(Nilai_Keluar_A, BIN));
  Serial.println("Data yang dikirim  (D6) : " + String(Nilai_Keluar_B, BIN));
  Serial.println("Data yang diterima (D8) : " + String(Nilai_Masuk, BIN));
}

// the loop routine runs over and over again forever:
void loop() {
}
