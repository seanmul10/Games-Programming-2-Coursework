#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Audio.h"
#include "Ball.h"
#include "transform.h"
#include <iostream>
#include <string>
#include <SDL\SDL.h>
#include <GL/glew.h>

enum class GameState { PLAY, EXIT }; // Game state enumerator

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void Run(); // Start the game loop

private:
	void InitSystems(); // Initialise the game (meshes, textures etc.)
	void RunGameLoop(); // Runs while the game is running
	void CollisionDetection(); // Check if objects are colliding
	void ProcessInputs(); // Process inputs from the player
	void Update(); // Update transforms and other non-draw code
	void Draw(); // Draw the game

	bool CheckCollision(glm::vec3 aPosition, float aRadius, glm::vec3 bPosition, float bRadius); // Check for collisions

	Display display; // The game display
	GameState state; // The current state of the game loop
	Mesh mesh; // Meshes
	Mesh mesh2;
	Mesh mesh3;
	Texture texture; // Single texture
	Shader shader;
	Audio audio; // For audio functions
	Camera mainCamera; // The main camera in the world

	Ball ball; // The ball object

	std::vector<GLuint> textures; // List of textures to use in the game
	std::vector<unsigned int> sounds; // List of sounds that can be used in the game

	float i; // Counter for the game loop
};