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
#include "imgParameters.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

imgParameters::imgParameters(myKissGUI* kissGUI)
{
	kissGUI->fillMidiParam(&midiParamList);
	kissGUI->fillImageParam(&imageParamList);
	kissGUI->kiss_window_new(&binding, NULL, 1, 0, 0, 480, 90);
	kissGUI->kiss_combobox_new(&imgParam, &binding, "Image Param", &imageParamList, binding.rect.x + 100, binding.rect.y + 50, 120, 100);
	kissGUI->kiss_combobox_new(&midiParam, &binding, "Midi Param", &midiParamList, binding.rect.x + 140, binding.rect.y + 50, 110, 100);
	kissGUI->kiss_entry_new(&noteEntry, &binding, 1, "Note/CC", binding.rect.x + 270, binding.rect.y + 50, 100);
	kissGUI->kiss_entry_new(&filePathEntry, &binding, 1, "FilePath", binding.rect.x + 5, binding.rect.y + 10, 400);
	kissGUI->kiss_button_new(&browsePath, &binding, "Browse", binding.rect.x + 410, binding.rect.y + 15);
	kissGUI->kiss_button_new(&midiLearn, &binding, "Listen", binding.rect.x + 380, binding.rect.y + 55);
}

