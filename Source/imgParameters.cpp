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

imgParameters::imgParameters(int x, int y, int id, myKissGUI* kissGUI, kiss_window *inWindow, int layerNum)
{
	char layerChar = layerNum + 48;
	char layerArray[2] = { layerChar, };
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
	kissGUI->kiss_label_new(&IDNum, &binding, layerArray, binding.rect.x + 15, binding.rect.y + 15);

	binding.visible = 1;
}

void imgParameters::render(int newY, SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);

	imgKissGUI->kiss_window_draw(&binding, renderer);
	imgKissGUI->kiss_button_draw(&remove, renderer);
	imgKissGUI->kiss_button_draw(&browsePath, renderer);
	imgKissGUI->kiss_button_draw(&midiLearn, renderer);
	imgKissGUI->kiss_combobox_draw(&imgParam, renderer);
	imgKissGUI->kiss_combobox_draw(&midiParam, renderer);
	imgKissGUI->kiss_combobox_draw(&selector, renderer);
	imgKissGUI->kiss_entry_draw(&noteEntry, renderer);
	imgKissGUI->kiss_entry_draw(&filePathEntry, renderer);
	imgKissGUI->kiss_entry_draw(&start, renderer);
	imgKissGUI->kiss_entry_draw(&end, renderer);
	imgKissGUI->kiss_label_draw(&IDNum, renderer);

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

	/*int line = imgParam.textbox.selectedline;
	if (line) {
		void** p = imgParam.textbox.array->data + line;
		void* s = *p;
		char* selection = (char*)s;
	}
	imgKissGUI->kiss_combobox_new(&imgParam, &binding, selection, &imageParamList, binding.rect.x + 5, binding.rect.y + 50, 120, 100);
	imgParam.textbox.selectedline = line;*/

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
	}
}

void imgParameters::selectImageParamEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_combobox_event(&imgParam, e, &draw))
	{
		//do stuff like the previous box up there
	}
}

void imgParameters::bindingSelectorEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_combobox_event(&selector, e, &draw))
	{

	}
}

void imgParameters::typeFilePath(SDL_Event* e, std::string* inString)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&filePathEntry, e, &draw))
	{
		char* inputText = filePathEntry.text;
		//do stuff with inputText

		std::string returnString(inputText);

		*inString = returnString;


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

	}
}

void imgParameters::midiLearnEvent(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&noteEntry, e, &draw))
	{
		char* inputText = noteEntry.text;
		//check if the note is infact a note. 

	}
}

void imgParameters::midiListenButton(SDL_Event* e, MidiModule* myMidiModule)//save binding and add it to the binding selector dropdown?
{
	int draw = 1;
	bool isMidiType = false;
	char newText[200] = "newNote";
	if (imgKissGUI->kiss_button_event(&midiLearn, e, &draw))
	{

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

							//Also, add this note to the translator app for the selected image param
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