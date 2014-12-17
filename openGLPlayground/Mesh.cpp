#include "Mesh.h"

Mesh::Mesh(){
}

Mesh::~Mesh(){
	if(verticies){
		delete[] verticies;
		delete[] normals;
		delete[] uvs;

		glDeleteVertexArrays(1,&vertexArray);
		glDeleteBuffers(1,&vertexBuffer);
		glDeleteBuffers(1,&normalBuffer);
		glDeleteBuffers(1,&uvBuffer);
	}
}

void Mesh::loadVertexData(){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
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
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);
}

void Mesh::unloadVertexData(){
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Mesh::createBuffers(){
	glGenVertexArrays(1,&vertexArray);
	glGenBuffers(1,&vertexBuffer);
	glGenBuffers(1,&normalBuffer);
	glGenBuffers(1,&uvBuffer);

	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,vertexCount*sizeof(glm::vec3),verticies,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,normalBuffer);
	glBufferData(GL_ARRAY_BUFFER,normalCount*sizeof(glm::vec3),normals,GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
	glBufferData(GL_ARRAY_BUFFER,uvCount*sizeof(glm::vec2),uvs,GL_STATIC_DRAW);
}