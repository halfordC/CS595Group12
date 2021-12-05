#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>


#include "UserGUI.hpp"
//#include "kiss_sdl.h"
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "Scene.h"
#include "imgParameters.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

Scene::Scene(myKissGUI* kissGUI, kiss_window *mainWindow)
{
	sceneKissGUI = kissGUI;
	sceneKissGUI->kiss_window_new(&sceneWindow, mainWindow, 1, 30, 60, 500, 300);

	addImgParamIndex = 0; //this is the number of imgParam objects in our ImgParam array.
	staticX = 40;
	currentY = 70;
	imgParameters *firstIMPar = new imgParameters(staticX, currentY, addImgParamIndex + 1, kissGUI, &sceneWindow, addImgParamIndex + 1);
	imgParArray[addImgParamIndex] = firstIMPar;
	imgParamIndex = 0;
	currentY += 90;
	addImgParamIndex = 1;

	displayIndex = 0;
}

void Scene::addImg()
{
	if (addImgParamIndex < 15)
	{
		 
		imgParameters* nextIMPar = new imgParameters(40, currentY, addImgParamIndex + 1, sceneKissGUI, &sceneWindow, addImgParamIndex + 1);
		imgParArray[addImgParamIndex] = nextIMPar;
		currentY += 90;
		addImgParamIndex++;
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
		else currentY -= 90;
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
		imgParArray[i]->typeFilePath(e);
		imgParArray[i]->midiLearnEvent(e);
		imgParArray[i]->midiListenButton(e, myMidiModule);
		imgParArray[i]->browseEvent(e, myRenderWindow);
	}
}