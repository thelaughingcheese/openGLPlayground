/*
contains a model and can be represented in the world
*/
#ifndef MODELENTITY
#define MODELENTITY

#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Model.h"

class ModelEntity: public Entity{
private:
	Model* model;

	glm::vec3 position;
	glm::quat orientation;	//euler
	glm::mat4 worldTransform;
public:
	static std::unordered_map<EntityID,ModelEntity*> modelEntities;

	ModelEntity(const char* modelName);
	~ModelEntity();

	void setPosition(glm::vec3 pos);
	glm::vec3 getPosition();

	void setOrientation(glm::quat ori);
	glm::quat getOrientation();

	void setModel(const char* modelName);
	Model* getModel();

	virtual void draw(glm::mat4& vp);
};

#endif