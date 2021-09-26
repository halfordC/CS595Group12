//press F7 to compile in Sublime Text <- so Hal remembers what the key is

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

bool programRunning = true;

int main(int argc, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init has Failed. SDL_ERROR:  " << SDL_GetError() << std::endl;
	}

	if(!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_Init has Failed. SDL_ERROR:  " << SDL_GetError() << std::endl;
	}

	RenderWindow window("FirstWindow", 640, 480);

	SDL_Event event;

	while(programRunning)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				programRunning = false;
			}

		}

	} 
	
	window.cleanUp();
	SDL_Quit();

	return 0;
	
}