#ifndef GENERICMVPSOLID
#define GENERICMVPSOLID

#include "Material.h"

class GenericMvpSolid: public Material{
public:
	GenericMvpSolid();

	void loadTextures();
	void loadUniforms();
};

#endif