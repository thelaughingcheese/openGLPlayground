#ifndef IMU
#define IMU

#include "Serial.h"
#include "ModelEntity.h"

class Imu{
private:
	short ax,ay,az,t,gx,gy,gz;
	Serial* serial;
	ModelEntity* model;
public:
	Imu(char* port, ModelEntity* ent);
	~Imu();
	void update();
};

#endif