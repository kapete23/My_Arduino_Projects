#include <IRremote.h> 

// pin Signal ke pin 2 
const byte PIN_RECV = 2;
 
// konfigurasi class irremote
IRrecv irrecv(PIN_RECV);
// penampung hasil identifikasi remote
decode_results results;

void setup() {
  // buka koneksi ke serial monitor
    Serial.begin(19200); 
    // aktifkan IR penerima
    irrecv.enableIRIn();
}

void loop() {
  // jika menerima data dan berhasil mendecode data 
    if (irrecv.decode(&results)) {
        // cetak ke serial monitor dg format Hex 
        Serial.println(results.value, HEX);
        // hapus history hasil sebelumnya 
        irrecv.resume();
    } 
}
