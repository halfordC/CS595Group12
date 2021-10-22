#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown);
	void enterViewMode();
	void openSceneFolder();
	void render();
	void cleanUp();
	SDL_DisplayMode mode;
	SDL_Window* window;
	std::filesystem::path cwd;
private:
	SDL_Renderer* renderer;
	SDL_Texture* image;
};
