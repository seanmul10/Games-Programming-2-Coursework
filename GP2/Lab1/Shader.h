#include "Camera.h"
#include "transform.h"
#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader();
	~Shader();

	void InitShader(const std::string&); // Initialise the shader

	void Bind(); // Allow shader to be used by the gpu
	void Update(const Transform&, const Camera& camera); // Updates the shader

	std::string LoadShader(const std::string&); // Load the shader from a filename
	GLuint CreateShader(const std::string&, unsigned int); // Create the loaded shader

	// Checks for a specified error to do with the shader before logging an error message to the console
	void Shader::CheckForShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

private:
	enum { TRANSFORM_U, NUM_UNIFORMS };

	static const unsigned int NUM_SHADERS = 2; // Amount of shaders

	GLuint program; // Shader program
	GLuint shaders[NUM_SHADERS]; // Shader array
	GLuint uniforms[NUM_UNIFORMS]; // Amount of uniforms
};

