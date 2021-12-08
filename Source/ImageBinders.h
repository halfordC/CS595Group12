#pragma once
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "CCBinding.h"
#include "NoteBinding.h"

//This class hold the path to an image, and all the bindings associated with that image
class ImageBinders
{
public:
	ImageBinders();
	//~ImageBinders();

	std::string path;
	std::vector<CCBinding*> ImageCCBindings;
	std::vector<NoteBinding*> ImageNoteBindings;

private:

};