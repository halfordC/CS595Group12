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

using std::cout; using std::cin;
using std::endl; using std::string;

extern MidiModule* myMidiModule;


UserGUI::UserGUI(char* p_title) : renderer(NULL)
{
	kissGUI = new myKissGUI();
	kissGUI->kiss_array_new(&objects );
	renderer = kissGUI->kiss_init(p_title, &objects, 640, 480);

	char message[KISS_MAX_LENGTH];
	strcpy(message, "Hello World!");

	
	kissGUI->fillConnectedMidiDevices(&connectedMidiDevices); // fill midi device dropdown
	kissGUI->fillMidiParam(&midiParamList); //fill midi param dropdown
	kissGUI->fillImageParam(&imageParamList); //fill midi param dropdown
	
	kissGUI->kiss_array_new(&objects); //init all the stuff that kiss expects in an array
	kissGUI->kiss_window_new(&window, NULL, 1, 0, 0, 640, 480);
	/*kissGUI->kiss_label_new(&label, &window, message, window.rect.w / 2 - strlen(message) *
		kissGUI->kiss_textfont.advance / 2, window.rect.h / 2 - (kissGUI->kiss_textfont.fontheight +
			2 * kissGUI->kiss_normal.h) / 2);*/

	kissGUI->kiss_combobox_new(&midiDeviceDrop, &window, "Midi Devices", &connectedMidiDevices, 490,20,120,100);
	kissGUI->kiss_combobox_new(&imgParam, &window, "Image Param", &imageParamList, 40, 140, 120, 100);
	kissGUI->kiss_combobox_new(&midiParam, &window, "Midi Param", &midiParamList, 180, 140, 110, 100);
	kissGUI->kiss_button_new(&noteButton, &window, "Note/CC", 310, 146);
	kissGUI->kiss_button_new(&addBinding, &window, "+", 40, 220);

	kissGUI->kiss_button_new(&startButton, &window, "Start", 550, 430);

	kissGUI->kiss_entry_new(&filePathEntry, &window, 1, "FilePath", 40, 100, 450);


	kissGUI->kiss_button_new(&browsePath, &window, "Browse", 500, 105);

	kissGUI->kiss_button_new(&midiLearn, &window, "Listen", 390, 146);

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
	/*kissGUI->kiss_label_draw(&label, renderer);*/
	kissGUI->kiss_button_draw(&browsePath, renderer);
	kissGUI->kiss_combobox_draw(&midiDeviceDrop, renderer);
	kissGUI->kiss_combobox_draw(&imgParam, renderer);
	kissGUI->kiss_combobox_draw(&midiParam, renderer);
	kissGUI->kiss_button_draw(&noteButton, renderer);
	kissGUI->kiss_button_draw(&addBinding, renderer);

	kissGUI->kiss_button_draw(&startButton, renderer);
	kissGUI->kiss_entry_draw(&filePathEntry, renderer);
	
	kissGUI->kiss_button_draw(&midiLearn, renderer);

	SDL_RenderPresent(renderer);
}

void UserGUI::cleanUp()
{
	SDL_DestroyRenderer(renderer);
}


void UserGUI::selectMidiDropdownEvent(SDL_Event* e)
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

				myMidiModule->connectToMidiDevice(connect);
			}
		}
	}
}

void UserGUI::selectMidiParamEvent(SDL_Event* e) 
{

	int draw = 1;
	if (kissGUI->kiss_combobox_event(&midiParam,e,&draw)) 
	{
		//An item has been clicked! but which one?
		//normally, we would use bsearch, but we can't really do that in c++ with how this is setup.
		//so we must mannualy search through and find the entry.
		int length = midiParam.textbox.array->length;
		for (int i = 0; i< length; i++) 
		{
			void** p = midiParam.textbox.array->data+i; //data is of type void pointer pointer
			void* s = *p; //derefference p, and get S. 
			char* contents = (char*)s; //contents is the char* string stored at data location i.;

			//now we need to compare this string with the string that was clicked. where does that string come from?
			bool result = kissGUI->dropBoxcompare(midiParam.entry, contents);
			if (result) 
			{
				//We are at the text box entry index of what we clicked on, do the clicked action. 
				//so it is important we know what is here. 

				listenFilter = i;

			}
		}
	}

}


void UserGUI::typeFilePath(SDL_Event* e) 
{
	int draw = 1;
	if (kissGUI->kiss_entry_event(&filePathEntry, e, &draw)) 
	{
		char* inputText = filePathEntry.text;
		//do stuff with inputText
	}
}
