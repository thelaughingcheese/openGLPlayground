#include "GenericMvpSolid.h"
#include "LoadShaders.h"
#include <iostream>
#include <sstream>

REGISTER_MATERIAL(GenericMvpSolid)

GLuint GenericMvpSolid::programID;
GLuint GenericMvpSolid::MVPId;
GLuint GenericMvpSolid::colourId;

void GenericMvpSolid::initMaterial(){
	programID = LoadShaders("shaders/GenericMvpSolid.vertexshader","shaders/GenericMvpSolid.fragmentshader");
	MVPId = glGetUniformLocation(programID,"MVP");
	colourId = glGetUniformLocation(programID,"colour");
}

void GenericMvpSolid::unloadMaterial(){
	glDeleteProgram(programID);
}

GenericMvpSolid::GenericMvpSolid(){
}

void GenericMvpSolid::loadUniforms(glm::mat4& mvp){
	glUseProgram(programID);
	glUniformMatrix4fv(MVPId,1,GL_FALSE,&mvp[0][0]);
	glUniform3fv(colourId,1,&colour[0]);
}

void GenericMvpSolid::loadMaterialData(std::string& data){
	//TODO read data, populate material parameters
	//use parser!! takes file and privides map of keys and values
	//colour = glm::vec3(1,0,0);

	std::stringstream dataStream(data);
	while(!dataStream.eof()){
		std::string key;
		dataStream >> key;
		if(key[0] == '#'){
			key = key.substr(1);
			if(key == "colour"){
				std::string r,g,b;
				dataStream >> r >> g >> b;
				colour = glm::vec3(std::stof(r)/255,std::stof(g)/255,std::stof(b)/255);
			}
		}
		else{
			std::cout << "material parameters invalid format" << std::endl;
			return;
		}
	}
}