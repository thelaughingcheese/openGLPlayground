#include "texture2D.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <GL/glew.h>

Texture2D::Texture2D(const char* file){
	bitmap = 0;
	loadBmp(file);
}

Texture2D::~Texture2D(){
	unload();
}

bool Texture2D::loadBmp(const char* filePath){
	unload();
	std::string nfilep = "materials/";
	nfilep += filePath;
	filePath = nfilep.data();
	std::ifstream file(filePath,std::ios::binary);
	if(!file.is_open()){
		std::cout << "Could not load texture: " << filePath << std::endl;
		return false;
	}

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	file.read((char*)header,54);
	if(!file.good()){
		std::cout << "BMP header too short: " << filePath << std::endl;
		file.close();
		return false;
	}
	if(header[0] != 'B' && header[1] != 'M'){
		std::cout << "BMP header incorrect: " << filePath << std::endl;
		file.close();
		return false;
	}

	width = *(unsigned int*)&header[0x12];
	height = *(unsigned int*)&header[0x16];
	imageSize = *(unsigned int*)&header[0x22];

	if(imageSize == 0){
		imageSize = width*height*3;
	}

	bitmap = new unsigned char[imageSize];
	file.read((char*)bitmap,imageSize);
	file.close();
	if(!file.good()){
		std::cout << "BMP file shorter than expected! Loaded anyways: " << filePath << std::endl;
	}
	glGenTextures(1,&glTextureID);
	glBindTexture(GL_TEXTURE_2D,glTextureID);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGR,GL_UNSIGNED_BYTE,bitmap);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}

void Texture2D::unload(){
	if(bitmap != 0){
		delete[] bitmap;
		glDeleteTextures(1,&glTextureID);
	}
}

bool Texture2D::isLoaded(){
	return (bitmap != 0);
}

GLuint Texture2D::getTextureID(){
	return glTextureID;
}