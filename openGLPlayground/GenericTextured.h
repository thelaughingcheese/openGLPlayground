
#ifndef GENERICTEXTURED
#define GENERICTEXTURED

#include "Material.h"
#include "Texture2D.h"

class GenericTextured: public Material{
private:
	static GLuint programID;
	static GLuint MVPId;
	static GLuint baseTextureId;

	GLuint baseTexture;
public:
	static void initMaterial();
	static void unloadMaterial();

	GenericTextured();

	void loadUniforms(glm::mat4& mvp);
	void loadMaterialData(std::string& data);
};

#endif
