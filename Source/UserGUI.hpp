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
private:
	SDL_Renderer* renderer;
	SDL_Event e;
	kiss_window window;
	kiss_array objects;
	kiss_button button;
	kiss_combobox midiDeviceDrop;
	char message[KISS_MAX_LENGTH];
	kiss_label label;

};