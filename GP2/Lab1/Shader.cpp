#include "Shader.h"

Shader::Shader()
{

}

void Shader::InitShader(const std::string& filename)
{
	program = glCreateProgram(); // Create the shader program

	// Create vertex and fragment shader
	shaders[0] = CreateShader(LoadShader("shader.vert"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader("shader.frag"), GL_FRAGMENT_SHADER);

	// Attach each shader to the shader program
	for (int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	// Attributes
	glBindAttribLocation(program, 0, "position"); // associate attribute variable with our shader program attribute (in this case attribute vec3 position;)
	glBindAttribLocation(program, 1, "texCoord");

	// Create executables that will run on the GPU shaders, if it doesn't work, return an error
	glLinkProgram(program);	
	CheckForShaderError(program, GL_LINK_STATUS, true, "Error: Shader program linking failed"); // cheack for error

	// Check the validity of the shader program, if invalid, return an error
	glValidateProgram(program);
	CheckForShaderError(program, GL_VALIDATE_STATUS, true, "Error: Shader program not valid");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
}

std::string Shader::LoadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(("..\\res\\" + filename).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	// Create shader with a given type
	GLuint shader = glCreateShader(type);

	// Return an error if the shader is null
	if (shader == NULL)
	{
		std::cerr << "Error type creation failed " << type << std::endl;
	}

	// Fornat the filename string
	const GLchar* stringSource[1]; //convert strings into list of c-strings
	stringSource[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	// Get source code and have opengl compile it
	glShaderSource(shader, 1, stringSource, lengths); //send source code to opengl
	glCompileShader(shader); //get open gl to compile shader code

	// If there was en error compiling the shader code, return an error
	CheckForShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!"); //check for compile error

	return shader;
}

void Shader::Bind()
{
	// Binds the shader program
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	// Update the game view by getting the from the intended projection of the world
	glm::mat4 mvp = camera.GetViewProjection() * transform.GetModel();;
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GLU_FALSE, &mvp[0][0]);
}

void Shader::CheckForShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

Shader::~Shader()
{
	// Detach and delete each shader
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	// Delete the shader program
	glDeleteProgram(program);
}