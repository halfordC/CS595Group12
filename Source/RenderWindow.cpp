#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "RenderWindow.hpp"
#include "Sprite.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

namespace fs = std::filesystem;

RenderWindow::RenderWindow(const char* p_title) :mode(), window(NULL), renderer(NULL), image(NULL)
{

	/* Get current display mode to initialize a window with native screen resolution. */
	if (SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		cout << "Failed to get current display mode. Error: " << SDL_GetError() << endl;
	}
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN_DESKTOP); //title, xpos, ypos, width, height, and show the window.
	if (window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.
	if (renderer == NULL)
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
	cout << cwd.string() << endl;
	if (!fs::exists(cwd)) fs::create_directory(cwd);
	//fullscreen = true;
	fullscreen = false;
	initializeScene();

	for (int i = 0; i < 15; i++) 
	{
		num_sprites[i] = 0;
	}
	
}

/* This method will show the RenderWindow in the native resolution of the system. It will be fullscreen
   and borderless. This method should be triggered by the "START" button on the GUI. */
void RenderWindow::enterViewMode() { SDL_ShowWindow(window);	}
void RenderWindow::toggleFullscreen()
{
	if (fullscreen)
	{
		SDL_SetWindowSize(window, 640, 480);
		SDL_SetWindowPosition(window, 50, 50);
		SDL_SetWindowFullscreen(window, 0);
		fullscreen = false;
	}
	else
	{
		SDL_SetWindowSize(window, mode.w, mode.h);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		fullscreen = true;
	}
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
	cout << command << endl;
#endif
	system(command.c_str());
}

/* This method clears and sets up a new sprites vector for rendering. This Method
	 should be called any time a change is made to the current scene directory
	 and any time the directory changes. */
void RenderWindow::initializeScene()
{
	
		//for (Sprite* s : sprites) { s->~Sprite(); };
		//sprites.clear();

		//int i = 0;
		//int w, h;
		//for (auto& dir_entry : fs::directory_iterator(cwd))
		//{
		//	if (!fs::is_directory(dir_entry))
		//	{
				/* Pull file extension and set to upper case for string comparison. */
		//		string ext = dir_entry.path().extension().string();
		//		std::for_each(ext.begin(), ext.end(), [](char& c) {
		//			c = ::toupper(c);
		//			});

				/* Only allow JPEG or PNG at this time as I am a lazy POS */
		//		if (ext.compare(".JPEG") == 0 || ext.compare(".PNG") == 0)
		//		{

					/* .string().c_str() necessary for macOSx and Windows cross compatablility. */
		//			image = IMG_LoadTexture(renderer, (dir_entry.path()).string().c_str());
		//			SDL_QueryTexture(image, NULL, NULL, &w, &h);
		//			Sprite* temp = new Sprite(i * 0.1f, i * 0.1f, w, h, image);

					/* calls to setScale() and setRotation() are for demonstrative purposes. */
		//			temp->setScale((i + 1) * 0.2);
		//			temp->setRotation((i * 36));
		//			sprites.push_back(temp);
		//			i++;
		//		}
		//		cout << "Sprite " << i << "| w->" << w << " h->" << h << endl;
		//	}
		//}
	
}

/* This method sets the current working directory to newDir. After setting to a new
	 directory, the scene will be reinitialized wity the initializeScene() method. */
void RenderWindow::setSceneDirectory(fs::path path)
{
	std::error_code ec;
	cout << path << endl;
	if (!fs::exists(path)) fs::create_directory(path);
	if (fs::is_directory(path, ec))
	{
		cwd = path;
		initializeScene();
	}
}

bool RenderWindow::addSprite(Sprite* sprite, int sceneIndex)
{
	if (num_sprites[sceneIndex] < 15)
	{
		arr_sprites[sceneIndex][num_sprites[sceneIndex]] = sprite;
		num_sprites[sceneIndex]++;
		return true;
	}
	return false;
}

/* This method will render the sprites that are held in the sprite vector to the screen.
	 Sprites are going to be rendered with the center of their rect at the x and y percentages that are
	 stored. This method should be called by main in the main program loop. */
void RenderWindow::render(int sceneIndex)
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < num_sprites[sceneIndex]; i++)
	{
		SDL_Rect texr;
		texr.x = (mode.w * arr_sprites[sceneIndex][i]->getX()) - ((arr_sprites[sceneIndex][i]->getWidth() * arr_sprites[sceneIndex][i]->getScale()) / 2);
		texr.y = (mode.h * arr_sprites[sceneIndex][i]->getY()) - ((arr_sprites[sceneIndex][i]->getHeight() * arr_sprites[sceneIndex][i]->getScale()) / 2);
		texr.w = arr_sprites[sceneIndex][i]->getWidth() * arr_sprites[sceneIndex][i]->getScale();
		texr.h = arr_sprites[sceneIndex][i]->getHeight() * arr_sprites[sceneIndex][i]->getScale();

		SDL_RenderCopyEx(renderer, arr_sprites[sceneIndex][i]->getRes(), NULL, &texr, arr_sprites[sceneIndex][i]->getRotation(), NULL, SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	// CLEAN UP THE SPRITE ARRAY TODO
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

