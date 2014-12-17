/*
contains a model and can be represented in the world
*/
#ifndef MODELENTITY
#define MODELENTITY

#include "Entity.h"
#include <glm/glm.hpp>

#include "Model.h"

class ModelEntity: public Entity{
private:
	Model* model;

	glm::vec3 position;
	glm::vec3 orientation;	//euler
	glm::mat4 worldTransform;
public:
	ModelEntity(const char* modelName);
	~ModelEntity();

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();

	void setOrientation(glm::vec3 ori);
	glm::vec3 getOrientation();

	void setModel(const char* modelName);
	Model* getModel();

	virtual void draw();
};

#endif