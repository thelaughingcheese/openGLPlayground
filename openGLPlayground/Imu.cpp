#include "Imu.h"
#include <iostream>

Imu::Imu(char* port,ModelEntity* ent){
	model = ent;
	serial = new Serial(port);

	if(!serial->IsConnected()){
		std::cout << "Serial Port Not connected" << std::endl;
	}
}

Imu::~Imu(){
	delete serial;
}

void Imu::update(){
	char a;
	char buffer[14];
	int count = 0;
	serial->WriteData(&a,1);
	while(count < 14){
		int read = serial->ReadData(&buffer[count],14);
		if(read < 0) read = 0;
		count += read;
	}

	ax = *((short*)&buffer[0]);
	ay = *((short*)&buffer[2]);
	az = *((short*)&buffer[4]);
	t = *((short*)&buffer[6]);
	gx = *((short*)&buffer[8]);
	gy = *((short*)&buffer[10]);
	gz = *((short*)&buffer[12]);

	std::cout << -ax << ",";
	std::cout << -az << ",";
	std::cout << ay << std::endl;

	glm::vec3 accel(-ax,-az,ay);
	glm::vec3 accelProj(-ax,0,ay);

	float verticalAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(0,-1,0),accel)/glm::length(accel)));
	float horizontalAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(-1,0,0),accel)/glm::length(accelProj)));
	if(accelProj.z < 0) horizontalAngle = -horizontalAngle;
	std::cout << verticalAngle << ", " << horizontalAngle << std::endl<<std::endl;
	model->setOrientation(glm::vec3(0,horizontalAngle,verticalAngle));
}