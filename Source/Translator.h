#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiModule.h"
#include "Binding.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"

#pragma once

class Translator
{
public:
	Translator();
	void updateBindings();
	void pushBinding(Binding* b);
	Binding** getBindings();
	void translate(RenderWindow* a, MidiModule* myMidiModule);
	void setX(Binding* b, RenderWindow* a, int i);
	void scaleX(Binding* b, RenderWindow* a, int i);
	void setY(Binding* b, RenderWindow* a, int i);
	void scaleY(Binding* b, RenderWindow* a, int i);
	void setWidth(Binding* b, RenderWindow* a, int i);
	void scaleWidth(Binding* b, RenderWindow* a, int i);
	void setHeight(Binding* b, RenderWindow* a, int i);
	void scaleHeight(Binding* b, RenderWindow* a, int i);
	void setSize(Binding* b, RenderWindow* a, int i);
	void scaleSize(Binding* b, RenderWindow* a, int i);
	void setRotation(Binding* b, RenderWindow* a, int i);
	void scaleRotation(Binding* b, RenderWindow* a, int i);
private:
	MidiModule* midimod;
	Binding* bindings[200];
	int bindingsAddIndex;
};