#include "Arduino.h"
#include "Wire.h"
#include <L3G.h>
#include "gyro.h"
Gyro::Gyro()
{
  
  Wire.begin();
  if (!gyro.init())
  {
    //Serial.println("Failed to autodetect gyro type!");
    //while (1);
  }
  gyro.enableDefault();
  for(int i = 0; i < 3; i++) {
    offset[i] = 0;
    noise[i] = 0;
    angle[i] = 0;
    rate[i] = 0;
    int sampleNum = 200;
    for(int n = 0; n < sampleNum; n++){
      gyro.read();
      if( i == 0) {
        offset[i] += (int) gyro.g.x;
      } else if( i == 1 ) {
        offset[i] += (int) gyro.g.y;
      } else if( i == 2 ) {
        offset[i] += (int) gyro.g.z;
      }
    }
    offset[i] /= sampleNum;
    int val = 0;
    for(int n = 0; n < sampleNum; n++){
      gyro.read();
      if( i == 0) {
        val = gyro.g.x - offset[i];
      } else if( i == 1 ) {
        val = gyro.g.y - offset[i];
      } else if( i == 2 ) {
        val = gyro.g.z - offset[i];
      }
      if(val - offset[i] > noise[i])
        noise[i] = val - offset[i];
      else if(val - offset[i] < -noise[i])
        noise[i] = -val - offset[i];
    }
    noise[i] = noise[i] / 100;
  }
}

void Gyro::read() {
  
  gyro.read();
  int rate;
  for(int i = 0; i < 3; i++) {
    if( i == 0 ) {
       rate = (gyro.g.x - offset[i]) / 100;
    } else if( i == 1 ) {
      rate = (gyro.g.y - offset[i]) / 100;  
    } else if( i == 2 ) {
      rate = (gyro.g.z - offset[i]) / 100;
    }
    
    if(rate >= noise[i] || rate <= -noise[i])
      angle[i] += ((double)(rate[i] + rate) * 10) / 2000;
    // remember the current speed for the next loop rate integration.
    rate[i] = rate;
    if(angle[i] >= 360)
      angle[i] -= 360;
    else if(angle[i] < 0)
      angle[i] += 360;
  }
}
int Gyro::getAngle(int x) {
  return angle[x];  
}
/*
int16_t avx, avy, avz;
int rate;
int prev_rate=0;
double angle=0;
void loop() {

  gyro.read();
  rate = (gyro.g.x - dc_offset) / 100;
  if(rate >= noise || rate <= -noise)
    angle += ((double)(prev_rate + rate) * 10) / 2000;
  // remember the current speed for the next loop rate integration.
  prev_rate = rate;
  if(angle >= 360)
    angle -= 360;
  else if(angle < 0)
    angle += 360;
  //float degree = (gyro.g.z * .85)/100
  Serial.print("rate: ");
  Serial.println(rate);
  Serial.print("angle: ");
  Serial.println((int)angle);
 Serial.print("G ");
   Serial.print(" ");
   Serial.print((int)gyro.g.x);
   Serial.print(" ");
   Serial.print((int)gyro.g.y);
   Serial.print(" ");
   Serial.print((int)gyro.g.z);
   Serial.println("");
  delay(10);
}*/


