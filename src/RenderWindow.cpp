#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>

#include "RenderWindow.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;

/*
#include <stdint.h>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

typedef struct
{
	fs::path resourcePath;
	float x, y, size, alpha;
	int rotation;
} sprite;
*/

RenderWindow::RenderWindow(const char* p_title, bool isFullScreen, int p_w, int p_h, uint32_t windowShown)
	:mode(), cwd(), window(NULL), renderer(NULL), image(NULL)
{
	/* Get current display mode to initialize a window with native screen resolution. */
	if(SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		cout << "Failed to get current display mode. Error: " << SDL_GetError() << endl;
	}

	if(isFullScreen)
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, windowShown); //title, xpos, ypos, width, height, and show the window.
		enterViewMode();
	}
	else
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_w, p_h, windowShown); //title, xpos, ypos, width, height, and show the window.
	}

	if(window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.

	if(renderer == NULL)
	{
		cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
	}

	/* sets cwd to the root directory of the program. */
	cwd = fs::current_path();
	image = IMG_LoadTexture(renderer, "mugshot.PNG");
}
void RenderWindow::enterViewMode()
{
	SDL_SetWindowSize(window, mode.w, mode.h);
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}
/* Method will open the scenes folder in file explorer(windows) or finder(macOSx) */
void RenderWindow::openSceneFolder()
{
	#ifdef __APPLE__
		cwd += "/scenes";
		string command = "open " + cwd.string();
	#elif _WIN32
		cwd += "\\scenes";
		string command = "explorer " + cwd.string();
	#endif
	if(!fs::exists(cwd))
	{
			fs::create_directory(cwd);
	}
	system(command.c_str());
}
void RenderWindow::render()
{
	int w, h;
	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	SDL_Rect texr;
	texr.x = (mode.w / 2) - (w / 2); texr.y = (mode.h / 2) - (h / 2); texr.w = w; texr.h = h;

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, image, NULL, &texr);
	SDL_RenderPresent(renderer);
}
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
