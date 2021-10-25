//press F7 to compile in Sublime Text <- so Hal remembers what the key is
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <filesystem>

#include "kiss_sdl.h"
#include "RenderWindow.hpp"
#include "RtMidi.h"
#include "Sprite.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

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
		cout << "SDL_Init has Failed. SDL_ERROR:  " << SDL_GetError() << endl;
	}

	if(!(IMG_Init(IMG_INIT_PNG)))
	{
		cout << "IMG_Init has Failed. SDL_ERROR:  " << SDL_GetError() << endl;
	}

	RenderWindow sceneViewWindow("Scene View Window");
	sceneViewWindow.enterViewMode();
	//sceneViewWindow.openSceneFolder();

	/* Start Program Loop */
	SDL_Event event;
	unsigned int lastTime = SDL_GetTicks();
	unsigned int currentTime;
	int fpsCounter = 0;
	int upsCounter = 0;
	while(programRunning)
	{
		/* Do Events */
		currentTime = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
	    {
				 case SDL_MOUSEBUTTONDOWN:
				 	programRunning = false;
	    }
		}
		/* Do updates */
		/* Do renders */
		if(((float)(currentTime - lastTime)) >= (16.67f * fpsCounter))
		{
			sceneViewWindow.render();
			fpsCounter++;
		}
		upsCounter++;
		if(currentTime - lastTime >= 1000)
		{
			cout << "FPS: " << fpsCounter << " | Updates: " << upsCounter << endl;
			lastTime = currentTime;
			fpsCounter = 0;
			upsCounter = 0;
		}
	}
	/* End Program Loop */

	sceneViewWindow.cleanUp();
	SDL_Quit();

	return 0;

}
