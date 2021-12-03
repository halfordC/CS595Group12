#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


#include "UserGUI.hpp"
//#include "kiss_sdl.h"
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "Scene.h"

using std::cout; using std::cin;
using std::endl; using std::string;


UserGUI::UserGUI(char* p_title, MidiModule* myMidiModule) : renderer(NULL)
{
	kissGUI = new myKissGUI();
	kissGUI->kiss_array_new(&objects );
	renderer = kissGUI->kiss_init(p_title, &objects, 640, 480);



	char message[KISS_MAX_LENGTH];
	strcpy(message, "Hello World!");

	
	kissGUI->fillConnectedMidiDevices(&connectedMidiDevices, myMidiModule); // fill midi device dropdown

	kissGUI->kiss_array_new(&objects); //init all the stuff that kiss expects in an array
	kissGUI->kiss_window_new(&window, NULL, 1, 0, 0, 640, 480);


	//We want to instantite the first scene after we instantiate the window. 
	sceneIndex = 0;
	addSceneIndex = 0;
	Scene* firstScene = new Scene(kissGUI, &window);
	sceneArray[0] = firstScene;

	kissGUI->kiss_tab_new(&(sceneTab[0]), &window, "Scene 1", 50, 34);
	
	kissGUI->kiss_tab_new(&plusTab, &window, "+", 125, 34);

	kissGUI->kiss_combobox_new(&midiDeviceDrop, &window, "Midi Devices", &connectedMidiDevices, 490,20,120,100);

	kissGUI->kiss_button_new(&addBinding, &window, "+", 40, 370);

	kissGUI->kiss_button_new(&startButton, &window, "Start", 550, 430);

	kissGUI->kiss_upbutton_new(&scrollUp, &window, 530, 65);
	kissGUI->kiss_downbutton_new(&scrollDown, &window, 530, 340);

	label.textcolor.r = 255;
	window.visible = 1;
	
	cout << "GUI started" << endl;
}

/* This method will render the sprites that are held in the sprite vector to the screen.
	 Sprites are going to be rendered with the center of their rect at the x and y percentages that are
	 stored. This method should be called by main in the main program loop. */
void UserGUI::render()
{
	SDL_RenderClear(renderer);

	kissGUI->kiss_window_draw(&window, renderer);

	kissGUI->kiss_window_draw(&(sceneArray[sceneIndex]->sceneWindow), renderer);
	
	kissGUI->kiss_button_draw(&addBinding, renderer); //If it's a button, draw it first.
	kissGUI->kiss_tab_draw(&plusTab, renderer);
	sceneArray[sceneIndex]->render(renderer);
	kissGUI->kiss_tab_draw(&(sceneTab[0]), renderer);
	
	kissGUI->kiss_button_draw(&startButton, renderer);
	
	kissGUI->kiss_combobox_draw(&midiDeviceDrop, renderer);

	kissGUI->kiss_upbutton_draw(&scrollUp, renderer);
	kissGUI->kiss_downbutton_draw(&scrollDown, renderer);
	

	SDL_RenderPresent(renderer);
}

void UserGUI::cleanUp()
{
	SDL_DestroyRenderer(renderer);
}

void UserGUI::guiEvent(SDL_Event* e, MidiModule* myMidiModule, RenderWindow myRenderWindow)
{
	for (int i = 0; i <= sceneIndex; ++i)
	{
		sceneArray[i]->sceneEvent(e, myMidiModule, myRenderWindow);
	}
}

void UserGUI::scrollUpEvent(SDL_Event* e)
{
	int draw = 1;
	if (kissGUI->kiss_upbutton_event(&scrollUp, e, &draw)) 
	{

	}
}

void UserGUI::scrollDownEvent(SDL_Event* e)
{
	int draw = 1;
	if (kissGUI->kiss_downbutton_event(&scrollDown, e, &draw)) 
	{

	}
}

void UserGUI::selectMidiDropdownEvent(SDL_Event* e, MidiModule* myMidiModule)
{
	int draw = 1;
	
	if (kissGUI->kiss_combobox_event(&midiDeviceDrop, e, &draw)) 
	{
		int length = midiDeviceDrop.textbox.array->length;
		for (int i = 0; i<length; i++) 
		{
			void** p = midiDeviceDrop.textbox.array->data + i;
			void* s = *p;
			char* contents = (char*)s;

			bool result = kissGUI->dropBoxcompare(midiDeviceDrop.entry, contents);
			if (result)
			{
				//we need to connect to the midi device here. 
				string connect(contents); //to convert to a std::string, just give a char* as a constructor parameter. 

				std::cout << connect << std::endl;

				myMidiModule->connectToMidiDevice(connect);
			}
		}
	}
}

void UserGUI::addBindingEvent(SDL_Event* e)
{
	int draw = 1;
	if (kissGUI->kiss_button_event(&addBinding, e, &draw))
	{
		sceneArray[sceneIndex]->addImg();
		
	}
}