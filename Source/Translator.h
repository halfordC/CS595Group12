#pragma once
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiModule.h"
#include "Binding.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "ImageBinders.h"
#include "NoteBinding.h"
#include "CCBinding.h"
#include "UserGUI.hpp"
#include "Scene.h"

class Translator
{
public:
	Translator(UserGUI *InGUI);
	void updateBindings();
	void pushBinding(Binding* b);
	Binding** getBindings();
	void translate(RenderWindow* a, MidiModule* myMidiModule);
	void NoteSetX(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleX(NoteBinding b, RenderWindow* a, int i);
	void NoteSetY(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleY(NoteBinding b, RenderWindow* a, int i);
	void NoteSetWidth(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleWidth(NoteBinding b, RenderWindow* a, int i);
	void NoteSetHeight(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleHeight(NoteBinding b, RenderWindow* a, int i);
	void NoteSetSize(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleSize(NoteBinding b, RenderWindow* a, int i);
	void NoteSetRotation(NoteBinding b, RenderWindow* a, int i);
	void NoteScaleRotation(NoteBinding b, RenderWindow* a, int i);
	std::vector<Scene*> translatorScenes;
	//each scene contains a vector of image binders, which holds all note and CC bindings for that image.
	//This way we can iterate through each binding for each image. 
	//use index userGUI->sceneIndex to access current scene

private:
	UserGUI* translatorGUI;



	
};