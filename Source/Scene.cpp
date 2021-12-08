#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


#include "UserGUI.hpp"
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "Scene.h"
#include "imgParameters.hpp"
#include "ImageBinders.h"
#include "NoteBinding.h"
#include "CCBinding.h"

using std::cout; using std::cin;
using std::endl; using std::string;

Scene::Scene(myKissGUI* kissGUI, kiss_window *mainWindow)
{
	sceneKissGUI = kissGUI;
	sceneKissGUI->kiss_window_new(&sceneWindow, mainWindow, 1, mainWindow->rect.x + 10, mainWindow->rect.y + 60, mainWindow->rect.w - 40, mainWindow->rect.h - 110);

	addImgParamIndex = 0; //this is the number of imgParam objects in our ImgParam array.
	staticX = 20;
	currentY = 70;
	imgParameters *firstIMPar = new imgParameters(staticX, currentY, addImgParamIndex, kissGUI, &sceneWindow, addImgParamIndex + 1);
	imgParArray[addImgParamIndex] = firstIMPar;
	imgParamIndex = 0;
	currentY += addY;
	addImgParamIndex = 1;

	ImageBinders* addImageBinding = new ImageBinders();
	SceneImageBindings.push_back(addImageBinding);

	displayIndex = 0;
}

void Scene::addImg()
{
	if (addImgParamIndex < 15)
	{
		 
		imgParameters* nextIMPar = new imgParameters(10, currentY, addImgParamIndex, sceneKissGUI, &sceneWindow, addImgParamIndex + 1);
		imgParArray[addImgParamIndex] = nextIMPar;
		currentY += addY;
		addImgParamIndex++;

		ImageBinders* addImageBinding = new ImageBinders();
		SceneImageBindings.push_back(addImageBinding);
	}
}

void Scene::removeImg()
{
	if (addImgParamIndex > 1) 
	{ 
		imgParArray[--addImgParamIndex] = NULL; 
		
		if (addImgParamIndex == displayIndex)
		{
			sceneScroll(1);
		}
		else currentY -= addY;

		SceneImageBindings.pop_back(); //we need to remove the previous Image from the array

	}
}

void Scene::render(SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);
	
	sceneKissGUI->kiss_window_draw(&sceneWindow, renderer);
	
	for (int i = displayIndex +2; i >= displayIndex; i--) 
	{
		if(i<addImgParamIndex)
		{
			imgParArray[i]->render(0, renderer);
		}
	}
}


//if we are successfully able to scroll, return 1. else, return 0. 
int Scene::sceneScroll(int direction)
{

	if((displayIndex-direction >= 0 && direction==1)||(addImgParamIndex + direction >= displayIndex + 1 && direction==(-1)))
	{
		for (int i = addImgParamIndex - 1; i >= 0; i--)
		{
			imgParArray[i]->imgScroll(direction);
		}
		displayIndex -= direction;
		return 1;
	}
	else 
	{
		return 0;
	}
}

void Scene::sceneEvent(SDL_Event* e, MidiModule* myMidiModule, RenderWindow myRenderWindow)
{
	for (int i = 0; i < addImgParamIndex; i++)
	{
		imgParArray[i]->selectMidiParamEvent(e);
		imgParArray[i]->selectImageParamEvent(e);
		imgParArray[i]->bindingSelectorEvent(e);
		imgParArray[i]->typeFilePath(e, &(SceneImageBindings[i]->path));
		imgParArray[i]->startLocation(e);
		imgParArray[i]->endLocation(e);
		imgParArray[i]->midiLearnEvent(e);
		imgParArray[i]->midiListenButton(e, myMidiModule);
		imgParArray[i]->browseEvent(e, myRenderWindow);
	}
}