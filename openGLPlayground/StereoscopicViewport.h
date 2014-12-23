#ifndef STEREOSCOPICVIEWPORT
#define STEREOSCOPICVIEWPORT

#include "Viewport.h"
#include "StereoscopicCamera.h"

class StereoscopicViewport:public Viewport{
private:
	StereoscopicCamera* stereoCamera;

	static bool initialized;
	static const float viewportQuadLeft[];
	static const float viewportQuadUvsLeft[];
	static const float viewportQuadRight[];
	static const float viewportQuadUvsRight[];
	static GLuint viewportQuadBufferLeft;
	static GLuint viewportQuadUvsBufferLeft;
	static GLuint viewportQuadBufferRight;
	static GLuint viewportQuadUvsBufferRight;

	void firstInit();
public:
	StereoscopicViewport(StereoscopicCamera* cam);
	void setCamera(Camera* cam){}
	void setCamera(StereoscopicCamera* cam);
	void draw();
};

#endif