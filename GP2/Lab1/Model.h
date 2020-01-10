#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

class Model
{
public:
	Model(Transform transform, Mesh* mesh, Texture* texture)
	{
		this->mesh = mesh;
		this->texture = texture;
	}

	~Model()
	{
		delete mesh;
	}
private:
	Mesh* mesh;
	Texture* texture;
};