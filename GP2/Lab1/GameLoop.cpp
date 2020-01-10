#include "GameLoop.h"

Transform transform;
Transform transform2;
Transform transform3;

float degree = 0;

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

	//Audio
	Audio* audio();

	// Golf ball
	Ball* ball();

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
	mesh.LoadModel("grass.obj");
	mesh2.LoadModel("table.obj");
	mesh3.LoadModel("golf_ball.obj");

	// Add textures
	textures.push_back(texture.InitTexture("grass.jpg"));
	texture.Bind(0);
	textures.push_back(texture.InitTexture("wood.png"));
	texture.Bind(1);
	textures.push_back(texture.InitTexture("golf_ball2.jpg"));
	texture.Bind(2);

	// Add shaders
	shader.InitShader("shader");

	// Load sounds
	sounds.push_back(audio.loadSound("..\\res\\birds.wav"));
	sounds.push_back(audio.loadSound("..\\res\\bounce.wav"));
	sounds.push_back(audio.loadSound("..\\res\\ping.wav"));

	// Set camera
	mainCamera.initCamera(glm::vec3(0, 40, -70), 70.0f, (float)display.GetScreenWidth() / display.GetScreenHeight(), 0.01f, 10000.0f);
	mainCamera.Pitch(0.3);
}


void GameLoop::RunGameLoop()
{
	audio.playSound(sounds[0]);
	while (state == GameState::PLAY)
	{
		ProcessInputs();
		CollisionDetection();
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
				mainCamera.MoveForward(10);
				break;
			case SDLK_s:
				// Move backward
				mainCamera.MoveForward(-5);
				break;
			case SDLK_a:
				// Move left
				mainCamera.MoveLeft(5);
				break;
			case SDLK_d:
				// Move right
				mainCamera.MoveLeft(-5);
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
			case SDLK_SPACE:
				if (ball.Launch(0.5f))
				{
					audio.playSound(sounds[2]);
				}
				break;
			}
			break;
		}
	}
}

// Check for possible collisions
void GameLoop::CollisionDetection()
{
	if (CheckCollision(*transform2.GetPos(), 7.25f, *transform3.GetPos(), 1.5f))
	{
		if (ball.Impact())
		{
			audio.playSound(sounds[1]);
		}
	}
}

void GameLoop::Update()
{
	// Set transforms
	//Mesh 1
	transform.SetPos(glm::vec3(0, 0, 0));
	transform.SetRot(glm::vec3(4.7, 0, 0));
	transform.SetScale(glm::vec3(0.1, 0.1, 0.1));

	//Mesh 2
	transform2.SetPos(glm::vec3(0, 5, 0));
	transform2.SetRot(glm::vec3(0, 0.2, 0));
	transform2.SetScale(glm::vec3(1, 1, 1));

	//Mesh 3
	transform3.SetPos(ball.position);
	transform3.SetRot(glm::vec3(0, -1.5, 0));
	transform3.SetScale(glm::vec3(0.1, 0.1, 0.1));

	ball.Update();

	i++; // Increment gameloop counter
}

void GameLoop::Draw()
{
	display.ClearDisplay(0.56f, 0.79f, 0.89f, 1.0f); // Background colour of the game window

	shader.Bind(); // Bind shader
	shader.Update(transform, mainCamera);
	mesh.Draw(textures[0]);

	shader.Bind(); // Bind shader
	shader.Update(transform2, mainCamera);
	mesh2.Draw(textures[1]);

	shader.Bind(); // Bind shader
	shader.Update(transform3, mainCamera);
	mesh3.Draw(textures[2]);

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