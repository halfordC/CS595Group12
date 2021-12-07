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
	imgParameters(int x, int y, int id, myKissGUI* kissGUI, kiss_window *inWindow, int layerNum);

	void render(int newY, SDL_Renderer* renderer);//Alternatively could modify coordinates for scrolling in their own method
	void cleanUp();
	void selectMidiParamEvent(SDL_Event* e);
	void selectImageParamEvent(SDL_Event* e);
	void typeFilePath(SDL_Event* e);
	void midiLearnEvent(SDL_Event* e);
	void midiListenButton(SDL_Event* e, MidiModule* myMidiModule);
	void browseEvent(SDL_Event* e, RenderWindow myRenderWindow);
	void imgScroll(int direction);

	kiss_window binding;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	kiss_entry noteEntry;
	kiss_entry filePathEntry;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_label IDNum;
	kiss_button removeBinding;
	kiss_entry startX;
	kiss_entry startY;
	kiss_combobox selector;

	kiss_array midiParamList;
	kiss_array imageParamList;

private:
	SDL_Event* e;
	myKissGUI* imgKissGUI;
	int listenFilter;
};