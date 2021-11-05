//press F7 to compile in Sublime Text <- so Hal remembers what the key is

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "kiss_sdl.h"
#include "RenderWindow.hpp"
#include "RtMidi.h"

bool programRunning = true;

int main(int argc, char* args[])
{
	//init Midi object, will be wrapped in it's own init function later. 
	try {
    RtMidiIn midiin;
  } catch (RtMidiError &error) {
    // Handle the exception here
    error.printMessage();
  }

  ///Initialze SDL stuff
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