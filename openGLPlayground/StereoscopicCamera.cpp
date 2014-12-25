#include "StereoscopicCamera.h"
#include <glm/gtx/transform.hpp>

StereoscopicCamera::StereoscopicCamera(unsigned int w,unsigned int h,float f,glm::vec3 pos,glm::vec2 ori){
	setPos(pos);
	setOri(ori);
	setFov(f);
	setResolution(w,h);
}

void StereoscopicCamera::setPos(glm::vec3 pos){
	position = pos;
	leftCam.setPos(pos);
	rightCam.setPos(pos);
	
	glm::vec3 offset = glm::mat3(glm::rotate(glm::radians(orientation.x),glm::vec3(0,1,0))) * seperationVector;
	leftCam.setPos(position + offset);
	rightCam.setPos(position - offset);
}

glm::vec3 StereoscopicCamera::getPos(){
	return position;
}

void StereoscopicCamera::setOri(glm::vec2 ori){
	orientation = ori;
	leftCam.setOri(ori);
	rightCam.setOri(ori);
	
	glm::vec3 offset = glm::mat3(glm::rotate(glm::radians(orientation.x),glm::vec3(0,1,0))) * seperationVector;
	leftCam.setPos(position + offset);
	rightCam.setPos(position - offset);
}

glm::vec2 StereoscopicCamera::getOri(){
	return orientation;
}

void StereoscopicCamera::setFov(float f){
	fov = f;
	leftCam.setFov(f);
	rightCam.setFov(f);
}

float StereoscopicCamera::getFov(){
	return fov;
}

float StereoscopicCamera::getAspect(){
	return aspectRatio;
}

void StereoscopicCamera::setResolution(unsigned int w,unsigned int h){
	leftCam.setResolution(w,h);
	rightCam.setResolution(w,h);
	width = w;
	height = h;
	aspectRatio = float(width)/float(height);
}

unsigned int StereoscopicCamera::getWidth(){
	return width;
}

unsigned int StereoscopicCamera::getHeight(){
	return height;
}

void StereoscopicCamera::draw(){
	leftCam.draw();
	rightCam.draw();
}

GLuint StereoscopicCamera::getLeftRenderTexture(){
	return leftCam.getRenderTexture();
}

GLuint StereoscopicCamera::getRightRenderTexture(){
	return rightCam.getRenderTexture();
}

glm::vec3 StereoscopicCamera::getForwardVector(){
	return leftCam.getForwardVector();
}
glm::vec3 StereoscopicCamera::getRightVector(){
	return leftCam.getRightVector();
}
glm::vec3 StereoscopicCamera::getUpVector(){
	return leftCam.getUpVector();
}

void StereoscopicCamera::setSeperation(float sep){
	seperationVector = glm::vec3(sep,0,0);
}