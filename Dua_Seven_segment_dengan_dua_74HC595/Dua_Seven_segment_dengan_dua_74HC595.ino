#define OFF ~255

// konversi angka
// 8 bit data : A B C D E F G DP
const byte Angka[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B00000010  // -
};
// konfigurasi pin Arduino
const byte LatchPin = 7;  // ST_CP
const byte DataPin = 6;   // data
const byte ClockPin = 5;  // SH_CP
// jumlah digit single seven segment
const byte jumlah_digit = 2;
// data counter
int counter = 0;

void setup() {
  // konfigurasi pin sebagai ouput
  pinMode(LatchPin, OUTPUT);
  pinMode(ClockPin, OUTPUT);
  pinMode(DataPin, OUTPUT);
  // pastikan seven segment mati
  // mulai transfer
  digitalWrite(LatchPin, LOW);
  // kirim data
  shiftOut(DataPin, ClockPin, LSBFIRST, OFF);
  // stop transfer
  digitalWrite(LatchPin, HIGH);
}

void loop() {
  // delay 200ms
  if ( nonblocking_delay(200) ){
    counter++;
    if( counter >= 100 ) counter = 0;
    // cetak angka
    PrintDigit(counter, jumlah_digit);
    }
}

// fungsi untuk mencetak angka
// INPUT : angka dan jumlah_digit
void PrintDigit(int angka, byte jumlah_digit){
  // konversi angka jadi string
  String numstr = String(angka);
  byte lenstr = numstr.length();
  // mulai transfer
  digitalWrite(LatchPin, LOW);
  // kirim data sesuai index angka
  for(byte i=0; i<jumlah_digit; i++){
    if( i < lenstr ){
      // jika jumlah digit < jumlah angka
      // cetak angka pada digit tersebut
      byte posisi = (lenstr-i-1);
      byte angka = (numstr.substring(posisi,posisi+1)).toInt();
      shiftOut(DataPin, ClockPin, LSBFIRST, Angka[ angka ]);
      } else {
        // jika tidak, matikan digit seven segment
        shiftOut(DataPin, ClockPin, LSBFIRST, OFF);
        }
  }
  // stop transfer
  digitalWrite(LatchPin, HIGH);
}

// tambahan untuk membuat delay non blocking
unsigned long nonblocking_time = millis();
unsigned long nonblocking_last = millis();
boolean nonblocking_delay(long milidetik){
  nonblocking_time = millis();
  if(nonblocking_time - nonblocking_last >= milidetik){
    nonblocking_last = nonblocking_time;
    return true;
  }
  return false;
}
