#include "GenericMvpSolid.h"
#include "LoadShaders.h"

GenericMvpSolid::GenericMvpSolid(){
	programID = LoadShaders("SimpleVertexShader.vertexshader","SimpleFragmentShader.fragmentshader");
}

void GenericMvpSolid::loadTextures(){
}

void GenericMvpSolid::loadUniforms(){
}