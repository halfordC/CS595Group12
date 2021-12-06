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
#include "ImageBinder.h"

ImageBinder::ImageBinder()
{
	bingindAddIndex = 0;
	//malloc() //will we need this?
}

