#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "Sprite.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title);
	void enterViewMode();
	void openSceneFolder();
	void initializeScene();
	void setSceneDirectory(std::filesystem::path newDir);
	void render(int sceneIndex);
	void cleanUp();
	void toggleFullscreen();
	bool addSprite(Sprite* sprite, int sceneIndex);
	std::filesystem::path cwd;
	//std::vector<Sprite*> sprites;
	SDL_DisplayMode mode;
	SDL_Window* window;

	int num_sprites[15]; //we have upto 15 sprite indexes. 
	Sprite* arr_sprites[15][15]; //15 max scenes, 15 max sprites per scene. [Scene][Sprite]
	SDL_Renderer* renderer;

private:
	bool fullscreen;
	SDL_Texture* image;
	Sprite temp;
};
