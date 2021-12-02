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
	addImgParamIndex = 0; //this is the number of imgParam objects in our ImgParam array.
	imgParameters *firstIMPar = new imgParameters(kissGUI);
	imgParArray[addImgParamIndex] = firstIMPar;
	imgParamIndex = 0;

	sceneKissGUI = kissGUI;
	sceneKissGUI->kiss_window_new(&sceneWindow, mainWindow, 1, 30, 60, 500, 300);
}

void Scene::addImg()
{
	if (addImgParamIndex < 15)
	{
		addImgParamIndex++; 
		imgParameters* nextIMPar = new imgParameters(sceneKissGUI);
		imgParArray[addImgParamIndex] = nextIMPar;
	}
}

void Scene::render(SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);
	
	sceneKissGUI->kiss_window_draw(&sceneWindow, renderer);
	
	for (int i = 0; i < addImgParamIndex; i++) 
	{
		imgParArray[i]->render();
	}
}