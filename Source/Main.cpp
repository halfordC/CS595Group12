#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <filesystem>

#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "midiModule.h"
#include "UserGUI.hpp"
#include "myKissGui.hpp"
#include "Translator.h"

using std::cout; using std::cin;
using std::endl; using std::string;

uint8_t numDevices = 0;
bool programRunning = true;


int main(int argc, char* args[])
{

	//init Midi Module, get midi input
	MidiModule* myMidiModule = new MidiModule();

	
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
	//sceneViewWindow.enterViewMode();
	UserGUI gui("Scene Editor", myMidiModule);

	Translator* translator = new Translator(&gui);

	SDL_Event event;
	unsigned int lastTime = SDL_GetTicks();
	unsigned int currentTime;
	int fpsCounter = 0;
	int upsCounter = 0;

	/* Start paths to simulate directory changing.*/
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
		// Do Events
		currentTime = SDL_GetTicks();
		
		while ( SDL_PollEvent(&event) != 0 )
		{
      
			//GUI callback events go here.
			gui.selectMidiDropdownEvent(&event, myMidiModule);
			gui.addBindingEvent(&event);
			gui.removeBindingEvent(&event);
			gui.guiEvent(&event, myMidiModule, &sceneViewWindow, sceneViewWindow.renderer);
			gui.addSceneEvent(&event);
			gui.sceneTabEvent(&event);
			gui.scrollEvent(&event);
			gui.startEvent(&event, &sceneViewWindow);
			switch (event.type)
			{
			case SDL_QUIT:
				programRunning = false;
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					programRunning = false;
					break;
				default:
					break;
				}
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_F11:
					sceneViewWindow.toggleFullscreen();
					break;
				case SDLK_ESCAPE:
					sceneViewWindow.toggleFullscreen();
					break;
				}
			default:
				break;
			}
		}

		/* Do updates */
		/* Do renders */
		if (((float)(currentTime - lastTime)) >= (16.67f * fpsCounter))
		{
			sceneViewWindow.render(gui.sceneIndex);
			gui.render();
			fpsCounter++;
			translator->translate(&sceneViewWindow, myMidiModule);
			/*
			if (myMidiModule->hasNewMidiMessage())
			{
				std::vector<juce::MidiMessage> inBuffer = myMidiModule->getMidiBuffer();

				for (int i = 0; i < inBuffer.size(); i++)
				{
					std::cout << "message Recieved: " << myMidiModule->printMessage(inBuffer[i]) << std::endl;

				}
				myMidiModule->messagesParsed(); //this clears the flag, and waits for a new message. 

			}
			*/
			
		}
		upsCounter++;
		/*
		if (currentTime - lastTime >= 1000)
		{
			cout << "FPS: " << fpsCounter << " | Updates: " << upsCounter << endl;
			lastTime = currentTime;
			fpsCounter = 0;
			upsCounter = 0;

			// Simulate directory change every 4 seconds.
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
		*/

	}

	myMidiModule->~MidiModule();
	SDL_Quit();

		/* End Program Loop */
	
	myMidiModule->~MidiModule();
	sceneViewWindow.cleanUp();
	gui.cleanUp();
	
	

	return 0;

}
