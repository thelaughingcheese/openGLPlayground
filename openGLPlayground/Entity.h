/*
instances can be handled dynamically
*/

#ifndef ENTITY
#define ENTITY

typedef unsigned long EntityID;

class Entity{
private:
	EntityID entityID;
public:
	Entity();
	virtual ~Entity();

	EntityID getEntityID();
};

#endif