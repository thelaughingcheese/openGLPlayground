/*
camera in opengl, has position and orientation (2 axis only)
*/
#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <GL/glew.h>

class Camera{
private:
	unsigned int width,height;
	glm::vec3 position;
	glm::vec2 orientation;
	float fov,aspectRatio,nearClipping,farClipping;
	glm::mat3 orientationMatrix;

	GLuint frameBuffer;
	GLuint renderBuffer;
	GLuint renderTexture;
public:

	Camera(unsigned int w = 1024,unsigned int h = 768,float f = 45.0,glm::vec3 pos = glm::vec3(0,0,0),glm::vec2 ori = glm::vec2(0,0));
	~Camera();

	void setPos(glm::vec3 pos);
	glm::vec3 getPos();
	void setOri(glm::vec2 ori);
	glm::vec2 getOri();
	void setFov(float f);
	float getFov();
	void setAspect(float f);
	float getAspect();

	void setResolution(unsigned int w, unsigned int h);
	unsigned int getWidth();
	unsigned int getHeight();

	glm::mat4 getVPMatrix();
	glm::vec3 getForwardVector();
	glm::vec3 getRightVector();

	GLuint getRenderTexture();
	void draw();
};

#endif