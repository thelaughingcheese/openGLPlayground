#include "Utility.h"
#include <unordered_map>
#include "Texture2D.h"
#include "LoadShaders.h"
#include "GenericMvpSolid.h"
#include <iostream>
#include <fstream>

//0 is Null entity
EntityID NextEntityID = 1;

std::unordered_map<const char*,Model*> loadedModels;
std::unordered_map<const char*,Texture2D*> loadedTextures;

Camera* Utility::curCamera;

void Utility::initShaders(){
	MaterialDictionary::initMaterials();
}

void Utility::unloadShaders(){
	MaterialDictionary::unloadMaterials();
}

EntityID Utility::getNewEntityID(){
	return NextEntityID++;
}

Entity* getEntityByID(EntityID id){
	try{
		return Entity::entities.at(id);
	}
	catch(std::out_of_range exep){
		return 0;
	}
}

Model* Utility::getModel(const char* modelName){
	try{
		return loadedModels.at(modelName);
	}
	catch(std::out_of_range exep){
		Model* newModel = new Model(modelName);
		loadedModels.insert(std::pair<const char*,Model*>(modelName,newModel));
		return newModel;
	}
}

GLuint Utility::getTexture(const char* textureName){
	try{
		return loadedTextures.at(textureName)->getTextureID();
	}
	catch(std::out_of_range exep){
		Texture2D* newTexture = new Texture2D(textureName);
		loadedTextures.insert(std::pair<const char*,Texture2D*>(textureName,newTexture));
		return newTexture->getTextureID();
	}
}

Material* Utility::loadMaterialFromFile(const char* materialName){
	std::ifstream materialFile(std::string("materials/")+materialName,std::ios::binary);
	if(!materialFile.is_open()){
		std::cout << std::endl << "material " << materialName << " not found" << std::endl;
		return 0;
	}
	char line[128];
	materialFile.getline(line,128);
	std::string shader = line;
	shader = shader.substr(0,shader.size()-1);
	std::string data;
	while(!materialFile.eof()){
		materialFile.getline(line,128);
		data += line;
	}
	MaterialRecord* p = (*MaterialDictionary::getMaterialDictionary())[shader.data()];
	Material* rtn = p->create();
	rtn->loadMaterialData(data);
	return rtn;
}

void Utility::unloadModels(){
	std::unordered_map<const char*,Model*>::iterator it = loadedModels.begin();
	for(; it != loadedModels.end(); ++it){
		delete it->second;
	}
	loadedModels.clear();
}

void Utility::unloadTextures(){
	std::unordered_map<const char*,Texture2D*>::iterator it = loadedTextures.begin();
	for(; it != loadedTextures.end(); ++it){
		delete it->second;
	}
	loadedTextures.clear();
}