#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "Utility.h"
#include "ModelEntity.h"
#include <iostream>

Camera::Camera(unsigned int w,unsigned int h,float f,glm::vec3 pos,glm::vec2 ori){
	position = pos;
	orientation = ori;
	fov = f;
	width = w;
	height = h;
	aspectRatio = float(width)/float(height);

	nearClipping = 0.1f;
	farClipping = 10000.0f;

	glGenFramebuffers(1,&frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);

	glGenRenderbuffers(1,&renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER,renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,w,h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,renderBuffer);

	glGenTextures(1,&renderTexture);
	glBindTexture(GL_TEXTURE_2D,renderTexture);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,w,h,0,GL_RGB,GL_UNSIGNED_BYTE,0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
}

Camera::~Camera(){
	glDeleteTextures(1,&renderTexture);
	glDeleteRenderbuffers(1,&renderBuffer);
	glDeleteFramebuffers(1,&frameBuffer);
}

void Camera::setPos(glm::vec3 pos){
	position = pos;
}

glm::vec3 Camera::getPos(){
	return position;
}

void Camera::setOri(glm::vec2 ori){
	orientation = ori;
	orientationMatrix = glm::mat3(glm::rotate(glm::radians(orientation.x),glm::vec3(0,1,0))) * glm::mat3(glm::rotate(glm::radians(orientation.y),glm::vec3(1,0,0)));
}

glm::vec2 Camera::getOri(){
	return orientation;
}

void Camera::setFov(float f){
	fov = f;
}

float Camera::getFov(){
	return fov;
}

void Camera::setAspect(float a){
	aspectRatio = a;
}

float Camera::getAspect(){
	return aspectRatio;
}

glm::mat4 Camera::getVPMatrix(){
	glm::vec3 lookAt = position + orientationMatrix * glm::vec3(0,0,-1);
	return glm::perspective(fov,aspectRatio,nearClipping,farClipping) * glm::lookAt(position,lookAt,glm::vec3(0,1,0));
}

glm::vec3 Camera::getForwardVector(){
	return orientationMatrix * glm::vec3(0,0,-1);
}

glm::vec3 Camera::getRightVector(){
	return orientationMatrix * glm::vec3(1,0,0);
}

GLuint Camera::getRenderTexture(){
	return renderTexture;
}

void Camera::draw(){
	glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,renderTexture,0);
	GLenum drawBuffers[1] ={GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1,drawBuffers);

	glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);

	std::unordered_map<EntityID,ModelEntity*>::iterator it = ModelEntity::modelEntities.begin();
	for(; it != ModelEntity::modelEntities.end(); it++){
		it->second->draw(getVPMatrix());
	}

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		std::cout << "Frame buffer not ok!" << std::endl;
	}
}