#include "GenericTextured.h"
#include "LoadShaders.h"
#include "Utility.h"
#include <iostream>
#include <sstream>

REGISTER_MATERIAL(GenericTextured)

GLuint GenericTextured::programID;
GLuint GenericTextured::MVPId;
GLuint GenericTextured::baseTextureId;

void GenericTextured::initMaterial(){
	GenericTextured::programID = LoadShaders("shaders/GenericTextured.vertexshader","shaders/GenericTextured.fragmentshader");
	MVPId = glGetUniformLocation(GenericTextured::programID,"MVP");
	baseTextureId = glGetUniformLocation(GenericTextured::programID,"baseTexture");
}

void GenericTextured::unloadMaterial(){
	glDeleteProgram(programID);
}

GenericTextured::GenericTextured(){
}

void GenericTextured::loadUniforms(glm::mat4& mvp){
	glUseProgram(programID);
	glUniformMatrix4fv(MVPId,1,GL_FALSE,&mvp[0][0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,baseTexture);
	glUniform1i(baseTexture,0);
}

void GenericTextured::loadMaterialData(std::string& data){
	//TODO read data, populate material parameters
	//use parser!! takes file and privides map of keys and values
	//colour = glm::vec3(1,0,0);

	std::stringstream dataStream(data);
	while(!dataStream.eof()){
		std::string key;
		dataStream >> key;
		if(key[0] == '#'){
			key = key.substr(1);
			if(key == "basetexture"){
				std::string tex;
				dataStream >> tex;
				baseTexture = Utility::getTexture(tex.data());
			}
		}
		else{
			std::cout << "material parameters invalid format" << std::endl;
			return;
		}
	}
}