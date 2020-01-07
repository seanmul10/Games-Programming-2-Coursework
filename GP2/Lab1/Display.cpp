#include "Display.h"

Display::Display()
{
	// Initialise window and context
	sdlWindow = nullptr;
	glContext = nullptr;
}

void Display::InitDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer  

	// Create the window
	sdlWindow = SDL_CreateWindow(
		"Game Window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int)screenWidth, (int)screenHeight,
		SDL_WINDOW_OPENGL
	);

	// If the window is an invalid pointer, return an error
	if (sdlWindow == nullptr)
	{
		PrintError("Failed to create window");
	}

	glContext = SDL_GL_CreateContext(sdlWindow); // Create context for the window

	// If the context is invalid, return an error
	if (glContext == nullptr)
	{
		PrintError("Failed to create SDL_GL context");
	}

	// Initialise GLEW, return an error if this fails
	if (glewInit() != GLEW_OK)
	{
		PrintError("Couldn't initialise GLEW");
	}

	glEnable(GL_DEPTH_TEST); // Enable z-buffering 
	glEnable(GL_CULL_FACE); // Faces not in view of the camera are not drawn

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void Display::SwapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow);
}

void Display::ClearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the colour and depth buffers
}

float Display::GetScreenWidth()
{
	return screenWidth;
}

float Display::GetScreenHeight()
{
	return screenHeight;
}

void Display::PrintError(char* errorMessage)
{
	std::cout << errorMessage << std::endl;
	std::cout << "Press any key to quit";
	std::cin.get();
	SDL_Quit();
}

Display::~Display()
{
	// Delete the context then window
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}