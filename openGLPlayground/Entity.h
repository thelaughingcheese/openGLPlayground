/*
instances can be handled dynamically
*/

#ifndef ENTITY
#define ENTITY

#include <unordered_map>

typedef unsigned long EntityID;

class Entity{
private:
	EntityID entityID;
public:
	static std::unordered_map<EntityID,Entity*> entities;

	Entity();
	virtual ~Entity();

	EntityID getEntityID();
};

#endif