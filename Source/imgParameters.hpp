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
#include "Translator.h"

#define windowWidth 480
#define windowHeight 90

class imgParameters
{
public:
	imgParameters(int x, int y, int id, myKissGUI* kissGUI, kiss_window *inWindow, int layerNum, Translator* t);

	void render(int newY, SDL_Renderer* renderer);//Alternatively could modify coordinates for scrolling in their own method
	void cleanUp();
	void selectMidiParamEvent(SDL_Event* e);
	void selectImageParamEvent(SDL_Event* e);
	void typeFilePath(SDL_Event* e);
	void midiLearnEvent(SDL_Event* e);
	void midiListenButton(SDL_Event* e, MidiModule* myMidiModule);
	void browseEvent(SDL_Event* e, RenderWindow myRenderWindow);
	void imgScroll(SDL_Event* e, int direction);

	kiss_window binding;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	kiss_entry noteEntry;
	kiss_entry filePathEntry;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_label IDNum;
	kiss_label warningLabel;
	kiss_window warningWindow;
	kiss_button warningButton;

	kiss_array midiParamList;
	kiss_array imageParamList;

private:
	SDL_Event* e;
	myKissGUI* imgKissGUI;
	Translator* translator;
	int listenFilter;
};