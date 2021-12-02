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
	Scene::Scene(myKissGUI* kissGUI, kiss_window* mainWindow);
	void addImg(); //not an event, called by the event in Main Window. 
	void render(SDL_Renderer* renderer);

	imgParameters* imgParArray[15]; // setting a hard limit of 15 images for now. Might change later.
	kiss_button addImgButton;
	kiss_window sceneWindow;
private:
	int imgParamIndex; //should not go over 15. 
	int addImgParamIndex;
	myKissGUI* sceneKissGUI;
};
