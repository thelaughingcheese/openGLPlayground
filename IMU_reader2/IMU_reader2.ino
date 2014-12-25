#include <Serial.h>
#include <Wire.h>

#define MPU 0x68

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
unsigned long lastUpdate = 0;

float quat[4] = {0,0,0,1};

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6b);
  Wire.write(0);
  Wire.endTransmission(false);
  Wire.write(0x1b);
  Wire.write(8);
  Wire.endTransmission(true);
}

inline void multiplyQuat(float* a, float* b, float* c){
  float result[4];
  
  result[0] = a[3]*b[0] + a[0]*b[3] + a[1]*b[2] - a[2]*b[1];
  result[1] = a[3]*b[1] - a[0]*b[2] + a[1]*b[3] + a[2]*b[0];
  result[2] = a[3]*b[2] + a[0]*b[1] - a[1]*b[0] + a[2]*b[3];
  result[3] = a[3]*b[3] - a[0]*b[0] - a[1]*b[1] - a[2]*b[2];
  
  c[0] = result[0];
  c[1] = result[1];
  c[2] = result[2];
  c[3] = result[3];
}

void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3b);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,14,true);
  
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  Tmp=Wire.read()<<8|Wire.read();
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
  
  unsigned long delta = micros() - lastUpdate;
  lastUpdate = micros();
  
  /*float newQuat[4];
  float GyLen = sqrt(pow(GyX,2)+pow(GyY,2)+pow(GyZ,2));
  float deltaTime = delta*0.000001f;
  float angle = GyLen*500*deltaTime*3.1415926535897932384626433832795/5898240;
  float sinAngle = sin(angle/2);
  
  newQuat[0] = GyX*sinAngle/GyLen;
  newQuat[1] = GyZ*sinAngle/GyLen;
  newQuat[2] = -GyY*sinAngle/GyLen;
  newQuat[3] = cos(angle/2);
  
  multiplyQuat(quat,newQuat,quat);*/
  
  float AcLen = sqrt(pow(AcX,2)+pow(AcY,2)+pow(AcZ,2));
  float AcXZLen = sqrt(pow(AcX,2)+pow(AcY,2));
  float accelVerticalAngle = acos(AcZ/AcLen);
  float accelVerticalAngleSin = sin(accelVerticalAngle/2);
  quat[0] = (AcY/AcXZLen)*accelVerticalAngleSin;
  quat[1] = 0;
  quat[2] = (AcX/AcXZLen)*accelVerticalAngleSin;
  quat[3] = cos(accelVerticalAngle/2);
  
  if(Serial.available()){
    Serial.read();
    Serial.write((byte*)quat,16);
  }
}
