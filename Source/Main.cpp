#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
//#include <unistd.h>
#include <filesystem>

#include "kiss_sdl.h"
#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "midiModule.h"

using std::cout; using std::cin;
using std::endl; using std::string;

bool programRunning = true;
MidiModule* myMidiModule = new MidiModule();

int main(int argc, char* args[])
{

	///Initialze SDL stuff
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		cout << "SDL_Init has Failed. SDL_ERROR:  " << SDL_GetError() << endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
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

	/* Start paths to simulate directory changing. */
	int secondCounter = 0;
	bool one = true;
	std::filesystem::path dir1 = std::filesystem::current_path();
	std::filesystem::path dir2 = std::filesystem::current_path();

#ifdef __APPLE__
	dir1 += "/scenes/scene1";
	dir2 += "/scenes/scene2";
#elif _WIN32
	dir1 += "\\scenes\\scene1";
	dir2 += "\\scenes\\scene2";
#endif
	/* End paths to simulate directory changing. */

	while (programRunning)
	{
		/* Do Events */
		currentTime = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				programRunning = false;
			}
		}
		/* Do updates */
		/* Do renders */
		if (((float)(currentTime - lastTime)) >= (16.67f * fpsCounter))
		{
			sceneViewWindow.render();
			fpsCounter++;
		}
		upsCounter++;
		if (currentTime - lastTime >= 1000)
		{
			cout << "FPS: " << fpsCounter << " | Updates: " << upsCounter << endl;
			lastTime = currentTime;
			fpsCounter = 0;
			upsCounter = 0;

			/* Simulate directory change every 4 seconds. */
			secondCounter++;
			if (secondCounter == 4)
			{
				if (one)
				{
					one = false;
					sceneViewWindow.setSceneDirectory(dir1);
				}
				else if (!one)
				{
					one = true;
					sceneViewWindow.setSceneDirectory(dir2);
				}
				secondCounter = 0;
			}
		}
	}
	/* End Program Loop */

	sceneViewWindow.cleanUp();
	SDL_Quit();

	return 0;

}
