#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown)
	:window(NULL), renderer(NULL), mode() //initialize memory
{
	/* Get current display mode to initialize a window with native screen resolution. */
	if(SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		std::cout << "Failed to get current display mode. Error: " << SDL_GetError() << std::endl;
	}

	if(isFullScreen)
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, windowShown); //title, xpos, ypos, width, height, and show the window.
		setFullScreen();
	}
	else
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, windowShown); //title, xpos, ypos, width, height, and show the window.
	}

	if(window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.

	if(renderer == NULL)
	{
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}
}
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::setFullScreen()
{
	SDL_SetWindowSize(window, mode.w, mode.h);
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}
