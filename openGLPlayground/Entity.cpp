#include "Entity.h"
#include "Utility.h"

Entity::Entity(){
	entityID = Utility::getNewEntityID();
	Utility::trackEntity(this);
}

Entity::~Entity(){
	Utility::untrackEntity(entityID);
}

EntityID Entity::getEntityID(){
	return entityID;
}