#include <pitches.h>

const int pinSpeaker = 8;

#define JUMLAH_NADA 85

const int daftar_nada[JUMLAH_NADA] = {
  NOTE_G4, NOTE_G4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_D5, 
      NOTE_E5, 0,
  NOTE_E5, NOTE_F5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, 
      NOTE_F5, NOTE_D5, 0,
  NOTE_G4, NOTE_G4, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_E5, 
      NOTE_F5, 0,
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4, NOTE_G4, NOTE_G4, 
      NOTE_A4, NOTE_B4, NOTE_C5, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_F5, 
      NOTE_G5, NOTE_A5, NOTE_G5, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_F5, 
      NOTE_G5, NOTE_A5, NOTE_G5, 0,
  NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_G4, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_E5, 0,
  NOTE_C5, NOTE_C5, NOTE_A5, NOTE_G5, NOTE_B4, NOTE_C5, 0
};

const int lama_beat = 150;
const int beats[JUMLAH_NADA] = {
  1, 1, 2, 2, 2, 2, 3, 1,
  1, 1, 2, 1, 1, 2, 2, 3, 1,
  1, 1, 2, 2, 2, 2, 3, 1,
  1, 1, 2, 1, 1, 2, 1, 1, 3, 1,
  1, 1, 2, 1, 1, 2, 1, 1, 3, 1,
  1, 1, 2, 1, 1, 2, 1, 1, 3, 1,
  2, 3, 1, 2, 2, 3, 1,
  1, 1, 1, 3, 1, 1, 1,
  1, 1, 1, 3, 1, 1, 1,
  2, 2, 2, 3, 1, 3, 0
};

void setup() {
  pinMode(pinSpeaker, OUTPUT);
}

void loop() {
  for(int i=0; i<JUMLAH_NADA; i++){
    if(nada[i] == 0){
      delay(beats[i] * lama_beat);
    }else{
      nada(daftar_nada[i], beats[i] * lama_beat);
    }
    // jeda antar nada
    noTone(pinSpeaker);
    delay(lama_beat / 2);
  }
}

void nada(int frek, int durasi){
  tone(pinSpeaker, frek, durasi);
  delay(durasi);
}
