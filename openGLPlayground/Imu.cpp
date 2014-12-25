#include "Imu.h"
#include <iostream>
#include <iomanip> 
#include <glm/gtx/string_cast.hpp>

Imu::Imu(char* port,ModelEntity& ent,ModelEntity& ent2,ModelEntity& ent3,ModelEntity& ent4){
	model = &ent;
	model2 = &ent2;
	model3 = &ent3;
	model4 = &ent4;
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
	float dps = (float(glm::length(localRotAxis))/32768)*(350*deltaTime/1000000.0f);

	float verticalAngle = glm::degrees(glm::acos(glm::dot(glm::vec3(0,-1,0),accel)/glm::length(accel)));
	//model->setOrientation(glm::angleAxis(glm::radians(verticalAngle),glm::normalize(accelProj)));

	glm::vec3 accelCross = glm::normalize(glm::cross(accel,glm::vec3(0,-1,0)));
	if(verticalAngle < 25 || verticalAngle > 155){
		accelCross = glm::vec3(0,0,-1);
	}

	//accelCross = glm::vec3(1,0,0);
	glm::vec3 rotAxis = model2->getOrientation() * localRotAxis;
	glm::vec3 yAngleTest = (glm::toMat3( model2->getOrientation()) * accelCross);
		yAngleTest = glm::normalize(glm::vec3(yAngleTest.x,0,yAngleTest.z));

	glm::quat accelQuat = glm::angleAxis(glm::radians(verticalAngle),glm::normalize(accelProj));
	glm::vec3 accelTest = glm::toMat3(accelQuat)*accelCross;
		accelTest = glm::normalize(glm::vec3(accelTest.x,0,accelTest.z));
	float yAngle = glm::acos(glm::dot(yAngleTest,glm::vec3(1,0,0)));
	float accelAngle = glm::acos(glm::dot(accelTest,glm::vec3(1,0,0)));
	if(yAngleTest.z > 0) yAngle = -yAngle;
	if(accelTest.z > 0) accelAngle = -accelAngle;
	yAngle -= accelAngle;
	
	glm::quat quat = glm::mix(glm::angleAxis(glm::radians(dps),glm::normalize(rotAxis)) * model2->getOrientation(),
							  glm::angleAxis(yAngle,glm::vec3(0,1,0))*accelQuat,
							  0.04f);
	//quat = glm::angleAxis(glm::radians(45.0f),glm::vec3(0,1,0));
	model2->setOrientation(quat);
	model2->setPosition(glm::vec3(-0,0,0));
	model->setPosition(glm::vec3(-100,0,0));

	model->setOrientation(glm::angleAxis(yAngle,glm::vec3(0,1,0)) * accelQuat);
	model3->setPosition( (yAngleTest*10.0f));

	model4->setPosition(glm::angleAxis(yAngle,glm::vec3(0,1,0)) *accelTest*12.0f);

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