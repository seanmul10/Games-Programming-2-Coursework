#pragma once

#include "glm/glm.hpp"

enum class State { STOPPED, MOVING };

class Ball
{
private:
	const float gravity = -0.005f; // Gravity amount

	glm::vec3 velocity; // The current velocity of the ball
	State state; // The state of the balls movement

public:
	Ball();

	bool Launch(float force); // Launches the ball upwards with a force
	void Update(); // Called in the games Update method to apply physics
	bool Impact(); // Called when the ball collides with an object

	glm::vec3 position; // The position of the ball
};
