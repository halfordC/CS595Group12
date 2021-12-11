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
#include "ImageBinders.h"


class imgParameters
{
public:
	imgParameters(int x, int y, int p_index, myKissGUI* kissGUI, kiss_window* inWindow, int layerNum, int inSceneIndex);

	void render(int newY, SDL_Renderer* renderer);//Alternatively could modify coordinates for scrolling in their own method
	void cleanUp();
	void selectMidiParamEvent(SDL_Event* e);
	void selectImageParamEvent(SDL_Event* e);
	void bindingSelectorEvent(SDL_Event* e);
	void startLocation(SDL_Event* e);
	void endLocation(SDL_Event* e);
	void typeFilePath(SDL_Event* e, RenderWindow * inRenderWindow, SDL_Renderer* renderer);
	void midiLearnEvent(SDL_Event* e);
	void midiListenButton(SDL_Event* e, MidiModule* myMidiModule, RenderWindow* inRenderWindow);
	void browseEvent(SDL_Event* e, RenderWindow myRenderWindow);
	void imgScroll(int direction);

	void updateWarning(char* newText);

	int getIndex() { return index; };
	void warningEvent(SDL_Event* e);

	kiss_window binding;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	kiss_entry noteEntry;
	kiss_entry filePathEntry;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_label IDNum;
	kiss_button remove;
	kiss_entry start;
	kiss_entry end;
	kiss_combobox selector;

	kiss_array midiParamList;
	kiss_array imageParamList;
	kiss_array bindingList;
	int previousImageFlag = 0;//0 is no previous image, 1 is previous image

	Sprite* sprite;
	//ImageBinders* bindings;
	int noteBindingIndex;
	int ccBindingIndex;
	int paramSelected;
	int setOrScaleSelected; //if 1, set. if 2, scale.
	float startValue;
	float endValue;
	kiss_label warningLabel;
	kiss_window warningWindow;
	kiss_button warningButton;

private:
	SDL_Event* e;
	myKissGUI* imgKissGUI;
	int listenFilter;
	int index;
	bool warning;
	bool imageParamSelected;
	bool midiParamSelected;
	bool endParamSelected;
	int sceneIndex; //this is the scene that this layer is attached to.
};