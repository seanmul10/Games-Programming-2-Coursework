#include "Ball.h"

Ball::Ball()
{
	// Setup initial position and velocity
	position = glm::vec3(0.0f, 20.0f, 0.0f);
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	state = State::MOVING;
}

bool Ball::Launch(float force)
{
	if (state == State::STOPPED)
	{
		state = State::MOVING;
		velocity = glm::vec3(0.0f, force, 0.0);
		return true;
	}
	return false;
}

void Ball::Update()
{
	if (state == State::MOVING)
	{
		position = position + velocity;
		velocity += glm::vec3(0.0f, gravity, 0.0f); // Apply gravity
	}
	if (state == State::STOPPED)
	{
		velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}

bool Ball::Impact()
{
	if (state == State::MOVING && velocity.y < 0)
	{
		state = State::STOPPED;
		return true;
	}
	return false;
}