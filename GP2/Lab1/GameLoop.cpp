#include "GameLoop.h"

Transform transform;

GameLoop::GameLoop()
{
	state = GameState::PLAY;
	Display* display = new Display();
	// Meshes
	Mesh* mesh();
	
	// Textures
	Texture* texture();

	// Shaders
	Shader* shader();

	i = 0.0f;
}

void GameLoop::Run()
{
	InitSystems();
	RunGameLoop();
}

void GameLoop::InitSystems()
{
	display.InitDisplay();
	// Add meshes
	mesh.LoadModel("..\\res\\monkey3.obj");

	// Add textures
	texture.InitTexture("bricks.jpg");

	// Add shaders
	shader.InitShader("shader");

	// Set camera
	mainCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)display.GetScreenWidth() / display.GetScreenHeight(), 0.01f, 1000.0f);
}


void GameLoop::RunGameLoop()
{
	while (state == GameState::PLAY)
	{
		ProcessInputs();
		Update();
		Draw();
	}
}

void GameLoop::ProcessInputs()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			state = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				// Move forward
				mainCamera.MoveForward(1);
				break;
			case SDLK_s:
				// Move backward
				mainCamera.MoveForward(-1);
				break;
			case SDLK_a:
				// Move left
				mainCamera.MoveLeft(1);
				break;
			case SDLK_d:
				// Move right
				mainCamera.MoveLeft(-1);
				break;
			case SDLK_LEFT:
				// Turn left
				mainCamera.TurnLeft(0.1);
				break;
			case SDLK_RIGHT:
				// Turn right
				mainCamera.TurnLeft(-0.1);
				break;
			case SDLK_UP:
				// Pitch up
				mainCamera.Pitch(-0.1);
				break;
			case SDLK_DOWN:
				// Pitch down
				mainCamera.Pitch(0.1);
				break;
			}
			break;
		}
	}
}

void GameLoop::Update()
{
	// Set transform
	transform.SetPos(glm::vec3(0, -1, 0));
	transform.SetRot(glm::vec3(0, 180, 0));
	transform.SetScale(glm::vec3(1, 1, 1));

	mesh.UpdateSphere(*transform.GetPos(), 0.62f);

	// Shaders
	shader.Bind(); // Bind shader
	shader.Update(transform, mainCamera); // Update shader

	// Textures
	texture.Bind(0); // Bind the texture

	if (CheckCollision(mainCamera.GetPosition(), 2, *transform.GetPos(), 0.62f))
	{
		display.ClearDisplay(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		display.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	}

	i += 0.01f; // Increment gameloop counter
}

void GameLoop::Draw()
{
	display.ClearDisplay(0.0f, 0.0f, 0.0f, 1.0f); // Background colour of the game window

	// Draw meshes
	mesh.Draw();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	display.SwapBuffer();
}

bool GameLoop::CheckCollision(glm::vec3 aPosition, float aRadius, glm::vec3 bPosition, float bRadius)
{
	float distance = sqrt(pow(bPosition.x - aPosition.x, 2) + pow(bPosition.y - aPosition.y, 2) + pow(bPosition.z - aPosition.z, 2));
	if (distance - aRadius - bRadius < 0)
	{
		return true;
	}
	return false;
}

GameLoop::~GameLoop()
{

}