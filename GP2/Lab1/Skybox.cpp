#include "Skybox.h"

// Method used from https://learnopengl.com/Advanced-OpenGL/Cubemaps

unsigned int Skybox::LoadSkybox(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;

	// Loop through each face
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else // If the data is invalid, print an error message
		{
			std::cerr << "Failed to load skybox: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID; // Return the texture ID
}

// Get the faces
vector<string> Skybox::GetFaces()
{
	return faces;
}

void Skybox::DrawSkybox()
{
	layout(location = 0) in vec3 aPos;

	out vec3 TexCoords;

	uniform mat4 projection;
	uniform mat4 view;

	void main()
	{
		TexCoords = aPos;
		gl_Position = projection * view * vec4(aPos, 1.0);
	}
}