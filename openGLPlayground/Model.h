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

class Model{
private:
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
	GLuint* textures;
	int textureCount;
public:
	Model(const char* modelName);
	~Model();

	GLuint getVertexBuffer();
	GLuint getNormalBuffer();
	GLuint getUvBuffer();

	unsigned int getVertexCount();
	unsigned int getNormalCount();
	unsigned int getUvCount();
};

#endif

/*
glGenVertexArrays(1,&VertexArrayID);
glBindVertexArray(VertexArrayID);

glGenBuffers(1,&vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);

glDeleteBuffers(1,&vertexbuffer);
glDeleteVertexArrays(1,&VertexArrayID);

drawing

glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
glVertexAttribPointer(
0,
3,
GL_FLOAT,
GL_FALSE,
0,
(void*)0
);
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
glVertexAttribPointer(
1,
2,
GL_FLOAT,
GL_FALSE,
0,
(void*)0
);


glDrawArrays(GL_TRIANGLES,0,36); // 3 indices starting at 0 -> 1 triangle

glDisableVertexAttribArray(0);
glDisableVertexAttribArray(1);
*/