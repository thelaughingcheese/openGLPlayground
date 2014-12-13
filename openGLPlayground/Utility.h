/*
utilities:
entity creation
entity distruction
*/
#ifndef UTILITY
#define UTILITY

#include <glm/glm.hpp>
#include "Model.h"
#include "Entity.h"

namespace Utility{
	EntityID getNewEntityID();

	Entity* createEntity();
	void destroyEntity();

	Entity* getEntityByID(EntityID id);

	Model* getModel(const char* modelName);
	GLuint getTexture(const char* textureName);
}

#endif