#include <Serial.h>
#include <Wire.h>

#define MPU 0x68

//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int16_t data[7];

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6b);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop(){
  while(!Serial.available()){ }
  
  Wire.beginTransmission(MPU);
  Wire.write(0x3b);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  
  data[0]=Wire.read()<<8|Wire.read();
  data[1]=Wire.read()<<8|Wire.read();
  data[2]=Wire.read()<<8|Wire.read();
  data[3]=Wire.read()<<8|Wire.read();
  data[4]=Wire.read()<<8|Wire.read();
  data[5]=Wire.read()<<8|Wire.read();
  data[6]=Wire.read()<<8|Wire.read();
  
  Serial.write((byte*)data,14);
  /*Serial.print(data[0]);Serial.write(",");
  Serial.print(data[1]);Serial.write(",");
  Serial.print(data[2]);Serial.write(",");
  Serial.print(data[3]);Serial.write(",");
  Serial.print(data[4]);Serial.write(",");
  Serial.print(data[5]);Serial.write(",");
  Serial.print(data[6]);Serial.write("\n");*/
  
  //flush
  while(Serial.available()){
    Serial.read();
  }
  //delay(10);
}
