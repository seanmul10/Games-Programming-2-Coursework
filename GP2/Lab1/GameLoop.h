#include "Display.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Audio.h"
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
	void ProcessInputs(); // Process inputs from the player
	void Update(); // Update transforms and other non-draw code
	void Draw(); // Draw the game

	bool CheckCollision(glm::vec3 aPosition, float aRadius, glm::vec3 bPosition, float bRadius); // Check for collisions

	Display display; // The game display
	GameState state; // The current state of the game loop
	Mesh mesh[2]; // Array of meshes
	Texture texture; // Single texture
	Shader shader;
	Audio audio; // For audio functions
	Camera mainCamera; // The main camera in the world

	unsigned int sounds[10];

	float i; // Counter for the game loop
};