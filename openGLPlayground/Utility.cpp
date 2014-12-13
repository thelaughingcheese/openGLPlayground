#include "Utility.h"
#include <unordered_map>
#include "Texture2D.h"

//0 is Null entity
EntityID NextEntityID = 1;

std::unordered_map<EntityID,Entity*,std::hash<EntityID>,std::equal_to<EntityID>,std::allocator<std::pair<EntityID,Entity*>>> Entities;

std::unordered_map<const char*,Model*,std::hash<const char*>,std::equal_to<const char*>,std::allocator<std::pair<const char*,Model*>>> loadedModels;
std::unordered_map<const char*,Texture2D*,std::hash<const char*>,std::equal_to<const char*>,std::allocator<std::pair<const char*,Texture2D*>>> loadedTextures;

EntityID Utility::getNewEntityID(){
	return NextEntityID++;
}

Entity* Utility::createEntity();
void Utility::destroyEntity();

Entity* getEntityByID(EntityID id){
	try{
		return Entities.at(id);
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