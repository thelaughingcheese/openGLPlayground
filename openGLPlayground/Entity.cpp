#include "Entity.h"
#include "Utility.h"

std::unordered_map<EntityID,Entity*> Entity::entities;

Entity::Entity(){
	entityID = Utility::getNewEntityID();
	entities.insert(std::pair<EntityID,Entity*>(entityID,this));
}

Entity::~Entity(){
	entities.erase(entityID);
}

EntityID Entity::getEntityID(){
	return entityID;
}