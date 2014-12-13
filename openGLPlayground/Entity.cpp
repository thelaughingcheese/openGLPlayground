#include "Entity.h"
#include "Utility.h"

Entity::Entity(){
	entityID = Utility::getNewEntityID();
}

EntityID Entity::getEntityID(){
	return entityID;
}