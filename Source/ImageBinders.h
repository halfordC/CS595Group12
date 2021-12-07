#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "CCBinding.h"
#include "NoteBinding.h"


class ImageBinders
{
public:
	ImageBinders();
	~ImageBinders();

	std::string path;
	std::vector<CCBinding*> ImageCCBindings;
	std::vector<NoteBinding*> ImageNoteBindings;

private:

};