#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "LoadShaders.h"

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

		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4,3,3),glm::vec3(0,0,0),glm::vec3(0,1,0));
		glm::mat4 perspectiveMatrix = glm::perspective(45.0,4.0/3.0,0.1,100.0);
		glm::mat4 projectionMatrix = perspectiveMatrix * viewMatrix;

		GLint MatrixID = glGetUniformLocation(programID,"MVP");

		GLuint vertexbuffer;
		glGenBuffers(1,&vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER,sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);

		do{
			glClear(GL_COLOR_BUFFER_BIT);

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

		}
		while(glfwGetKey(window,GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

		glDeleteBuffers(1,&vertexbuffer);
		glDeleteVertexArrays(1,&VertexArrayID);
		glDeleteProgram(programID);

		glfwTerminate();

		return 0;
	}

