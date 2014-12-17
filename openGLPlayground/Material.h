#ifndef MATERIAL
#define MATERIAL

#include <GL/glew.h>

class Material{
private:
protected:
	GLuint programID;
public:
	virtual void loadTextures() = 0;
	virtual void loadUniforms() = 0;
};

#endif