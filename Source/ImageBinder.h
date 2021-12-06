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
#include "Scene.h"
#include "Translator.h"
#include "Binding.hpp"

class ImageBinder 
{
public:
	ImageBinder();
	std::string imgPath;
	Binding* imgBindings[200]; //doesn't need to be this big, but this works for now. 
private:
	int bingindAddIndex;
};