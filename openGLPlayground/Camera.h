/*
camera in opengl, has position and orientation (2 axis only)
*/
#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>

class Camera{
private:
	glm::vec3 position;
	glm::vec2 orientation;
	float fov,aspectRatio,nearClipping,farClipping;
	glm::mat3 orientationMatrix;
public:

	Camera(float f = 45.0,float asp = 4.0/3.0,glm::vec3 pos = glm::vec3(0,0,0),glm::vec2 ori = glm::vec2(0,0));

	void setPos(glm::vec3 pos);
	glm::vec3 getPos();
	void setOri(glm::vec2 ori);
	glm::vec2 getOri();
	void setFov(float f);
	float getFov();
	void setAspect(float f);
	float getAspect();

	glm::mat4 getProjectionMatrix();
	glm::vec3 getForwardVector();
	glm::vec3 getRightVector();
};

#endif