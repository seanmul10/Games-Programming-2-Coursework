#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>

class Display
{
public:
	Display();
	~Display();

	void InitDisplay(); // Initialise the display
	void SwapBuffer(); // Swap the buffers
	void ClearDisplay(float r, float g, float b, float a); // Clear the display

	// Return the screen dimensions
	float GetScreenWidth();
	float GetScreenHeight();

private:
	void PrintError(char*); // Print an error message and quits SDL

	SDL_GLContext glContext; // Context variable
	SDL_Window* sdlWindow; // Pointer to window

	//Screen dimensions
	const float screenWidth = 1024.0f;
	const float screenHeight = 768.0f;
};

