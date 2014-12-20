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
#include "Camera.h"
#include "Material.h"

namespace Utility{
	extern Camera* curCamera;

	void initShaders();
	void unloadShaders();

	EntityID getNewEntityID();

	void trackEntity(Entity* ent);
	void untrackEntity(EntityID id);
	void untrackEntity(Entity* ent);

	Entity* getEntityByID(EntityID id);

	Model* getModel(const char* modelName);
	GLuint getTexture(const char* textureName);

	Material* loadMaterialFromFile(const char* materialName);

	void unloadModels();
	void unloadTextures();
}

#endif