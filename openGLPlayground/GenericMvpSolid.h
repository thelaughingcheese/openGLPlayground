#ifndef GENERICMVPSOLID
#define GENERICMVPSOLID

#include "Material.h"
#include "Texture2D.h"
#include <glm/glm.hpp>

class GenericMvpSolid: public Material{
private:
	static GLuint MVPId;
	static GLuint colourId;

	glm::vec3 colour;
public:
	static void initMaterial();
	static void unloadMaterial();

	GenericMvpSolid();

	void loadUniforms(glm::mat4& mvp);
	void loadMaterialData(std::string& data);
};

#endif