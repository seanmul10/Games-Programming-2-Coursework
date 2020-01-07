#include "Texture.h"

Texture::Texture()
{

}

void Texture::InitTexture(const std::string& filename)
{
	// Texture dimensions
	int width;
	int height;
	int numComponents;

	// Load and store the texture image
	unsigned char* imageData = stbi_load(("..\\res\\" + filename).c_str(), &width, &height, &numComponents, 4);

	// If the image data is invalid, output an error message
	if (imageData == nullptr)
	{
		std::cerr << "Failed to load texture with filename: " + filename << std::endl;
	}

	glGenTextures(1, &textureHandle); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandle); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageData);
}

void Texture::Bind(unsigned int uint)
{
	// Make sure uint is within range
	if (uint < 0 || uint > 31)
	{
		std::cerr << "Texture could not be binded, index must be between 0 and 31" << std::endl;
		return;
	}

	// Set active texture and bind it
	glActiveTexture(GL_TEXTURE + uint);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}

Texture::~Texture()
{

}