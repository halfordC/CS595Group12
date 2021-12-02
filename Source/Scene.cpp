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

Scene::Scene() 
{
	imgParamIndex = 0; //this is the number of imgParam objects in our ImgParam array.
	imgParameters *firstIMPar = new imgParameters();
	imgParArray[imgParamIndex] = firstIMPar;
	imgParamIndex++;


}
void Scene::addImg(myKissGUI *kissGUI, SDL_Event* e)
{
	int draw = 1;
	if (kissGUI->kiss_button_event(&addImgButton, e, &draw))
	{
		imgParameters* nextIMPar = new imgParameters();
		imgParArray[imgParamIndex] = nextIMPar;
		imgParamIndex++;
	}
}

void Scene::render(int *draw, SDL_Renderer* renderer, myKissGUI *kissGUI)
{
	SDL_RenderClear(renderer);
	kissGUI->kiss_window_draw(&sceneWindow, renderer);



	//also, call the render function on all img that we have in scene view. 

}