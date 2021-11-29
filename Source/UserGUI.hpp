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

class UserGUI
{
public:
	UserGUI(char* p_title, MidiModule* myMidiModule);
	void render();
	void cleanUp();
	void selectMidiDropdownEvent(SDL_Event* e, MidiModule * myMidiModule);
	void selectMidiParamEvent(SDL_Event* e);
	void selectImageParamEvent(SDL_Event* e);
	void typeFilePath(SDL_Event* e);
	void midiLearnEvent(SDL_Event* e);
	void midiListenButton(SDL_Event* e, MidiModule* myMidiModule);
	void browseEvent(SDL_Event* e, RenderWindow myRenderWindow);
	void addBindingEvent(SDL_Event* e);

	std::filesystem::path selectedDirectory;
	myKissGUI* kissGUI;
	kiss_window window;

	std::vector<kiss_window> bindings; //Hoping I can create a new window for each binding.  Possibly could use a vector or some type of dynamic array

	kiss_array objects;
	kiss_button addScene;
	kiss_entry noteEntry;
	kiss_button addBinding;
	kiss_combobox midiDeviceDrop;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	char message[KISS_MAX_LENGTH];
	kiss_label label;
	kiss_array connectedMidiDevices; //This will need to be changed as devices are connected and disconnected.
	kiss_array midiParamList;
	kiss_array imageParamList;

	kiss_button startButton;
	kiss_array path;
	kiss_textbox filePath;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_entry filePathEntry;
private:
	SDL_Renderer* renderer;
	SDL_Event e;
	int listenFilter;


	

};