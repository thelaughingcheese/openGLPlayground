#ifndef IMU
#define IMU

#include "Serial.h"
#include "ModelEntity.h"

class Imu{
private:
	short ax,ay,az,t,gx,gy,gz;
	unsigned long deltaTime;
	Serial* serial;
	ModelEntity* model,*model2;
public:
	Imu(char* port,ModelEntity& ent,ModelEntity& ent2);
	~Imu();
	void update();
};

#endif