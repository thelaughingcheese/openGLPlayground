#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>]
#include <iostream>

Camera::Camera(float f, float asp, glm::vec3 pos, glm::vec2 ori){
	position = pos;
	orientation = ori;
	fov = f;
	aspectRatio = asp;

	nearClipping = 0.1;
	farClipping = 10000.0;
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

glm::mat4 Camera::getProjectionMatrix(){
	glm::vec3 lookAt = position + orientationMatrix * glm::vec3(0,0,-1);
	return glm::perspective(fov,aspectRatio,nearClipping,farClipping) * glm::lookAt(position,lookAt,glm::vec3(0,1,0));
}

glm::vec3 Camera::getForwardVector(){
	return orientationMatrix * glm::vec3(0,0,-1);
}

glm::vec3 Camera::getRightVector(){
	return orientationMatrix * glm::vec3(1,0,0);
}