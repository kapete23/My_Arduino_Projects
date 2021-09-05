#include <SHT1x.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to the Arduino RX on pin 2. 
// Connect the HC-05 RX to the Arduino TX on pin 3 through a voltage divider.

#define dataPin  10
#define clockPin 11
SHT1x sht1x(dataPin, clockPin);
 
void setup() 
{
    Serial.begin(9600);
    Serial.println("Enter AT commands:");
 
    // HC-06 default serial speed is 9600
    BTserial.begin(38400);  
}
 
void loop()
{
    String output = "";
    String tokenizer = "@"; 
  
    // Keep reading from HC-06 and send to Arduino Serial Monitor
        if (BTserial.available())
        {  
          
          Serial.write(BTserial.read());
        }
 
    // Keep reading from Arduino Serial Monitor and send to HC-06
         //dummy data
          //BTserial.write("@");
          output.concat(tokenizer);
          if (sht1x.readTemperatureC() != -999.00 || sht1x.readHumidity() != -999.00){
                
              if(sht1x.readTemperatureC() != -999.00){
                  output.concat(sht1x.readTemperatureC());         
                  output.concat(";");  
              }
              if(sht1x.readHumidity() != -999.00){            
                output.concat(sht1x.readHumidity());        
                output.concat(";");
              }
              output.concat("0.00@");
          
              Serial.println(output);
              BTserial.write(output.c_str());
              //BTserial.write("@100.25;100.00;100.00@");
          }
          delay(10);
     delay(500);
}
