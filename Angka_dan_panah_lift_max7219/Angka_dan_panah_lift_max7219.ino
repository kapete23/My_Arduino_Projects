#include <MaxMatrix.h>

//MaxMatrix m(DIN, CS, CLK, Jumlah IC MAX7219);
MaxMatrix m(14, 13, 12, 1); 

unsigned char Panah_Atas[] = {8, 6,
                      B001000,
                      B001100,
                      B001110,
                      B111111,
                      B111111,
                      B001110,
                      B001100,
                      B001000
                    };
unsigned char Panah_Bawah[] = {8, 6,
                      B000100,
                      B001100,
                      B011100,
                      B111111,
                      B111111,
                      B011100,
                      B001100,
                      B000100
                     };
unsigned char Angka_1[] = {5, 7,
                  B1000100,
                  B1000010,
                  B1111111,
                  B1000000,
                  B1000000
                 };

unsigned char Angka_2[] = {5, 7,
                  B1000010,
                  B1100001,
                  B1010001,
                  B1001001,
                  B1000110
                 };
unsigned char Angka_3[] = {5, 7,
                  B0100010,
                  B1000001,
                  B1001001,
                  B1001001,
                  B0110110
                 };                 

void setup() {
  m.init(); // MAX7219 initialization
  m.setIntensity(5); // initial led matrix intensity, 0-15
}

void loop() {
  m.writeSprite(0, 1, Panah_Atas);
  delay(1000);
  for (int i=0; i<32; i++){
    m.shiftUp(true);
    delay(300);
  }
  m.clear();
  m.writeSprite(0, 1, Panah_Bawah);
  delay(1000);
  for (int j=0; j<32; j++){
    m.shiftDown(true);
    delay(300);
  }
  m.clear();
  m.writeSprite(2, 0, Angka_1);
  delay(8000);
  m.clear();
  m.writeSprite(2, 0, Angka_2);
  delay(8000); 
  m.clear();
  m.writeSprite(2, 0, Angka_3);
  delay(8000);
  m.clear();
}
