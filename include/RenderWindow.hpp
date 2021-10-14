#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>

using std::string;
namespace fs = std::filesystem;

class RenderWindow
{
public:
	RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown);
	void cleanUp();
	void enterViewMode();
	SDL_DisplayMode mode;
	fs::path cwd;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
