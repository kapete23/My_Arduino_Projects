#include <LiquidCrystal_I2C.h>
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <EEPROM.h>

const byte PIN_RECV = 2;
// konfigurasi class irremote
IRrecv irrecv(PIN_RECV);
// penampung hasil identifikasi remote
decode_results results;

// data tombol (Remote Toshiba DVD)
#define TOMBOL_1 0x22B3807F
#define TOMBOL_2 0x22B340BF
#define TOMBOL_3 0x22B3C03F
#define TOMBOL_4 0x22B320DF
#define TOMBOL_5 0x22B3A05F
#define TOMBOL_6 0x22B3609F
#define TOMBOL_7 0x22B3E01F
#define TOMBOL_8 0x22B310EF
#define TOMBOL_9 0x22B3906F
#define TOMBOL_0 0x22B350AF
#define TOMBOL_>=10 0x22B3D02F
#define TOMBOL_Digest 0x22B3A45B
#define TOMBOL_Open/Close 0x22B3AF50
#define TOMBOL_PBC 0x22B3E817
#define TOMBOL_RET 0x22B32CD3
#define TOMBOL_ZOOM 0x22B324DB
#define TOMBOL_Program 0x22B33AC5
#define TOMBOL_Cancel 0x22B3F708
#define TOMBOL_Repeat 0x22B304FB
#define TOMBOL_GoTo 0x22B3A15E
#define TOMBOL_SoundSelector 0x22B3CA35
#define TOMBOL_Surround 0x22B32AD5
#define TOMBOL_Keyb 0x22B38D72
#define TOMBOL_key# 0x22B30DF2
#define TOMBOL_Random 0x22B3C43B
#define TOMBOL_OSD 0x22B330CF
#define TOMBOL_Time 0x22B36897
#define TOMBOL_Pause 0x22B38877
#define TOMBOL_Frame/Slow 0x22B300FF
#define TOMBOL_Resume 0x22B344BB
#define TOMBOL_Rew 0x22B39867                // Star
#define TOMBOL_PlaySelect 0x22B3A857         // Panah ke atas
#define TOMBOL_FF 0x22B3C837                 // OK
#define TOMBOL_Prev 0x22B39C63               // Panah ke kiri
#define TOMBOL_Stop 0x22B328D7               // panah ke bawah
#define TOMBOL_Next 0x22B3CC33               // Panah ke kanan

// alamat untuk menyimpan status backlight
#define ADDR_BACKLIGHT 0
#define ADDR_ARAH 1
#define BACKLIGHT_ON HIGH
#define BACKLIGHT_OFF !BACKLIGHT_ON

// jumlah kolom dan baris LCD (16x2)
#define LCD_COL 16
#define LCD_ROW 2

// LCD1602 dengan Modul I2C
// Alamat I2C di 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// status backlight LCD
boolean backlight = BACKLIGHT_ON;

// karakter di LCD
byte mangap_arr[] = {
  B00000,
  B01110,
  B01011,
  B11111,
  B00011,
  B10011,
  B01110,
  B00000
};

byte mingkem_arr[] = {
  B00000,
  B01110,
  B01011,
  B11111,
  B11111,
  B01111,
  B00000,
  B00000
};

#define ARAH_DIAM 0
#define ARAH_KIRI 1
#define ARAH_KANAN 2
#define ARAH_ATAS 3
#define ARAH_BAWAH 4

byte arah = ARAH_DIAM;
boolean Nganga = false;
byte Nganga_counter = 0;
const byte Nganga_pindah = 2;
int posisi_baris = 0;
int posisi_kolom = 0;

void setup() {
  // buka koneksi ke serial monitor
  Serial.begin(19200);
  // Settingan LCD
  lcd.init();                 
  lcd.init();
  lcd.begin(LCD_COL,LCD_ROW);
  
  // baca informasi status backlight terakhir
  backlight = EEPROM.read(ADDR_BACKLIGHT);
  // jika backlight > 1 reset ke 1
  if( backlight > 1) backlight = 1;
  // baca informasi arah gerakan
  arah = EEPROM.read(ADDR_ARAH);
  // jika arah > 4, maka diam
  if( arah > ARAH_BAWAH) arah = ARAH_DIAM;
  
  // buat karakter baru
  lcd.createChar(0, mingkem_arr);
  lcd.createChar(1, mangap_arr);
  // Nyalakan Backlight
  lcd.setBacklight(backlight);
  
  // aktifkan penerima infrared
  irrecv.enableIRIn();
}

void loop() {
  // jika menerima data dan berhasil mendecode data
  if(irrecv.decode(&results)) {
    // cetak ke serial monitor dg format Hex
    Serial.println(results.value, HEX);
    // eksekusi aksi sesuai tombol yang dipilih
    IRAction(results.value);
    // hapus history hasil sebelumnya
    irrecv.resume();
  }
  
  // gerakkan karakter lcd
  MoveChar();
}

// fungsi aksi penekanan tombol
void IRAction(unsigned long tombol){
  // ketika anti arah atau ganti mode backlight
  // simpan data ke EEPROM
  switch(tombol){
    // setting backlight
    case TOMBOL_Rew:         // Tombol Star
      // balik logika backlight
      backlight = !backlight;
      lcd.setBacklight(backlight);
      // simpan konfigurasi backlight
      EEPROM.write(ADDR_BACKLIGHT,backlight);
      break;
    case TOMBOL_PlaySelect: // Tombol Atas
      arah = ARAH_ATAS;
      EEPROM.write(ADDR_ARAH,arah);
      break;
    case TOMBOL_Stop:        // Tombol Bawah
      arah = ARAH_BAWAH;
      EEPROM.write(ADDR_ARAH,arah);
      break;
    case TOMBOL_FF:          // Tombol OK
      arah = ARAH_DIAM;
      EEPROM.write(ADDR_ARAH,arah);
      break;
    case TOMBOL_Prev:        // Tombol Kiri
      arah = ARAH_KIRI;
      EEPROM.write(ADDR_ARAH,arah);
      break;
    case TOMBOL_Next:        // Tombol Kanan
      arah = ARAH_KANAN;
      EEPROM.write(ADDR_ARAH,arah);
      break;
  }
}

// fungsi untuk menggerakkan karakter di lcd
void MoveChar(){
  // animasi menanga setiap 150ms
  if( nonblocking_delay(150) ){
    // balik logika kondisi nganga
    Nganga = !Nganga;
    
    // bersihkan lcd, kemudian set posisi kursor
    lcd.clear();
    lcd.setCursor(posisi_kolom, posisi_baris);

    // jika ngaga = true
    // tampilkan karakter menganga
    // jika false, tampilkan karakter biasa
    if( Nganga == true ){
      lcd.write(byte(0));
    } else {
      lcd.write(byte(1));
    } 
    
    // setiap jumlah nganga = nganga_pindah
    // maka mindah posisi karakter
    if ( Nganga_counter == Nganga_pindah ){
      // pindah posisi karakter sesuai
      // dengan arah yang dipilih tombol remote
      PilihArah(arah);
      Nganga_counter = 0;
    } else {
      Nganga_counter++;
    }
  }
}

// fungsi untuk memilih arah gerakan
void PilihArah(byte arah){
  switch(arah){
    case ARAH_KANAN:
      // jika arah kanan, tambah posisi kolom
      // jika posisi melebihi jumlah kolom,
      // kembali ke 0
      posisi_kolom++;
      if(posisi_kolom >= LCD_COL){
        posisi_kolom = 0;
      }
      break;
    case ARAH_KIRI:
      // jika arah kiri, kurangi posisi kolom
      // jika posisi < posisi 0
      // kembali ke kanan (posisi LCD_COL-1)
      posisi_kolom--;
      if(posisi_kolom < 0){
        posisi_kolom = LCD_COL-1;
      }
      break;
    case ARAH_ATAS:
      // jika arah atas, kurangi posisi baris
      // ingat, 0 ada di atas
      // jika posisi lebih kecil 0,
      // kembali ke index row (LCD_ROW-1)
      posisi_baris--;
      if(posisi_baris < 0){
        posisi_baris = LCD_ROW-1;
      }
      break;
    case ARAH_BAWAH:
      // jika arah bawah, tambah posisi baris
      // jika posisi melebihi jumlah baris,
      // kembali ke 0
      posisi_baris++;
      if(posisi_baris >= LCD_ROW){
        posisi_baris = 0;
      }
    break;
  }
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
