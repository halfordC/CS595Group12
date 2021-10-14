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

	/* Last flag must be SDL_WINDOW_SHOWN or SDL_WINDOW_HIDDEN */
	RenderWindow sceneViewWindow("Scene View Window", false, 400, 400, SDL_WINDOW_HIDDEN);
	RenderWindow guiWindow("GUI Window", false, 400, 400, SDL_WINDOW_SHOWN);
	/* End KISS_SDL fuckery */


	/* Start Program Loop */
	SDL_Event event;
	while(programRunning)
	{
		/* Do Events */
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
	    {
	    	case SDL_WINDOWEVENT:
	        switch(event.window.event)
	        {
	        	case SDL_WINDOWEVENT_ENTER:
							#ifdef __APPLE__
								string command = "open " + sceneViewWindow.cwd.string();
							#elif _WIN32
								string command = "explorer " + sceneViewWindow.cwd.string();
							#endif
							system(command.c_str());
							programRunning = false;
	            break;
	        }
	       break;
	    }
			/* Do Renders */
		}
	}
	/* End Program Loop */

	sceneViewWindow.cleanUp();
	guiWindow.cleanUp();
	SDL_Quit();

	return 0;

}
