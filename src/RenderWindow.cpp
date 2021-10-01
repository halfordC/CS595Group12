#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "renderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL) //initialize memory
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN); //title, xpos, ypos, width, height, and show the window. 
	
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