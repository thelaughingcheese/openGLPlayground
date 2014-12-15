#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

Model::Model(const char* modelName){
	verticies = 0;
	normals = 0;
	uvs = 0;
	textures = 0;

	//load raw data
	std::string objFilePath = "models/";
	objFilePath += modelName;
	objFilePath += ".obj";
	std::ifstream objFile(objFilePath,std::ios::binary);

	if(!objFile.is_open()){
		std::cout << "Could not load model: " << modelName << std::endl;
		return;
	}

	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> texcoords;
	std::vector<std::string> faces;

	while(!objFile.eof()){
		char line[128];
		objFile.getline(line,128);
		if(line[0] == 'v' && line[1] == 't'){
			std::stringstream data(&line[3]);
			float x,y;

			data >> x >> y;

			texcoords.push_back(glm::vec2(x,y));
		}
		else if(line[0] == 'v' && line[1] == 'n'){
			std::stringstream data(&line[3]);
			float x,y,z;

			data >> x >> y >> z;

			norms.push_back(glm::vec3(x,y,z));
		}
		else if(line[0] == 'v'){
			std::stringstream data(&line[2]);
			float x,y,z;

			data >> x >> y >> z;

			verts.push_back(glm::vec3(x,y,z));
		}
		else if(line[0] == 'f'){
			faces.push_back(&line[1]);
		}
		else if(line[0] == '#'){
			//comment
		}
		else{
			std::cout << "Line unrecognised: " << line << std::endl;
		}
	}

	std::vector<glm::vec3> newVerts;
	std::vector<glm::vec3> newNorms;
	std::vector<glm::vec2> newUvs;

	for(int i=0;i<faces.size();i++){
		int vertIndex[3];
		int normIndex[3];
		int uvIndex[3];

		std::string buffer;
		/*std::getline(data,buffer,'/'); vertIndex[0] = std::stoi(buffer);
		std::getline(data,buffer,'/'); uvIndex[0] = std::stoi(buffer);
		std::getline(data,buffer,'/'); normIndex[0] = std::stoi(buffer);

		std::getline(data,buffer,'/'); vertIndex[1] = std::stoi(buffer);
		std::getline(data,buffer,'/'); uvIndex[1] = std::stoi(buffer);
		std::getline(data,buffer,'/'); normIndex[1] = std::stoi(buffer);

		std::getline(data,buffer,'/'); vertIndex[2] = std::stoi(buffer);
		std::getline(data,buffer,'/'); uvIndex[2] = std::stoi(buffer);
		std::getline(data,buffer,'/'); normIndex[2] = std::stoi(buffer);*/

		sscanf(faces[i].data(),"%d/%d/%d %d/%d/%d %d/%d/%d",&vertIndex[0],&uvIndex[0],&normIndex[0],&vertIndex[1],&uvIndex[1],&normIndex[1],&vertIndex[2],&uvIndex[2],&normIndex[2]);

		newVerts.push_back(verts[vertIndex[0] - 1]);
		newVerts.push_back(verts[vertIndex[1] - 1]);
		newVerts.push_back(verts[vertIndex[2] - 1]);

		newNorms.push_back(norms[normIndex[0] - 1]);
		newNorms.push_back(norms[normIndex[1] - 1]);
		newNorms.push_back(norms[normIndex[2] - 1]);

		newUvs.push_back(texcoords[uvIndex[0] - 1]);
		newUvs.push_back(texcoords[uvIndex[1] - 1]);
		newUvs.push_back(texcoords[uvIndex[2] - 1]);
	}

	vertexCount = newVerts.size();
	normalCount = newNorms.size();
	uvCount = newUvs.size();

	verticies = new glm::vec3[vertexCount];
	normals = new glm::vec3[normalCount];
	uvs = new glm::vec2[uvCount];

	for(unsigned int i=0; i<vertexCount; i++){
		verticies[i] = newVerts[i];
	}
	for(unsigned int i=0; i<normalCount; i++){
		normals[i] = newNorms[i];
	}
	for(unsigned int i=0; i<uvCount; i++){
		uvs[i] = newUvs[i];
	}

	//create buffers
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

Model::~Model(){
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

GLuint Model::getVertexBuffer(){
	return vertexBuffer;
}

GLuint Model::getNormalBuffer(){
	return normalBuffer;
}

GLuint Model::getUvBuffer(){
	return uvBuffer;
}

unsigned int Model::getVertexCount(){
	return vertexCount;
}

unsigned int Model::getNormalCount(){
	return normalCount;
}

unsigned int Model::getUvCount(){
	return uvCount;
}