#include <GL\glew.h>
#include "stb_image.h"
#include <iostream>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	GLuint InitTexture(const std::string&); // Initialises the texture
	void Bind(unsigned int); // Bind the texture and give it an index from 0 - 31

private:
	GLuint textureHandle;
};