#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Sphere
{
public:
	Sphere() {}

	Sphere(glm::vec3 position, float radius)
	{
		this->position = position;
		this->radius = radius;
	}

	glm::vec3 GetPosition()
	{
		return position;
	}

	float GetRadius()
	{
		return radius;
	}

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
	}

	void SetPosition(float x, float y, float z)
	{
		this->position = position;
	}

	void SetRadius(float radius)
	{
		this->radius = radius;
	}

private:
	glm::vec3 position;
	float radius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	//void InitMesh();
	void LoadModel(const std::string&); // Loads model from an address
	void InitModel(const IndexedModel&); // Initialises the model for use

	void Draw(GLuint texture); // Draws the model on the screen with the specified texture

	Sphere sphereMesh;

	void UpdateSphere(glm::vec3, float);

	glm::vec3 GetSpherePosition();
	float GetSphereRadius();

private:
	enum { POSITION_VERTEX_BUFFER, TEX_COORD_VB, NORMAL_VB, INDEX_VB, NUM_BUFFERS };

	unsigned int drawCount;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];
};