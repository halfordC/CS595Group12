#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

class UserGUI
{
public:
	UserGUI(const char* p_title);
	void enterViewMode();
	int initializeScene();
	void render();
	void cleanUp();
	std::filesystem::path selectedDirectory;
	SDL_DisplayMode mode;
	SDL_Window* window;
private:
	SDL_Renderer* renderer;
	SDL_Event e;
};