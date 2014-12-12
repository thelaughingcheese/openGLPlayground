#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <windows.h>

#include "LoadShaders.h"
#include "Camera.h"

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

		GLFWwindow* window = glfwCreateWindow(1024,768,"Tutorial 02 - Red triangle",NULL,NULL);
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

		glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

		glClearColor(0.0f,0.0f,0.4f,0.0f);

		GLuint VertexArrayID;
		glGenVertexArrays(1,&VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Create and compile our GLSL program from the shaders
		GLuint programID = LoadShaders("SimpleVertexShader.vertexshader","SimpleFragmentShader.fragmentshader");

		static const GLfloat g_vertex_buffer_data[] ={
			-1.0f,-1.0f,0.0f,
			1.0f,-1.0f,0.0f,
			0.0f,1.0f,0.0f,
		};

		Camera camera(45,4.0/3.0,glm::vec3(0,0,5));
		glm::mat4 projectionMatrix = camera.getProjectionMatrix();

		GLint MatrixID = glGetUniformLocation(programID,"MVP");

		GLuint vertexbuffer;
		glGenBuffers(1,&vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);

		double xMouse, yMouse;
		glfwSetCursorPos(window,512,768/2);
		glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
		double lastTime = glfwGetTime();
		
		do{
			glClear(GL_COLOR_BUFFER_BIT);
			glfwGetCursorPos(window,&xMouse,&yMouse);
			xMouse -= 512; xMouse /= 16;
			yMouse -= 768/2; yMouse /= 16;
			glfwSetCursorPos(window,512,768/2);
			glm::vec3 changePos(0,0,0);
			if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
				changePos += 0.05f * camera.getForwardVector();
			}
			if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS){
				changePos += -0.05f * camera.getRightVector();
			}
			if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS){
				changePos += -0.05f * camera.getForwardVector();
			}
			if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS){
				changePos += 0.05f * camera.getRightVector();
			}
			camera.setPos(camera.getPos() + changePos);

			camera.setOri(glm::vec2((-xMouse + camera.getOri().x),min(89.99,max(-89.99,-yMouse + camera.getOri().y))));
			projectionMatrix = camera.getProjectionMatrix();

			//std::cout << 1/(glfwGetTime() - lastTime) << std::endl;
			lastTime = glfwGetTime();

			glUseProgram(programID);
			glUniformMatrix4fv(MatrixID,1,GL_FALSE,&projectionMatrix[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
				);

			glDrawArrays(GL_TRIANGLES,0,3); // 3 indices starting at 0 -> 1 triangle

			glDisableVertexAttribArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
			while(glfwGetTime() - lastTime < 0.012);
		}
		while(glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

		glDeleteBuffers(1,&vertexbuffer);
		glDeleteVertexArrays(1,&VertexArrayID);
		glDeleteProgram(programID);

		glfwTerminate();

		return 0;
	}

