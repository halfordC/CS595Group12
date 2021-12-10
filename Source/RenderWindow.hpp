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
	void render();
	void cleanUp();
	void toggleFullscreen();
	bool addSprite(Sprite* sprite);
	std::filesystem::path cwd;
	//std::vector<Sprite*> sprites;
	SDL_DisplayMode mode;
	SDL_Window* window;

	// Trying to connect shit
	Sprite* arr_sprites[15];
	SDL_Renderer* renderer;

private:
	int num_sprites;
	bool fullscreen;
	SDL_Texture* image;
	Sprite temp;
};
