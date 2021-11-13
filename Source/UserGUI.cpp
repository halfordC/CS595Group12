#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "UserGUI.hpp"
//#include "kiss_sdl.h"
#include "myKissGui.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;


UserGUI::UserGUI(char* p_title) : renderer(NULL)
{
	kissGUI = new myKissGUI();
	kissGUI->kiss_array_new(&objects );
	renderer = kissGUI->kiss_init(p_title, &objects, 640, 480);

	char message[KISS_MAX_LENGTH];
	strcpy(message, "Hello World!");
	
	kissGUI->fillConnectedMidiDevices(&connectedMidiDevices); // fill dropdown

	
	kissGUI->kiss_array_new(&objects); //init all the stuff that kiss expects in an array
	kissGUI->kiss_window_new(&window, NULL, 1, 0, 0, 640, 480);
	/*kissGUI->kiss_label_new(&label, &window, message, window.rect.w / 2 - strlen(message) *
		kissGUI->kiss_textfont.advance / 2, window.rect.h / 2 - (kissGUI->kiss_textfont.fontheight +
			2 * kissGUI->kiss_normal.h) / 2);*/

	kissGUI->kiss_combobox_new(&midiDeviceDrop, &window, "Midi Devices", &connectedMidiDevices, 490,20,120,100);
	midiDeviceDrop.visible = 1;
	kissGUI->kiss_combobox_new(&imgParam, &window, "Image Param", &imageParamList, 40, 140, 120, 100);
	imgParam.visible = 1;
	kissGUI->kiss_combobox_new(&midiParam, &window, "Midi Param", &midiParamList, 180, 140, 110, 100);
	midiParam.visible = 1;
	kissGUI->kiss_button_new(&noteButton, &window, "Note/CC", 310, 146);
	noteButton.visible = 1;
	kissGUI->kiss_button_new(&addBinding, &window, "+", 40, 220);
	addBinding.visible = 1;

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
	kissGUI->kiss_combobox_draw(&midiDeviceDrop, renderer);
	kissGUI->kiss_combobox_draw(&imgParam, renderer);
	kissGUI->kiss_combobox_draw(&midiParam, renderer);
	kissGUI->kiss_button_draw(&noteButton, renderer);
	kissGUI->kiss_button_draw(&addBinding, renderer);
	SDL_RenderPresent(renderer);
}

void UserGUI::cleanUp()
{
	SDL_DestroyRenderer(renderer);
}


void UserGUI::selectMidiDropdownEvent(SDL_Event* e)
{
	int draw = 1;
	void** p, * s;
	int i;
	if (kissGUI->kiss_combobox_event(&midiDeviceDrop, e, &draw)) 
	{
		
/*
		if ((p = (void**)bsearch(&s, midiDeviceDrop.textbox.array->data,
			midiDeviceDrop.textbox.array->length, sizeof(void*),
			kiss_string_compare))) {
			i = p - combobox->textbox.array->data;


		}
		else
			std::cout << "data not found" << std::endl;
			//strcpy(stext, "Data not found");
			*/
	}


}
