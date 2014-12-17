#ifndef MESH
#define MESH

#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh{
public:
	glm::vec3* verticies;
	glm::vec3* normals;
	glm::vec2* uvs;
	unsigned int vertexCount;
	unsigned int normalCount;
	unsigned int uvCount;

	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;

	Mesh();
	~Mesh();

	void createBuffers();
	void loadVertexData();
	void unloadVertexData();
};

#endif