#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

GLuint LoadShaders(const char * vertexFilePath,const char * fragmentFilePath){
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath,std::ios::in);
	if(vertexShaderStream.is_open()){
		std::string line = "";
		while(getline(vertexShaderStream,line)){
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath,std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::string line = "";
		while(getline(fragmentShaderStream,line)){
			fragmentShaderCode += "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	//compile vertex shader
	printf("Compiling shader: %s\n",vertexFilePath);
	char const * VertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(VertexShaderID,1,&VertexSourcePointer,NULL);
	glCompileShader(VertexShaderID);
	//check vertex shader
	glGetShaderiv(VertexShaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(VertexShaderID,GL_INFO_LOG_LENGTH,&infoLogLength);
	std::vector<char> VertexShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(VertexShaderID,infoLogLength,NULL,&VertexShaderErrorMessage[0]);
	fprintf(stdout,"%s\n",&VertexShaderErrorMessage[0]);

	//compile fragment shader
	printf("Compiling shader: %s\n",fragmentFilePath);
	char const * FragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID,1,&FragmentSourcePointer,NULL);
	glCompileShader(FragmentShaderID);
	//check fragment shader
	glGetShaderiv(FragmentShaderID,GL_COMPILE_STATUS,&result);
	glGetShaderiv(FragmentShaderID,GL_INFO_LOG_LENGTH,&infoLogLength);
	std::vector<char> FragmentShaderErrorMessage(infoLogLength);
	glGetShaderInfoLog(FragmentShaderID,infoLogLength,NULL,&FragmentShaderErrorMessage[0]);
	fprintf(stdout,"%s\n",&FragmentShaderErrorMessage[0]);

	//link shaders to a program
	fprintf(stdout,"Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID,VertexShaderID);
	glAttachShader(ProgramID,FragmentShaderID);
	glLinkProgram(ProgramID);

	//check program
	glGetProgramiv(ProgramID,GL_LINK_STATUS,&result);
	glGetProgramiv(ProgramID,GL_INFO_LOG_LENGTH,&infoLogLength);
	std::vector<char> ProgramErrorMessage(fmax(infoLogLength,int(1)));
	glGetProgramInfoLog(ProgramID,infoLogLength,NULL,&ProgramErrorMessage[0]);
	fprintf(stdout,"%s\n",&ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}