#include "StereoscopicViewport.h"

bool StereoscopicViewport::initialized = false;
const float StereoscopicViewport::viewportQuadRight[] ={
	-1.0f,-1.0f,0.0f,
	0.0,-1.0f,0.0f,
	-1.0f,1.0f,0.0f,
	-1.0f,1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f,
};
const float StereoscopicViewport::viewportQuadUvsRight[] ={
	0.0f,0.0f,
	1.0f,0.0f,
	0.0f,1.0f,
	0.0f,1.0f,
	1.0f,0.0f,
	1.0f,1.0f,
};
const float StereoscopicViewport::viewportQuadLeft[] ={
	0.0f,-1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	1.0f,-1.0f,0.0f,
	1.0f,1.0f,0.0f,
};
const float StereoscopicViewport::viewportQuadUvsLeft[] ={
	0.0f,0.0f,
	1.0f,0.0f,
	0.0f,1.0f,
	0.0f,1.0f,
	1.0f,0.0f,
	1.0f,1.0f,
};
GLuint StereoscopicViewport::viewportQuadBufferLeft;
GLuint StereoscopicViewport::viewportQuadUvsBufferLeft;
GLuint StereoscopicViewport::viewportQuadBufferRight;
GLuint StereoscopicViewport::viewportQuadUvsBufferRight;

void StereoscopicViewport::firstInit(){
	if(!initialized){
		glGenBuffers(1,&viewportQuadBufferLeft);
		glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBufferLeft);
		glBufferData(GL_ARRAY_BUFFER,sizeof(viewportQuadLeft),viewportQuadLeft,GL_STATIC_DRAW);
		glGenBuffers(1,&viewportQuadBufferRight);
		glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBufferRight);
		glBufferData(GL_ARRAY_BUFFER,sizeof(viewportQuadRight),viewportQuadRight,GL_STATIC_DRAW);

		glGenBuffers(1,&viewportQuadUvsBufferLeft);
		glBindBuffer(GL_ARRAY_BUFFER,viewportQuadUvsBufferLeft);
		glBufferData(GL_ARRAY_BUFFER,sizeof(viewportQuadUvsLeft),viewportQuadUvsLeft,GL_STATIC_DRAW);
		glGenBuffers(1,&viewportQuadUvsBufferRight);
		glBindBuffer(GL_ARRAY_BUFFER,viewportQuadUvsBufferRight);
		glBufferData(GL_ARRAY_BUFFER,sizeof(viewportQuadUvsRight),viewportQuadUvsRight,GL_STATIC_DRAW);
	}
}

StereoscopicViewport::StereoscopicViewport(StereoscopicCamera* cam){
	stereoCamera = cam;
	setResolution(cam->getWidth(),cam->getHeight());
	firstInit();
}

void StereoscopicViewport::setCamera(StereoscopicCamera* cam){
	stereoCamera = cam;
}

void StereoscopicViewport::draw(){
	stereoCamera->draw();

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glViewport(0,0,width,height);
	glUseProgram(Viewport::passThroughProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,stereoCamera->getLeftRenderTexture());

	glUniform1i(passThroughTexture,0);

	glBindVertexArray(viewportVertexArray);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBufferLeft);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,viewportQuadUvsBufferLeft);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES,0,6); // 2*3 indices starting at 0 -> 2 triangles

	//right
	glBindTexture(GL_TEXTURE_2D,stereoCamera->getRightRenderTexture());

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,viewportQuadBufferRight);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,viewportQuadUvsBufferRight);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);
	glDrawArrays(GL_TRIANGLES,0,6); // 2*3 indices starting at 0 -> 2 triangles
}