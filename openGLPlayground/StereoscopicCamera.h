#ifndef STEREOSCOPICCAMERA
#define STEREOSCOPICCAMERA

#include "Camera.h"

class StereoscopicCamera{
private:
	unsigned int width,height;
	glm::vec3 position;
	glm::vec2 orientation;
	float fov,aspectRatio,nearClipping,farClipping;

	Camera leftCam,rightCam;
	//right
	glm::vec3 seperationVector;
public:
	StereoscopicCamera(unsigned int w = 1024,unsigned int h = 768,float f = 45.0,glm::vec3 pos = glm::vec3(0,0,0),glm::vec2 ori = glm::vec2(0,0));

	void setPos(glm::vec3 pos);
	glm::vec3 getPos();
	void setOri(glm::vec2 ori);
	glm::vec2 getOri();
	void setFov(float f);
	float getFov();
	void setAspect(float f);
	float getAspect();

	void setResolution(unsigned int w,unsigned int h);
	unsigned int getWidth();
	unsigned int getHeight();
	GLuint getLeftRenderTexture();
	GLuint getRightRenderTexture();

	glm::vec3 getForwardVector();
	glm::vec3 getRightVector();

	void draw();
	void setSeperation(float sep);
};

#endif