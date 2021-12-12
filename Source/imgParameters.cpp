#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>


#include "UserGUI.hpp"
//#include "kiss_sdl.h"
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "imgParameters.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;

imgParameters::imgParameters(int x, int y, int p_index, myKissGUI* kissGUI, kiss_window *inWindow, int layerNum, int inSceneIndex)
{
	kissGUI->kiss_array_new(&bindingList);
	kissGUI->kiss_array_appendstring(&bindingList, 0, "New Binding", NULL);
	char* warningText = "No Midi Device Selected";
	warning = false;
	imageParamSelected = false;
	midiParamSelected = false;

	std::string tmp = "" + std::to_string(layerNum);
	char* layerNumber = const_cast<char*>(tmp.c_str());
	imgKissGUI = kissGUI;
	kissGUI->fillMidiParam(&midiParamList);
	kissGUI->fillImageParam(&imageParamList);
	kissGUI->kiss_window_new(&binding, inWindow, 1, inWindow->rect.x + 10, y, inWindow->rect.w - 20, 130);
	kissGUI->kiss_combobox_new(&imgParam, &binding, "Image Param", &imageParamList, binding.rect.x + 80, binding.rect.y + 50, 120, 100);
	kissGUI->kiss_combobox_new(&midiParam, &binding, "Midi Param", &midiParamList, binding.rect.x + 220, binding.rect.y + 50, 110, 100);
	kissGUI->kiss_combobox_new(&selector, &binding, "Binding Selector", &bindingList, binding.rect.x + 310, binding.rect.y + 90, 200, 100);
	kissGUI->kiss_entry_new(&noteEntry, &binding, 1, "Note/CC", binding.rect.x + 350, binding.rect.y + 50, 100);
	kissGUI->kiss_entry_new(&filePathEntry, &binding, 1, "FilePath", binding.rect.x + 35, binding.rect.y + 10, 465);
	kissGUI->kiss_entry_new(&start, &binding, 1, "Start (0-1)", binding.rect.x + 10, binding.rect.y + 90, 130);
	kissGUI->kiss_entry_new(&end, &binding, 1, "End (0-1)", binding.rect.x + 150, binding.rect.y + 90, 130);
	kissGUI->kiss_button_new(&remove, &binding, "Remove", binding.rect.x + 10, binding.rect.y + 54);
	kissGUI->kiss_button_new(&browsePath, &binding, "Browse", binding.rect.x + 505, binding.rect.y + 14);
	kissGUI->kiss_button_new(&midiLearn, &binding, "Listen", binding.rect.x + 460, binding.rect.y + 54);
	kissGUI->kiss_label_new(&IDNum, &binding, layerNumber, binding.rect.x + 15, binding.rect.y + 15);
	kissGUI->kiss_window_new(&warningWindow, &binding, 1, x, y, inWindow->rect.w - 20, 130);
	kissGUI->kiss_label_new(&warningLabel, &warningWindow, warningText, warningWindow.rect.x + 10, warningWindow.rect.y + 10);
	kissGUI->kiss_button_new(&warningButton, &warningWindow, "OK", (warningWindow.rect.w) / 2, warningWindow.rect.y + 60);

	

	binding.visible = 1;
	index = p_index;
	//bindings = binder;
	bindingIndex = 0;
	setOrScaleSelected = 1;
	imageLoaded = false;
	sceneIndex = inSceneIndex;
}

void imgParameters::render(int newY, SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);
	if (warning)
	{
		imgKissGUI->kiss_window_draw(&warningWindow, renderer);
		imgKissGUI->kiss_button_draw(&warningButton, renderer);
		imgKissGUI->kiss_label_draw(&warningLabel, renderer);
	}else
	{
		imgKissGUI->kiss_window_draw(&binding, renderer);
		imgKissGUI->kiss_button_draw(&remove, renderer);
		imgKissGUI->kiss_button_draw(&browsePath, renderer);
		imgKissGUI->kiss_button_draw(&midiLearn, renderer);
		imgKissGUI->kiss_entry_draw(&start, renderer);
		imgKissGUI->kiss_entry_draw(&end, renderer);
		imgKissGUI->kiss_combobox_draw(&selector, renderer);
		imgKissGUI->kiss_combobox_draw(&imgParam, renderer);
		imgKissGUI->kiss_combobox_draw(&midiParam, renderer);
	
		imgKissGUI->kiss_entry_draw(&noteEntry, renderer);
		imgKissGUI->kiss_entry_draw(&filePathEntry, renderer);
	
		imgKissGUI->kiss_label_draw(&IDNum, renderer);
	}
	//SDL_RenderPresent(renderer);
}

void imgParameters::imgScroll(int direction)//shift should be the same distance both ways so direction will just be a negative for up and a positive for down
{
	binding.rect.y += (direction * addY);
	browsePath.rect.y += (direction * addY);
	browsePath.texty += (direction * addY);
	midiLearn.rect.y += (direction * addY);
	midiLearn.texty += (direction * addY);

	imgParam.textbox.rect.y += (direction * addY);
	imgParam.vscrollbar.downrect.y += (direction * addY);
	imgParam.vscrollbar.sliderrect.y += (direction * addY);
	imgParam.vscrollbar.uprect.y += (direction * addY);
	imgParam.entry.rect.y += (direction * addY);
	imgParam.entry.texty += (direction * addY);

	midiParam.textbox.rect.y += (direction * addY);
	midiParam.vscrollbar.downrect.y += (direction * addY);
	midiParam.vscrollbar.sliderrect.y += (direction * addY);
	midiParam.vscrollbar.uprect.y += (direction * addY);
	midiParam.entry.rect.y += (direction * addY);
	midiParam.entry.texty += (direction * addY);

	noteEntry.rect.y += (direction * addY);
	noteEntry.texty += (direction * addY);
	filePathEntry.rect.y += (direction * addY);
	filePathEntry.texty += (direction * addY);
	IDNum.rect.y += (direction * addY);

	start.rect.y += (direction * addY);
	start.texty += (direction * addY);
	end.rect.y += (direction * addY);
	end.texty += (direction * addY);

	remove.rect.y += (direction * addY);
	remove.texty += (direction * addY);

	selector.textbox.rect.y += (direction * addY);
	selector.vscrollbar.downrect.y += (direction * addY);
	selector.vscrollbar.sliderrect.y += (direction * addY);
	selector.vscrollbar.uprect.y += (direction * addY);
	selector.entry.rect.y += (direction * addY);
	selector.entry.texty += (direction * addY);
}

void imgParameters::cleanUp()
{
}

void imgParameters::selectMidiParamEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_combobox_event(&midiParam, e, &draw))
	{
		//An item has been clicked! but which one?
		//normally, we would use bsearch, but we can't really do that in c++ with how this is setup.
		//so we must mannualy search through and find the entry.
		int length = midiParam.textbox.array->length;
		for (int i = 0; i < length; i++)
		{
			void** p = midiParam.textbox.array->data + i; //data is of type void pointer pointer
			void* s = *p; //derefference p, and get S. 
			char* contents = (char*)s; //contents is the char* string stored at data location i.;

			//now we need to compare this string with the string that was clicked. where does that string come from?
			bool result = imgKissGUI->dropBoxcompare(midiParam.entry, contents);
			if (result)
			{
				//We are at the text box entry index of what we clicked on, do the clicked action.
				//so it is important we know what is here.

				listenFilter = i;
			}
		}
		midiParamSelected = true;
	}
}

void imgParameters::selectImageParamEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_combobox_event(&imgParam, e, &draw))
	{
		
		//do stuff like the previous box up there

		char* contents = imgParam.entry.text;

		string checkString(contents);
		int space = checkString.find_last_of(" ");
		if (space==3) 
		{
			setOrScaleSelected = 0;
		}
		
		if (!strcmp(contents, "Scale X")|| !strcmp(contents, "Set X")) paramSelected = 0;
		else if (!strcmp(contents, "Scale Y") || !strcmp(contents, "Set Y")) paramSelected = 1;
		else if (!strcmp(contents, "Scale Width") || !strcmp(contents, "Set Width")) paramSelected = 2;
		else if (!strcmp(contents, "Scale Height") || !strcmp(contents, " Set Height")) paramSelected = 3;
		else if (!strcmp(contents, "Scale Rotation") || !strcmp(contents, "Set Rotation")) paramSelected = 4;
		else if (!strcmp(contents, "Scale Size") || !strcmp(contents, "Set Size")) paramSelected = 5;


		
		imageParamSelected = true;
		
	}
}

void imgParameters::bindingSelectorEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_combobox_event(&selector, e, &draw))
	{

	}
}

void imgParameters::typeFilePath(SDL_Event* e, RenderWindow *inRenderWindow, SDL_Renderer* renderer)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&filePathEntry, e, &draw))
	{
		char* inputText = filePathEntry.text;
		//do stuff with inputText
		int i = 0;
		int w, h; 
		
		std::string returnString(inputText);


		int lastPeriod = returnString.find_last_of(".");
		if (lastPeriod == (-1)) 
		{
			//go into warning state
			imgKissGUI->kiss_string_copy(filePathEntry.text, 16, "Not a file Type", NULL);
			return;
			//
			
		}

		//std::cout << "lastPeriodIs " << lastPeriod << std::endl;
		std::string ext = returnString.substr(lastPeriod);
		transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
		if (ext.compare(".JPEG") == 0 || ext.compare(".PNG") == 0)
		{
			//*inString = returnString;
			//push the sprite onto this 
			//inRenderWindow->sprites.push_back();

			//is this a valid file? does it actually exist? does the SDL image return a bad path that we can check?
			SDL_Texture* image = IMG_LoadTexture(renderer, inputText);

			if (image == NULL) 
			{
				imgKissGUI->kiss_string_copy(filePathEntry.text, 18, "Invalid File Path", NULL);
				return;
			}

			//if not, render the file 

			SDL_QueryTexture(image, NULL, NULL, &w, &h);

			if (previousImageFlag==1) 
			{	

				inRenderWindow->arr_sprites[sceneIndex][index]->setRes(image);
				imageLoaded = true;
				return;
			}
			
			Sprite* temp = new Sprite(i * 0.1f, i * 0.1f, w, h, image);
			if (!inRenderWindow->addSprite(temp, sceneIndex)) {
				std::cout << "Add new image failure" << std::endl;
			}
			 //Sprite has been inserted
			previousImageFlag = 1;
			imageLoaded = true;
			return;

		}
			//go into warning state
			//char warning[KISS_MAX_LENGTH] = "Incompatible file type";
			//filePathEntry.text = warning;
			imgKissGUI->kiss_string_copy(filePathEntry.text, 17, "Invalid File type", NULL);
			
	}
}

void imgParameters::startLocation(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&start, e, &draw))
	{
		

	}
}

void imgParameters::endLocation(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&end, e, &draw))
	{

		std::string toFloat(end.text);
		std::istringstream iss(toFloat);
		float f;
		iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
		// Check the entire string was consumed and if either failbit or badbit is set
		if (iss.eof() && !iss.fail())
		{
			endValue = std::stof(toFloat);
			if (endValue > 1 || endValue < 0)
				imgKissGUI->kiss_string_copy(end.text, 14, "Must be (0-1)", NULL);
			endParamSelected = true;
			return;
		}

		imgKissGUI->kiss_string_copy(end.text, 12, "Not a Float", NULL);

		//we need to see if it's in range. 0 to 1.
		//check saftey on current binding. 

		//is this a note on/off?
		//check saftey on current binding. 

		//is this a note on/off?

	}
}

void imgParameters::midiLearnEvent(SDL_Event* e)
{
	/*
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&noteEntry, e, &draw))
	{

		char* inputText = noteEntry.text;
		//check if the note is infact a note. 

	}
	*/
}

void imgParameters::midiListenButton(SDL_Event* e, MidiModule* myMidiModule, RenderWindow* inRenderWindow)//save binding and add it to the binding selector dropdown?
{
	int draw = 1;
	bool isMidiType = false;
	char newText[200] = "newNote";
	if (imgKissGUI->kiss_button_event(&midiLearn, e, &draw))
	{
		if (!myMidiModule->isConnected())
		{

			//display warning
			warning = true;
			updateWarning("No Midi Device Connected");
			return; //if no connected devices, we will be in a loop forever.
		}

		if (!imageParamSelected)
		{
			warning = true;
			updateWarning("No Image Parameter selected");
			return;
		}
		if (!midiParamSelected)
		{
			warning = true;
			updateWarning("No Midi Message type selected");
			return;
		}
		if (!imageLoaded)
		{
			warning = true;
			updateWarning("Missing Image");
			return;
		}
		/*
		if (!endParamSelected)
		{
			warning = true;
			updateWarning("No endpoint selected");
			return;

		}
		*/


		if (!myMidiModule->isConnected())
		{
			return; //if no connected devices, we will be in a loop forever.
		}
		memset(noteEntry.text, 0, 200); //clear char array
		strcat(noteEntry.text, "newNote"); //fill char array with new note value
		while (!isMidiType)
		{
			if (myMidiModule->hasNewMidiMessage())
			{
				std::vector<juce::MidiMessage> inBuffer = myMidiModule->getMidiBuffer();

				for (int i = 0; i < inBuffer.size(); i++)
				{
					//std::cout << "message Recieved in Button: " << myMidiModule->printMessage(inBuffer[i]) << std::endl;

					//this is kinda gross, sorry
					switch(listenFilter)
					{
					case 0: //Note on
						if (inBuffer[i].isNoteOn())
						{
							isMidiType = true;
							memset(noteEntry.text, 0, 200); //clear char array

							string noteString = juce::MidiMessage::getMidiNoteName(inBuffer[i].getNoteNumber(), true, true, 3).toStdString();
							const char* newNote = noteString.c_str();
							strcat(noteEntry.text, newNote); //fill char array with new note value

							//Also, add this note to the translator app for the selected image param
							NoteBinding* newNoteBinding = new NoteBinding();
							newNoteBinding->noteNumber = inBuffer[i].getNoteNumber();
							newNoteBinding->noteChannel = inBuffer[i].getChannel();
							newNoteBinding->param = paramSelected;
							newNoteBinding->setOrScale = setOrScaleSelected;
							newNoteBinding->amountOrPosition = endValue;
							newNoteBinding->noteOffOn = 1;
							newNoteBinding->index = bindingIndex;
							inRenderWindow->arr_sprites[sceneIndex][index]->n_binding.push_back(newNoteBinding);
							
							std::string tmp = "" + std::to_string(bindingIndex + 1);
							std::string param(imgParam.entry.text);
							std::string type(midiParam.entry.text);
							tmp += "-" + param + " " + type + " " + noteString;
							char* bindingNumber = const_cast<char*>(tmp.c_str());
							imgKissGUI->kiss_array_appendstring(&bindingList, 0, bindingNumber, NULL);
							
								//bindings->ImageNoteBindings.push_back(newNoteBinding);
							//noteBindingIndex++;
							bindingIndex++;

						}

						break;

					case 1: //Note off
						if (inBuffer[i].isNoteOff())
						{
							isMidiType = true;
							memset(noteEntry.text, 0, 200); //clear char array
							string noteString = juce::MidiMessage::getMidiNoteName(inBuffer[i].getNoteNumber(), true, true, 3).toStdString();
							const char* newNote = noteString.c_str();
							strcat(noteEntry.text, newNote); //fill char array with new note value

							NoteBinding* newNoteBinding = new NoteBinding();
							newNoteBinding->noteNumber = inBuffer[i].getNoteNumber();
							newNoteBinding->noteChannel = inBuffer[i].getChannel();
							newNoteBinding->param = paramSelected;
							newNoteBinding->setOrScale = setOrScaleSelected;
							newNoteBinding->noteOffOn = 0;
							newNoteBinding->amountOrPosition = endValue;
							newNoteBinding->index = bindingIndex;
							inRenderWindow->arr_sprites[sceneIndex][index]->n_binding.push_back(newNoteBinding);
							
							std::string tmp = "" + std::to_string(bindingIndex + 1);
							std::string param(imgParam.entry.text);
							std::string type(midiParam.entry.text);
							tmp += "-" + param + " " + type + " " + noteString;
							char* bindingNumber = const_cast<char*>(tmp.c_str());
							imgKissGUI->kiss_array_appendstring(&bindingList, 0, bindingNumber, NULL);
							
							//bindings->ImageNoteBindings.push_back(newNoteBinding);
							bindingIndex++;
						}

						break;

					case 2: //CC
						if (inBuffer[i].isController())
						{
							isMidiType = true;
							memset(noteEntry.text, 0, 200); //clear char array
							string CCstr = "CC " + std::to_string(inBuffer[i].getControllerNumber());
							const char* newCC = CCstr.c_str(); //really long function to get note number / letter
							strcat(noteEntry.text, newCC); //fill char array with new note value


							CCBinding* newCCBinding = new CCBinding();
							newCCBinding->CCnumber = inBuffer[i].getControllerNumber();
							newCCBinding->CCChannel = inBuffer[i].getChannel();
							newCCBinding->param = paramSelected;
							newCCBinding->index = bindingIndex;
							inRenderWindow->arr_sprites[sceneIndex][index]->c_binding.push_back(newCCBinding);
							//bindings->ImageCCBindings.push_back(newCCBinding);
							
							
							std::string tmp = "" + std::to_string(bindingIndex + 1);
							std::string param(imgParam.entry.text);
							tmp += "-" + param + " " + CCstr;
							char* bindingNumber = const_cast<char*>(tmp.c_str());
							imgKissGUI->kiss_array_appendstring(&bindingList, 0, bindingNumber, NULL);
							
							//name this and place in Bindings selector

							bindingIndex++;

							//Also, add this note to the translator app for the selected image param
						}

						break;

					}

				}
				myMidiModule->messagesParsed(); //this clears the flag, and waits for a new message.

			}
		}


	}
}

void imgParameters::browseEvent(SDL_Event* e, RenderWindow myRenderWindow)
{
	int draw = 1;
	if (imgKissGUI->kiss_button_event(&browsePath, e, &draw))
	{
		myRenderWindow.openSceneFolder();
	}
}

void imgParameters::updateWarning(char* newText)
{
	imgKissGUI->kiss_label_new(&warningLabel, &warningWindow, newText, warningWindow.rect.x + 10, warningWindow.rect.y + 10);
}


void imgParameters::warningEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_button_event(&warningButton, e, &draw))
	{
		warning = false;
	}

}