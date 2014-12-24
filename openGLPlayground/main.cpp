#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <windows.h>

#include "Utility.h"
#include "Camera.h"
#include "Texture2D.h"
#include "ModelEntity.h"
#include "Imu.h"
#include "StereoscopicViewport.h"

int main(int argc,char** argv){
		if(!glfwInit())
		{
			fprintf(stderr,"Failed to initialize GLFW\n");
			return -1;
		}

		glfwWindowHint(GLFW_SAMPLES,4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(1024,512,"Tutorial 02 - Red triangle",NULL,NULL);
		if(window == NULL){
			fprintf(stderr,"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		glewExperimental = true; // Needed for core profile
		if(glewInit() != GLEW_OK) {
			fprintf(stderr,"Failed to initialize GLEW\n");
			return -1;
		}
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

		glClearColor(0.0f,0.0f,0.4f,0.0f);

		//wireframe
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		//----------------

		ModelEntity xAxisArrow("arrowX");
		ModelEntity yAxisArrow("arrowY");
		yAxisArrow.setOrientation(glm::angleAxis(glm::radians(90.0f),glm::vec3(0,0,1)));
		ModelEntity zAxisArrow("arrowZ");
		zAxisArrow.setOrientation(glm::angleAxis(glm::radians(-90.0f),glm::vec3(0,1,0)));
		ModelEntity accelArrow("greyArrow");
		ModelEntity gyroArrow("box");

		Imu imu("COM2",accelArrow,gyroArrow);

		GLuint VertexArrayID;
		glGenVertexArrays(1,&VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Create and compile our GLSL program from the shaders
		Utility::initShaders();

		//Camera camera(2048,2048,45.0,glm::vec3(0,10,30));
		StereoscopicCamera camera(512,512,45.0,glm::vec3(0,10,30));
		//Viewport viewport(&camera);
		//viewport.setResolution(1024,1024);
		StereoscopicViewport viewport(&camera);
		//viewport.setResolution(512,256);
		camera.setSeperation(3);

		double xMouse, yMouse;
		int windowX,windowY;
		glfwGetWindowSize(window,&windowX,&windowY);
		glfwSetCursorPos(window,windowX/2,windowY/2);
		glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		double lastTime = glfwGetTime();
		
		do{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwGetCursorPos(window,&xMouse,&yMouse);
			xMouse -= windowX/2; xMouse /= 16;
			yMouse -= windowY/2; yMouse /= 16;
			glfwSetCursorPos(window,windowX/2,windowY/2);
			glm::vec3 changePos(0,0,0);
			if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
				changePos += 0.4f * camera.getForwardVector();
			}
			if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
				changePos += -0.4f * camera.getRightVector();
			}
			if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
				changePos += -0.4f * camera.getForwardVector();
			}
			if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
				changePos += 0.4f * camera.getRightVector();
			}
			camera.setPos(camera.getPos() + changePos);

			camera.setOri(glm::vec2((-xMouse + camera.getOri().x),min(89.99,max(-89.99,-yMouse + camera.getOri().y))));

			//std::cout << 1/(glfwGetTime() - lastTime) << std::endl;
			lastTime = glfwGetTime();

			imu.update();

			viewport.draw();

			glfwSwapBuffers(window);
			glfwPollEvents();
			while(glfwGetTime() - lastTime < 0.01666);
		}
		while(glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

		Utility::unloadModels();
		Utility::unloadTextures();
		Utility::unloadShaders();

		glfwTerminate();

		return 0;
	}

