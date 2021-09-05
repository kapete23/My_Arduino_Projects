#include <LiquidCrystal_I2C.h>
#include <ZMPT101B.h>

ZMPT101B voltageSensor(A0);

void setup() {
  Serial.begin(9600);
  // calibrate() method calibrates zero point of sensor,
  // It is not necessary, but may positively affect the accuracy
  // Ensure that no current flows through the sensor at this moment
  // If you are not sure that the current through the sensor will not leak during calibration - comment out this method
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  delay(100);
  voltageSensor.calibrate();
  Serial.println("Done!");

}

void loop() {
  float U = voltageSensor.getVoltageAC();
  Serial.println(String("U = ") + U + " V");
  delay(1000);
 }
