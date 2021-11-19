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

	kiss_array textArray;
	kissGUI->kiss_array_new(&textArray);

	kissGUI->kiss_array_append(&textArray, 0, "Thing1");
	kissGUI->kiss_array_append(&textArray, 1, "Thing2");
	
	kissGUI->kiss_array_new(&objects); //init all the stuff that kiss expects in an array
	kissGUI->kiss_window_new(&window, NULL, 1, 0, 0, 640, 480);
	/*kissGUI->kiss_label_new(&label, &window, message, window.rect.w / 2 - strlen(message) *
		kissGUI->kiss_textfont.advance / 2, window.rect.h / 2 - (kissGUI->kiss_textfont.fontheight +
			2 * kissGUI->kiss_normal.h) / 2);*/
	kissGUI->kiss_combobox_new(&midiDeviceDrop, &window, "Midi Devices", &textArray, 490,20,120,100);
	midiDeviceDrop.visible = 1;
	kissGUI->kiss_combobox_new(&imgParam, &window, "Image Param", &textArray, 40, 140, 120, 100);
	imgParam.visible = 1;
	kissGUI->kiss_combobox_new(&midiParam, &window, "Midi Param", &textArray, 180, 140, 110, 100);
	midiParam.visible = 1;
	kissGUI->kiss_entry_new()
	noteButton.visible = 1;
	kissGUI->kiss_button_new(&addBinding, &window, "+", 40, 220);
	addBinding.visible = 1;

	kissGUI->kiss_button_new(&startButton, &window, "Start", 550, 430);
	startButton.visible = 1;

	kissGUI->kiss_array_new(&path);
	kissGUI->kiss_textbox_new(&filePath, &window, 1, &path, 40, 100, 450, 30);
	filePath.visible = 1;

	kissGUI->kiss_button_new(&browsePath, &window, "Browse", 500, 105);
	browsePath.visible = 1;

	kissGUI->kiss_button_new(&midiLearn, &window, "Listen", 390, 146);
	midiLearn.visible = 1;


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

	kissGUI->kiss_button_draw(&startButton, renderer);
	kissGUI->kiss_textbox_draw(&filePath, renderer);
	kissGUI->kiss_button_draw(&browsePath, renderer);
	kissGUI->kiss_button_draw(&midiLearn, renderer);


	SDL_RenderPresent(renderer);
}

void UserGUI::cleanUp()
{
	SDL_DestroyRenderer(renderer);
}