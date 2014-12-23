#ifndef VIEWPORT
#define VIEWPORT

#include "Camera.h"

class Viewport{
protected:
	Camera* camera;
	unsigned int width,height;

	static GLuint passThroughProgram;
	static GLuint passThroughTexture;
	static bool initialized;
	static const float viewportQuad[];
	static const float viewportQuadUvs[];
	static GLuint viewportQuadBuffer;
	static GLuint viewportQuadUvsBuffer;
	static GLuint viewportVertexArray;

	void firstInit();
public:
	Viewport(Camera* cam);
	Viewport();

	void draw();
	void setCamera(Camera* cam);

	void setResolution(unsigned int w,unsigned int h);
	unsigned int getWidth();
	unsigned int getHeight();
};

#endif