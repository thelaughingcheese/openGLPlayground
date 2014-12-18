#include "GenericMvpSolid.h"
#include "LoadShaders.h"

REGISTER_MATERIAL(GenericMvpSolid)

GLuint GenericMvpSolid::programID;
GLuint GenericMvpSolid::MVPId;
GLuint GenericMvpSolid::colourId;

void GenericMvpSolid::initMaterial(){
	GenericMvpSolid::programID = LoadShaders("shaders/GenericMvpSolid.vertexshader","shaders/GenericMvpSolid.fragmentshader");
	MVPId = glGetUniformLocation(GenericMvpSolid::programID,"MVP");
	colourId = glGetUniformLocation(GenericMvpSolid::programID,"colour");
}

GenericMvpSolid::GenericMvpSolid(){
}

void GenericMvpSolid::loadUniforms(glm::mat4& mvp){
	glUseProgram(programID);
	glUniformMatrix4fv(MVPId,1,GL_FALSE,&mvp[0][0]);
	glUniform3fv(colourId,1,&colour[0]);
}

void GenericMvpSolid::loadMaterialData(std::string data){
	//TODO read data, populate material parameters
}