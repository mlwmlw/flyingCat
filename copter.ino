#include "Wire.h"
#include <L3G.h>
#include "gyro.h"
Gyro *gyro;
void setup() {
  Serial.begin(115200);
  Serial.println("test");
  gyro = new Gyro();
}

void loop() {
 
  gyro->read();
  
  Serial.print("x");
  Serial.println(gyro->getAngle(0));
  Serial.print("y");
  Serial.println(gyro->getAngle(1));
  Serial.print("z");
  Serial.println(gyro->getAngle(2));  
  delay(10);
}
