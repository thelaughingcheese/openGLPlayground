#include "Imu.h"
#include <iostream>
#include <iomanip> 
#include <glm/gtx/string_cast.hpp>
#include <limits>

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

Imu::Imu(char* port,ModelEntity& ent,ModelEntity& ent2){
	model = &ent;
	model2 = &ent2;
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
	char buffer[18];
	int count = 0;
	serial->WriteData(&a,1);
	while(count < 18){
		int read = serial->ReadData(&buffer[count],18);
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
	deltaTime = *((unsigned long*)&buffer[14]);

	glm::vec3 accel(-ax,-az,ay);
	glm::vec3 accelProj(accel.z,0,-accel.x);

	glm::vec3 localRotAxis(gx,gz,-gy);
	float dps = (float(glm::length(localRotAxis))/32768)*(500*deltaTime/1000000.0f);

	float verticalAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(0,-1,0),accel)/glm::length(accel)));
	glm::vec3 rotAxis = model2->getOrientation() * localRotAxis;
	glm::quat accelQuat = glm::angleAxis(glm::radians(verticalAngle),glm::normalize(accelProj));
	glm::vec3 rotationalConstraint = glm::toMat3(accelQuat) * glm::toMat3(glm::inverse(model2->getOrientation())) * glm::vec3(1,0,0);
		rotationalConstraint = glm::normalize(glm::vec3(rotationalConstraint.x,0,rotationalConstraint.z));
	float yAngle = glm::acos(MAX(MIN(glm::dot(glm::vec3(1,0,0),rotationalConstraint),1),-1));
	if(glm::cross(rotationalConstraint,glm::vec3(1,0,0)).y < 0){
		yAngle = -yAngle;
	}

	glm::quat quat = glm::slerp(glm::angleAxis(glm::radians(dps),glm::normalize(rotAxis)) * model2->getOrientation(),
							  glm::angleAxis(yAngle,glm::vec3(0,1,0))*accelQuat,
							  0.1f);
	model2->setOrientation(quat);
	model->setOrientation(glm::angleAxis(yAngle,glm::vec3(0,1,0))*accelQuat);

	//orientation kept on microcontroller
	//------------

	/*char a;
	char buffer[16];
	int count = 0;
	serial->WriteData(&a,1);
	while(count < 16){
		int read = serial->ReadData(&buffer[count],16);
		if(read < 0) read = 0;
		count += read;
	}

	float q[4];
	q[0] = *((float*)&buffer[0]);
	q[1] = *((float*)&buffer[4]);
	q[2] = *((float*)&buffer[8]);
	q[3] = *((float*)&buffer[12]);

	std::cout << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << "," << std::endl;

	model2->setOrientation(glm::quat(q[3],q[0],q[1],q[2]));*/
}