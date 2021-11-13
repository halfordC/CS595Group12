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
	kiss_button addScene;
	kiss_button noteButton;
	kiss_button addBinding;
	kiss_combobox midiDeviceDrop;
	kiss_combobox imgParam;
	kiss_combobox midiParam;

	kiss_button startButton;
	kiss_array path;
	kiss_textbox filePath;
	kiss_button browsePath;
	kiss_button midiLearn;

	char message[KISS_MAX_LENGTH];
	kiss_label label;

};