#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"

class imgParameters
{
public:
	imgParameters(myKissGUI* kissGUI);

	void render(SDL_Renderer* renderer);
	void cleanUp();
	void selectMidiParamEvent(SDL_Event* e);
	void selectImageParamEvent(SDL_Event* e);
	void typeFilePath(SDL_Event* e);
	void midiLearnEvent(SDL_Event* e);
	void midiListenButton(SDL_Event* e, MidiModule* myMidiModule);
	void browseEvent(SDL_Event* e, RenderWindow myRenderWindow);

	kiss_window binding;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	kiss_entry noteEntry;
	kiss_entry filePathEntry;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_array midiParamList;
	kiss_array imageParamList;

private:
	SDL_Event* e;
	myKissGUI* imgKissGUI;
};