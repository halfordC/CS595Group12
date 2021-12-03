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
	imgParameters *firstIMPar = new imgParameters(staticX, currentY, kissGUI, &sceneWindow);
	imgParArray[addImgParamIndex] = firstIMPar;
	imgParamIndex = 0;
	currentY += 90;
	addImgParamIndex = 1;


}

void Scene::addImg()
{
	if (addImgParamIndex < 15)
	{
		 
		imgParameters* nextIMPar = new imgParameters(40, currentY, sceneKissGUI, &sceneWindow);
		imgParArray[addImgParamIndex] = nextIMPar;
		currentY += 90;
		addImgParamIndex++;
	}
}

void Scene::render(SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);
	
	sceneKissGUI->kiss_window_draw(&sceneWindow, renderer);
	
	for (int i = addImgParamIndex - 1; i >= 0; i--) 
	{
		imgParArray[i]->render(0, 0, renderer);
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