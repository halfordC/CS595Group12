#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "myKissGui.hpp"

class UserGUI
{
public:
	UserGUI(char* p_title);
	void render();
	void cleanUp();
	std::filesystem::path selectedDirectory;
	myKissGUI* kissGUI;
	void selectMidiDropdownEvent(SDL_Event* e);
	kiss_window window;
	kiss_array objects;
	kiss_button addScene;
	kiss_button noteButton;
	kiss_button addBinding;
	kiss_combobox midiDeviceDrop;
	kiss_combobox imgParam;
	kiss_combobox midiParam;
	char message[KISS_MAX_LENGTH];
	kiss_label label;
	kiss_array connectedMidiDevices; //This will need to be changed as devices are connected and disconnected.
	kiss_array midiParamList;
	kiss_array imageParamList;
private:
	SDL_Renderer* renderer;
	SDL_Event e;
	

};