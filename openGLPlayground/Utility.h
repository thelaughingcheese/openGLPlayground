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

namespace Utility{
	extern GLuint basicShaderProgram;
	extern GLuint mvpUniform;
	extern GLuint baseTextureUniform;
	
	extern Camera* curCamera;

	void initShaders();

	EntityID getNewEntityID();

	void trackEntity(Entity* ent);
	void untrackEntity(EntityID id);
	void untrackEntity(Entity* ent);

	Entity* getEntityByID(EntityID id);

	Model* getModel(const char* modelName);
	GLuint getTexture(const char* textureName);
}

#endif