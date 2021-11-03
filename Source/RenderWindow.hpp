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
  std::filesystem::path cwd;
	std::vector<Sprite*> sprites;
	SDL_DisplayMode mode;
	SDL_Window* window;
private:
	SDL_Renderer* renderer;
	SDL_Texture* image;
	Sprite temp;
};
