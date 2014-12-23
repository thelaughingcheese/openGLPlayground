#ifndef VIEWPORT
#define VIEWPORT

#include "Camera.h"

class Viewport{
private:
	Camera* camera;
	unsigned int width,height;

	static GLuint passThroughProgram;
	static GLuint passThroughTexture;
	static bool initialized;
	static const float viewportQuad[];
	static GLuint viewportQuadBuffer;
public:
	Viewport(Camera* cam);

	void draw();
	void setCamera(Camera* cam);

	void setResolution(unsigned int w,unsigned int h);
	unsigned int getWidth();
	unsigned int getHeight();
};

#endif