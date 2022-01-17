void TSensor();
//void(*reset_Arduino) (void) = 0; //perintah reset arduino

//Creats a noDelay varible set to 650ms, 200ms, 150ms dan 90ms.
//noDelay TimeD1(650),TimeD2(200),TimeD3(150);
//noDelay TscreenSaver(90,tampilanAwal);

struct setDHT {
  byte humi[2];
  float temp[2];
  int tunda;
} dataSet, ds, *dsPtr;

bool chk[2]={0,0};

unsigned long currentMillis, previousMillis = 0;

result saveData(navNode& nav) {
  //menuNode& target = *nav.target;
  navRoot& root = *nav.root;
  byte b, a = root.path[0].sel; //Menu Utama
  
  ds = *dsPtr;
  EEPROM.get(0, dataSet);

  switch(a) {// Check perubahan data
    case 0: {//Set Temperatur
        for(b = 0; b < 2; b++) {
          if (dataSet.temp[b] != ds.temp[b]) {
            chk[0] = 1; // Salah satu data mengalami perubahan
            break;
          }
          chk[0] = 0;   // Data tidak mengalami perubahan
        }
        break;}
    case 1: {//Set Humidity
        for(b = 0; b < 2; b++) {
          if (dataSet.humi[b] != ds.humi[b]) {
            chk[0] = 1; // Salah satu data mengalami perubahan
            break;
          }
          chk[0] = 0;   // Data tidak mengalami perubahan
        }
        break;}
    case 2: {//Set Tunda
        if (dataSet.tunda != ds.tunda) chk[0] = 1;  // Salah satu data mengalami perubahan
        else chk[0] = 0;                            // Data tidak mengalami perubahan 
        break;}
  }

  if (chk[0]) {
    EEPROM.put(0, ds);
    EEPROM.get(0, dataSet);
  }
  
  return proceed;
}

byte charCustom[4][8] = {
{ 0b01000, //[0] Karakter segitiga
  0b00100, // Alamat karakter pada LCD2002 : lcd.print('\x08'); 
  0b10010,
  0b11001,
  0b10010,
  0b00100,
  0b01000,
  0b00000
  },
{ 0b11111, //[1] Karakter scroll bar 'n'
  0b11111, // Alamat karakter pada LCD2002 : lcd.print('\x09');
  0b11111,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001
  },
{ 0b10001, //[2] Karakter scroll bar '| |'
  0b10001, // Alamat karakter pada LCD2002 : lcd.print('\x0A');
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001
  },
{ 0b10001, //[3] Karakter scroll bar 'u'
  0b10001, // Alamat karakter pada LCD2002 : lcd.print('\x0B');
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b11111,
  0b11111
  }
};/*
{ 0b11111, //[4] Karakter 'bukan x' 
  0b00000, // Alamat karakter pada LCD2002 : lcd.print('\x0C');
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000
  },
{ 0b10000, //[5] Karakter '├>'
  0b10100, // Alamat karakter pada LCD2002 : lcd.print('\x0D');
  0b10110,
  0b11111,
  0b10110,
  0b10100,
  0b10000,
  0b10000
  },
{ 0b00001, //[6] Karakter '<┤' 
  0b00101, // Alamat karakter pada LCD2002 : lcd.print('\x0E');
  0b01101,
  0b11111,
  0b01101,
  0b00101,
  0b00001,
  0b00001
  },
{ 0b10000, //[7] Karakter '└>'
  0b10100, // Alamat karakter pada LCD2002 : lcd.print('\x0F');
  0b10010,
  0b11111,
  0b00010,
  0b00100,
  0b00000,
  0b00000
  }
};
*/

//////Scroll Bar (Custom Char LCD 20x2)/////////
/*
const byte charCustom[][8] = {
 
   { 0b11111, //[0] Scroll bar atas
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001
   },
   { 0b11111, //[1] Scroll bar atas pertama
     0b10001,
     0b11111,
     0b11111,
     0b10001,
     0b10001,
     0b10001,
     0b10001
   },
   { 0b11111, //[2] Scroll bar atas kedua
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b11111,
     0b11111,
     0b10001
   },
   { 0b11111, //[3] Scroll bar atas ketiga
     0b11111,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b11111
   },
   { 0b11111, //[4] Scroll bar bawah pertama
     0b11111,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b11111
   },
   { 0b10001, //[5] Scroll bar bawah kedua
     0b10001,
     0b11111,
     0b11111,
     0b10001,
     0b10001,
     0b10001,
     0b11111
   },
   { 0b10001, //[6] Scroll bar bawah ketiga
     0b10001,
     0b10001,
     0b10001,
     0b11111,
     0b11111,
     0b10001,
     0b11111
   },
   { 0b10001, //[7] Scroll bar bawah
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b10001,
     0b11111
   }
};*/
