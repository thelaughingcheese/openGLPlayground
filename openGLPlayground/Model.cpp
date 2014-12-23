#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "GenericMvpSolid.h"
#include "Utility.h"

Model::Model(const char* modelName){
	meshes = 0;
	materials= 0;

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
	std::vector<std::vector<std::string>> faceGroups;
	std::vector<std::string> materialNames;

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
			faceGroups.back().push_back(&line[1]);
		}
		else if(line[0] == '#'){
			//comment
		}
		else if(line[0] == 'u' && line[1] == 's' && line[2] == 'e' && line[3] == 'm' && line[4] == 't' && line[5] == 'l'){
			std::string matName = &line[7];
			matName = matName.substr(0,matName.size()-1);
			materialNames.push_back(matName);
			faceGroups.push_back(std::vector<std::string>());
		}
		else{
			std::cout << "Line unrecognised: " << line << std::endl;
		}
	}

	materialsCount = materialNames.size();
	materials = new Material*[materialsCount];
	meshCount = faceGroups.size();
	meshes = new Mesh[meshCount];

	for(unsigned int k=0; k<meshCount; k++){
		std::vector<glm::vec3> newVerts;
		std::vector<glm::vec3> newNorms;
		std::vector<glm::vec2> newUvs;

		for(unsigned int i=0; i<faceGroups[k].size(); i++){
			int vertIndex[3];
			int normIndex[3];
			int uvIndex[3];

			std::string buffer;
			sscanf(faceGroups[k][i].data(),"%d/%d/%d %d/%d/%d %d/%d/%d",&vertIndex[0],&uvIndex[0],&normIndex[0],&vertIndex[1],&uvIndex[1],&normIndex[1],&vertIndex[2],&uvIndex[2],&normIndex[2]);

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

		meshes[k].vertexCount = newVerts.size();
		meshes[k].normalCount = newNorms.size();
		meshes[k].uvCount = newUvs.size();

		meshes[k].verticies = new glm::vec3[meshes[0].vertexCount];
		meshes[k].normals = new glm::vec3[meshes[0].normalCount];
		meshes[k].uvs = new glm::vec2[meshes[0].uvCount];

		for(unsigned int i=0; i<meshes[0].vertexCount; i++){
			meshes[k].verticies[i] = newVerts[i];
		}
		for(unsigned int i=0; i<meshes[0].normalCount; i++){
			meshes[k].normals[i] = newNorms[i];
		}
		for(unsigned int i=0; i<meshes[0].uvCount; i++){
			meshes[k].uvs[i] = newUvs[i];
		}
	}

	//create buffers
	for(unsigned int i=0; i<meshCount; i++){
		meshes[i].createBuffers();
	}

	//add materials
	for(unsigned int i=0; i<materialsCount; i++){
		materials[i] = Utility::loadMaterialFromFile(materialNames[i].data());
	}
}

Model::~Model(){
	delete[] meshes;
	for(unsigned int i=0; i<materialsCount; i++){
		delete materials[i];
	}
	delete[] materials;
}

void Model::draw(glm::mat4& mvp){
	for(unsigned int i=0; i<meshCount; i++){
		materials[i]->loadUniforms(mvp);

		meshes[i].loadVertexData();
		glDrawArrays(GL_TRIANGLES,0,meshes[i].vertexCount);
		meshes[i].unloadVertexData();
	}
}

void Model::addMesh(){

}