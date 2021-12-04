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

imgParameters::imgParameters(int x, int y, int id, myKissGUI* kissGUI, kiss_window *inWindow)
{
	imgKissGUI = kissGUI;
	kissGUI->fillMidiParam(&midiParamList);
	kissGUI->fillImageParam(&imageParamList);
	kissGUI->kiss_window_new(&binding, inWindow, 1, x, y, 480, 90);
	kissGUI->kiss_combobox_new(&imgParam, &binding, "Image Param", &imageParamList, binding.rect.x + 5, binding.rect.y + 50, 120, 100);
	kissGUI->kiss_combobox_new(&midiParam, &binding, "Midi Param", &midiParamList, binding.rect.x + 140, binding.rect.y + 50, 110, 100);
	kissGUI->kiss_entry_new(&noteEntry, &binding, 1, "Note/CC", binding.rect.x + 270, binding.rect.y + 50, 100);
	kissGUI->kiss_entry_new(&filePathEntry, &binding, 1, "FilePath", binding.rect.x + 5, binding.rect.y + 10, 400);
	kissGUI->kiss_button_new(&browsePath, &binding, "Browse", binding.rect.x + 410, binding.rect.y + 15);
	kissGUI->kiss_button_new(&midiLearn, &binding, "Listen", binding.rect.x + 370, binding.rect.y + 55);
	kissGUI->kiss_label_new(&IDNum, &binding, "#", binding.rect.x + 440, binding.rect.y + 57);

	binding.visible = 1;
}

void imgParameters::render(int newY, SDL_Renderer* renderer)
{
	//SDL_RenderClear(renderer);

	imgKissGUI->kiss_window_draw(&binding, renderer);
	imgKissGUI->kiss_button_draw(&browsePath, renderer);
	imgKissGUI->kiss_button_draw(&midiLearn, renderer);
	imgKissGUI->kiss_combobox_draw(&imgParam, renderer);
	imgKissGUI->kiss_combobox_draw(&midiParam, renderer);
	imgKissGUI->kiss_entry_draw(&noteEntry, renderer);
	imgKissGUI->kiss_entry_draw(&filePathEntry, renderer);
	imgKissGUI->kiss_label_draw(&IDNum, renderer);

	//SDL_RenderPresent(renderer);
}

void imgParameters::imgScroll(SDL_Event* e, int direction)//shift should be the same distance both ways so direction will just be a negative for up and a positive for down
{

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

void imgParameters::typeFilePath(SDL_Event* e)
{
	int draw = 1;
	if (imgKissGUI->kiss_entry_event(&filePathEntry, e, &draw))
	{
		char* inputText = filePathEntry.text;
		//do stuff with inputText

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

void imgParameters::midiListenButton(SDL_Event* e, MidiModule* myMidiModule)
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