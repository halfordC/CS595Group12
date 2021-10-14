#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>

#include "RenderWindow.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;

/*
#include <stdint.h>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

typedef struct
{
	fs::path resourcePath;
	float x, y, size, alpha;
	int rotation;
} sprite;
*/

RenderWindow::RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown)
	:mode(), window(NULL), renderer(NULL), cwd()
{
	/* Get current display mode to initialize a window with native screen resolution. */
	if(SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		cout << "Failed to get current display mode. Error: " << SDL_GetError() << endl;
	}

	if(isFullScreen)
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, windowShown); //title, xpos, ypos, width, height, and show the window.
		enterViewMode();
	}
	else
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, windowShown); //title, xpos, ypos, width, height, and show the window.
	}

	if(window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.

	if(renderer == NULL)
	{
		cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
	}

	/* Initialize the CWD to the scenes folder. Creates one if none exists. */
	cwd = fs::current_path();

	#ifdef __APPLE__
		cwd += "/scenes";
	#elif _WIN32
		cwd += "\\scenes";
	#endif

	if(!fs::exists(cwd))
	{
			fs::create_directory(cwd);
	}
}
void RenderWindow::enterViewMode()
{
	SDL_SetWindowSize(window, mode.w, mode.h);
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
