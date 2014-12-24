#include "Imu.h"
#include <iostream>

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
	float dps = (float(glm::length(localRotAxis))/32768)*(250*deltaTime/1000000.0f);

	float verticalAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(0,-1,0),accel)/glm::length(accel)));
	model->setOrientation(glm::angleAxis(glm::radians(verticalAngle),glm::normalize(accelProj)));

	glm::vec3 rotAxis = model2->getOrientation() * localRotAxis;
	glm::vec3 yAngleTest = (glm::toMat3(glm::angleAxis(glm::radians(dps),glm::normalize(rotAxis))* model2->getOrientation()) * glm::vec3(1,0,0));
	float yAngle = glm::acos(glm::dot(glm::vec3(yAngleTest.x,0,yAngleTest.z),glm::vec3(1,0,0)));
	if(yAngleTest.z > 0) yAngle = -yAngle;
	std::cout << yAngleTest.x << ", "<< yAngleTest.z << std::endl;
	glm::quat quat = glm::mix(glm::angleAxis(glm::radians(dps),glm::normalize(rotAxis)) * model2->getOrientation(),
							  glm::angleAxis(yAngle,glm::vec3(0,1,0))*glm::angleAxis(glm::radians(verticalAngle),glm::normalize(accelProj)),
							  0.02f);
	model2->setOrientation(quat);
}