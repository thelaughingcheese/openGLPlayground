#include "ModelEntity.h"
#include "Utility.h"
#include <glm/gtx/transform.hpp>

ModelEntity::ModelEntity(const char* modelName){
	setModel(modelName);
	position = glm::vec3(0,0,0);
	orientation = glm::vec3(0,0,0);
}
ModelEntity::~ModelEntity(){

}

void ModelEntity::setPosition(glm::vec3 pos){
	position = pos;
	worldTransform = glm::translate(position) * 
		glm::rotate(glm::radians(orientation.x),glm::vec3(1,0,0)) * 
		glm::rotate(glm::radians(orientation.y),glm::vec3(0,1,0)) * 
		glm::rotate(glm::radians(orientation.z),glm::vec3(0,0,1));
}
glm::vec3 ModelEntity::getPosition(){
	return position;
}

void ModelEntity::setOrientation(glm::vec3 ori){
	orientation = ori;
	worldTransform = glm::translate(position) * 
		glm::rotate(glm::radians(orientation.x),glm::vec3(1,0,0)) * 
		glm::rotate(glm::radians(orientation.y),glm::vec3(0,1,0)) * 
		glm::rotate(glm::radians(orientation.z),glm::vec3(0,0,1));
}
glm::vec3 ModelEntity::getOrientation(){
	return orientation;
}

void ModelEntity::setModel(const char* modelName){
	model = Utility::getModel(modelName);
}
Model* ModelEntity::getModel(){
	return model;
}

void ModelEntity::draw(){
	glm::mat4 mvp = Utility::curCamera->getVPMatrix() * worldTransform;

	model->draw(mvp);
}