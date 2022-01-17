#define MAX_DEPTH 2

//Deklarasi kelas I2C LCD 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

///////////// Rotary Encoder ////////////////////////
#define encB 5 //Pin A10
#define encA 6 //Pin A11
//this encoder has a button here
#define encBtn 7 //Pin A12

encoderIn<encA,encB> encoder;                                   //simple quad encoder driver
#define ENC_SENSIVITY 4
encoderInStream<encA,encB> encStream(encoder,ENC_SENSIVITY);    // simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};   //negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);                                 //1 is the number of keys

//input from the encoder + encoder button
//serialIn serial(Serial);
menuIn* inputsList[]={&encStream,&encButton,/* &serial */}; //tanpa serial input
chainStream<2> in(inputsList);//2 is the number of inputs

//Keluaran menu pada Serial dan LCD
MENU_OUTPUTS(out,MAX_DEPTH
  //,SERIAL_OUT(Serial)
  ,LCD_OUT(lcd,{0,0,16,2})
  ,NONE
);
