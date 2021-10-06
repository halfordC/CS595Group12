#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown);
	void cleanUp();
	void setFullScreen();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_DisplayMode mode;



};
