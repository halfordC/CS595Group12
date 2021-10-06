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

	/* Last flag must be SDL_WINDOW_SHOWN or SDL_WINDOW_HIDDEN */
	RenderWindow sceneViewWindow("Scene View Window", false, 400, 400, SDL_WINDOW_HIDDEN);
	RenderWindow guiWindow("GUI Window", false, 400, 400, SDL_WINDOW_SHOWN);

	SDL_Event event;
	Uint32 lastTime = 0;
	Uint32 currentTime;
	while(programRunning)
	{
		currentTime = SDL_GetTicks();
		if(currentTime > lastTime + 7500)
		{
			programRunning = false;
		}
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
    	{
    		case SDL_WINDOWEVENT:
        	switch(event.window.event)
        	{
        		case SDL_WINDOWEVENT_ENTER:
							sceneViewWindow.setFullScreen();
            	break;
        	}
        break;
    	}
		}
	}

	sceneViewWindow.cleanUp();
	guiWindow.cleanUp();
	SDL_Quit();

	return 0;

}
