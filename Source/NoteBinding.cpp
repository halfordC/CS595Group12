#include <stdint.h>
#include <iostream>
#include <string>

#include "NoteBinding.h"

NoteBinding::NoteBinding() 
{
	noteNumber = 0;
	noteChannel = 0; 
	noteOffOn = 0;
	param = 7;
	setOrScale = 2;
	amountOrPosition = 0.0;
}

NoteBinding::~NoteBinding() 
{
	//what goes in a destructor?
}