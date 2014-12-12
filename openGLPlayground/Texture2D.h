/*
2D texture
*/
#include <GL/glew.h>

#ifndef TEXTURE2D
#define TEXTURE2D

class Texture2D{
private:
	unsigned char* bitmap;
	unsigned int width,height;
	GLuint glTextureID;
public:
	Texture2D(const char* file);
	~Texture2D();

	GLuint getTextureID();
	bool isLoaded();

	bool loadBmp(const char* file);
	void unload();
};

#endif