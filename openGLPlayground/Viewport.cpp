#include "Viewport.h"
#include "LoadShaders.h"

GLuint Viewport::passThroughProgram;
GLuint Viewport::passThroughTexture;
bool Viewport::initialized = false;
const float Viewport::viewportQuad[] = {
	-1.0f,-1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	-1.0f,1.0f,0.0f,
	-1.0f,1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	1.0f,1.0f,0.0f,
};
GLuint Viewport::viewportQuadBuffer;

Viewport::Viewport(Camera* cam){
	camera = cam;
	if(!initialized){
		passThroughProgram = LoadShaders("shaders/PassThrough.vertexshader","shaders/PassThrough.fragmentshader");
		passThroughTexture = glGetUniformLocation(passThroughProgram,"renderTexture");
		glGenBuffers(1,&viewportQuadBuffer);
		glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBuffer);
		glBufferData(GL_ARRAY_BUFFER,sizeof(viewportQuad),viewportQuad,GL_STATIC_DRAW);
		initialized = true;
	}
}

void Viewport::draw(){
	camera->draw();

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0,0,1024,768);
	glUseProgram(Viewport::passThroughProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,camera->getRenderTexture());

	glUniform1i(passThroughTexture,0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES,0,6); // 2*3 indices starting at 0 -> 2 triangles
	glDisableVertexAttribArray(0);
}

void Viewport::setCamera(Camera* cam){
	camera = cam;
}

void Viewport::setResolution(unsigned int w,unsigned int h){
	width = w;
	height = h;
}
unsigned int Viewport::getWidth(){
	return width;
}
unsigned int Viewport::getHeight(){
	return height;
}