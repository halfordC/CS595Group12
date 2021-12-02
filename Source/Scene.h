#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "imgParameters.hpp"


class Scene 
{
public:
	Scene();
	imgParameters * imgParArray[15]; // setting a hard limit of 15 images for now. Might change later.

	void addImg(myKissGUI* kissGUI, SDL_Event *e);
	void render(int * draw, SDL_Renderer* renderer, myKissGUI* kissGUI);

	kiss_button addImgButton;
	kiss_window sceneWindow;
	//we need a function to add 
private:
	int imgParamIndex; //should not go over 15. 
};
