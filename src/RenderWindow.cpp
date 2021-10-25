#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;

RenderWindow::RenderWindow(const char* p_title):mode(), window(NULL), renderer(NULL), image(NULL)
{
	/* Get current display mode to initialize a window with native screen resolution. */
	if(SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		cout << "Failed to get current display mode. Error: " << SDL_GetError() << endl;
	}
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_HIDDEN); //title, xpos, ypos, width, height, and show the window.
	if(window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.
	if(renderer == NULL)
	{
		cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
	}

	/* Initializes the working directory of the program to the scenes folder, creating one if necessary. */
	cwd = fs::current_path();
	#ifdef __APPLE__
		cwd += "/scenes";
	#elif _WIN32
		cwd += "\\scenes";
	#endif
	if(!fs::exists(cwd)) fs::create_directory(cwd);

	/* Below code is to set a Sprite to be rendered by the render method! */
  image = IMG_LoadTexture(renderer, "mugshot.PNG");
	int w, h;
	SDL_QueryTexture(image, NULL, NULL, &w, &h);
	for(int i = 0; i < 10; i++)
	{
		Sprite temp(i * 0.1, i * 0.1, w, h, image);
		temp.setScale((i + 1) * 0.1);
		temp.setRotation( (i * 36) );
		sprites.push_back(temp);
	}
}

/* This method will show the RenderWindow in the native resolution of the system. It will be fullscreen
   and borderless. This method should be triggered by the "START" button on the GUI. */
void RenderWindow::enterViewMode()
{
	SDL_SetWindowSize(window, mode.w, mode.h);
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

/* This method will open the scenes folder in file explorer(windows) or finder(macOSx).
 	 This will allow users to quickly add source images to the project from the gui and
	 use them in rendering. */
void RenderWindow::openSceneFolder()
{
	#ifdef __APPLE__
		string command = "open " + cwd.string();
	#elif _WIN32
		string command = "explorer " + cwd.string();
	#endif
	system(command.c_str());
}

/* This method will render the sprites that are held in the sprite vector to the screen.
 	 Sprites are going to be rendered with the center of their rect at the x and y percentages that are
	 stored. This method should be called by main in the main program loop. */
void RenderWindow::render()
{
	SDL_RenderClear(renderer);
	for(Sprite s : sprites)
	{
		SDL_Rect texr;
		texr.x = (mode.w * s.getX()) - ((s.getWidth() * s.getScale()) / 2);
		texr.y = (mode.h * s.getY()) - ((s.getHeight() * s.getScale()) / 2);
		texr.w = s.getWidth() * s.getScale();
		texr.h = s.getHeight() * s.getScale();

		SDL_RenderCopyEx(renderer, s.getRes(), NULL, &texr, s.getRotation(), NULL, SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
