/*
contains:
vertex
triangles
uvs
normals
texture
*/
#ifndef MODEL
#define MODEL

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Mesh.h"
#include "Material.h"

class Model{
private:
	Mesh* meshes;
	Material** materials;
	unsigned int meshCount;
	unsigned int materialsCount;

	void addMesh();
public:
	Model(const char* modelName);
	~Model();

	void draw(glm::mat4& mvp);
};

#endif