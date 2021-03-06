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
#include "ImageBinders.h"

#define addY 135


class Scene 
{
public:
	Scene::Scene(myKissGUI* kissGUI, kiss_window* mainWindow, int inSceneIndex);
	void addImg(); //not an event, called by the event in Main Window. 
	void removeImg();
	void render(SDL_Renderer* renderer);
	void sceneEvent(SDL_Event* e, MidiModule* myMidiModule, RenderWindow *myRenderWindow, SDL_Renderer* renderer);
	int sceneScroll(int direction);

	imgParameters* imgParArray[15]; // setting a hard limit of 15 images for now. Might change later.
	kiss_button addImgButton;
	kiss_window sceneWindow;
	int currentY;
	//std::vector<ImageBinders*> SceneImageBindings;

	// Using for connecting - Noah
	//std::vector<ImageBinders*> arr_SceneImageBindings[15];
private:
	int sceneIndex; //the Index of this scene, should not go over 15. does not change after instatiation
	int imgParamIndex; //should not go over 15. 
	int addImgParamIndex;
	myKissGUI* sceneKissGUI;
	
	int staticX;
	const int startY = 70;
	int displayIndex; //the first image item to be rendered in the scene window
};
