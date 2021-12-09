#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiModule.h"
#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "ImageBinders.h"
#include "NoteBinding.h"
#include "CCBinding.h"
#include "Translator.h"
#include "UserGUI.hpp"


//using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

//namespace fs = std::filesystem;




Translator::Translator(UserGUI* InGUI) //const RenderWindow &a maybe as a argument to get sprite data and match them with bindings
{
	translatorGUI = InGUI;
	translatorScenes = translatorGUI->getCurrentSceneArray(); //this may not work? I'm not sure if we need to copy vectors or not. 

	//we will fix the constructor once we get translation working. If we can get midi stuff moving, then we'll work on file io.
	/*
	vector<string> txtbindings;
	vector<string> bindingtokens;

	string str;
	std::ifstream infile;
	infile.open("bindings.txt");
	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, str); // Saves the line in str.
		txtbindings.push_back(str);
	}
	infile.close(); //saves lines in txtbindings

	string p = "";
	int trig;
	int tar;
	int typ;
	int amnt;

	//For each binding line tokenize and create bindings
	for (int i = 0; i < txtbindings.size(); i++)
	{
		//split bindings by their label and values
		str = strtok(&*txtbindings[i].begin(), ",:");
		while (str.size() != NULL)
		{
			bindingtokens.push_back(str);
			str = strtok(NULL, ",");
		}

		//Check if there are any missing values and reject any incomplete bindings
		if (bindingtokens.size() == 12)
		{
			//grab every other value since even ones are the 
			for (int i = 0; i < 6; i++)
			{
				if (bindingtokens[(int)i * 2] == "Path")
					p = bindingtokens[(int)i + 1];
				else if (bindingtokens[(int)i * 2] == "Trigger")
					trig = stoi(bindingtokens[(int)i + 1]);
				else if (bindingtokens[(int)i * 2] == "MessageType")
					typ = stoi(bindingtokens[(int)i + 1]);
				else if (bindingtokens[(int)i * 2] == "Target")
					tar = stoi(bindingtokens[(int)i + 1]);
				else if (bindingtokens[(int)i * 2] == "ChangeType")
					typ = stoi(bindingtokens[(int)i + 1]);
				else if (bindingtokens[(int)i * 2] == "Amount")
					amnt = stoi(bindingtokens[(int)i + 1]);
			}
		}
		else
			cout << "Incorrect Binding for Path: " << bindingtokens[0] << endl;

		if (p != "" && trig != NULL && typ != NULL && tar != NULL && typ != NULL && amnt != NULL)
		{
			Binding temp(bindingtokens[1], stoi(bindingtokens[3]), stoi(bindingtokens[5]), stoi(bindingtokens[7]), stoi(bindingtokens[9]), stof(bindingtokens[11]));
			bindings.push_back(temp);
		}
		else
			cout << "Incorrect Binding for Path: " << bindingtokens[0] << endl;
			
	}
	*/
}

void Translator::updateBindings()
{
	//see constructor
	/*
	std::ofstream file;
	file.open("bindings.txt");
	string bindingstr = "";
	if (file.is_open())
	{
		for (Binding b : bindings)
		{
			bindingstr = "";

			bindingstr.append(strcat("Path:", b.getPath().c_str()));
			bindingstr.append(",");
			bindingstr.append(strcat("Trigger:", std::to_string(b.getTrigger()).c_str()));
			bindingstr.append(",");
			bindingstr.append(strcat("MessageType:", std::to_string(b.getMessageType()).c_str()));
			bindingstr.append(",");
			bindingstr.append(strcat("Target:", std::to_string(b.getTarget()).c_str()));
			bindingstr.append(",");
			bindingstr.append(strcat("ChangeType:", std::to_string(b.getType()).c_str()));
			bindingstr.append(",");
			bindingstr.append(strcat("Amount:", std::to_string(b.getAmount()).c_str()));
			bindingstr.append("\n");

			file << bindingstr;
		}
	}

	*/
}


//TODO: Refactor with Image Bindings
void Translator::translate(RenderWindow* a, MidiModule* myMidiModule)
{
	if (translatorGUI->addSceneFlag) 
	{
		translatorScenes = translatorGUI->getCurrentSceneArray();
	}
	if (myMidiModule->hasNewMidiMessage())
	{
		//Grab the offered up midiMessage from the midi input/controller
		vector<juce::MidiMessage> buffer = myMidiModule->getMidiBuffer();
		int bufferlength = buffer.size();
		if (bufferlength == 0) 
		{
			myMidiModule->messagesParsed();
			return;
		}


		for (int i = 0; i < bufferlength; i++)
		{
			Scene* currentScene = translatorScenes[translatorGUI->sceneIndex];
			//grab the number of images in the current scene
			int numImages = currentScene->SceneImageBindings.size();
			for (int j = 0; j< numImages; j++) 
			{
				ImageBinders* currentImage = currentScene->SceneImageBindings[j];
				//update each image in the scene:
				if (buffer[i].isNoteOnOrOff())
				{
					for (int k = 0; k < currentImage->ImageNoteBindings.size(); k++)
					{
						NoteBinding* currentNoteBinding = currentImage->ImageNoteBindings[k];
						if (currentNoteBinding->noteNumber != NULL && currentNoteBinding->noteNumber == buffer[i].getNoteNumber())
						{
							switch (currentNoteBinding->param)
							{
							case 0: //target = 1 | X
							{
								if (currentNoteBinding->setOrScale == 0) //type = 0: Set
									NoteSetX(*currentNoteBinding, a, k);
								else //Scale
									NoteScaleX(*currentNoteBinding, a, k);
								break;
							}

							case 1: //target = 2 | Y
							{
								if (currentNoteBinding->setOrScale == 0) //type = 0: Set
									NoteSetY(*currentNoteBinding, a, k);
								else //Scale
									NoteScaleY(*currentNoteBinding, a, k);
								break;
							}

							case 2: //target = 3 | Size
							{
								if (currentNoteBinding->setOrScale == 0) //type = 0: Set
									NoteSetSize(*currentNoteBinding, a, k);
								else //Scale
									NoteScaleSize(*currentNoteBinding, a, k);
								break;
							}

							case 3: //target = 4 | Rotation
							{
								if (currentNoteBinding->setOrScale == 0) //type = 0: Set
									NoteSetRotation(*currentNoteBinding, a, k);
								else //Scale
									NoteScaleRotation(*currentNoteBinding, a, k);
								break;
							}

							//case 4: //target = 5 | Alpha
							//{
							//	if (bindings[j].getType() == 0) //type = 0: Set
							//		setAlpha(bindings[j], a);
							//	else //Scale
							//		scaleAlpha(bindings[j], a);
							//	break;
							//}

							default: // code to be executed if n doesn't match any cases
								cout << "Failed to execute Binding!" << endl;
							}
						}

					}
				}
				if(buffer[i].isController())
				{
					//do CC updates here. 
					for (int m = 0; m < currentImage->ImageCCBindings.size(); m++)
					{
						CCBinding* currentCCBinding = currentImage->ImageCCBindings[m];
						if (currentCCBinding->CCnumber != NULL && currentCCBinding->CCnumber == buffer[i].getControllerNumber())
						{
							switch (currentCCBinding->param)
							{
							case 0: //target = 1 | X
							{
								CCSetX(*currentCCBinding, a, m, buffer[i].getControllerValue());
								break;
							}

							case 1: //target = 2 | Y
							{
								CCSetY(*currentCCBinding, a, m, buffer[i].getControllerValue());
								break;
							}

							case 2: //target = 3 | Size
							{
								CCSetSize(*currentCCBinding, a, m, buffer[i].getControllerValue()); 
								break;
							}

							case 3: //target = 4 | Rotation
							{
								CCSetRotation(*currentCCBinding, a, m, buffer[i].getControllerValue()); 
								break;
							}

							//case 4: //target = 5 | Alpha
							//{
							//	if (bindings[j].getType() == 0) //type = 0: Set
							//		setAlpha(bindings[j], a);
							//	else //Scale
							//		scaleAlpha(bindings[j], a);
							//	break;
							//}

							default: // code to be executed if n doesn't match any cases
								cout << "Failed to execute Binding!" << endl;
							}
						}

					}

				}

			//we need two seperate loops, one for our Notes, and one for Our CCs. 
			}
		}

		myMidiModule->messagesParsed();
	}
}

#pragma region X
void Translator::NoteSetX(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setX(b.amountOrPosition);
}
void Translator::NoteScaleX(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setX(s->getX() * b.amountOrPosition);
}

void Translator::CCSetX(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127; 
	Sprite* s = a->sprites[i];
	s->setX(inCC);
}
#pragma endregion
#pragma region Y
void Translator::NoteSetY(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setY(b.amountOrPosition);
}
void Translator::NoteScaleY(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setY(s->getX() * b.amountOrPosition);
}
void Translator::CCSetY(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127;
	Sprite* s = a->sprites[i];
	s->setY(inCC);
}
#pragma endregion
#pragma region Width
void Translator::NoteSetWidth(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setWidth(b.amountOrPosition);
}
void Translator::NoteScaleWidth(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setWidth(s->getX() * b.amountOrPosition);
}
void Translator::CCSetWidth(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127;
	Sprite* s = a->sprites[i];
	s->setWidth(inCC);
}
#pragma endregion
#pragma region Height
void Translator::NoteSetHeight(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setHeight(b.amountOrPosition);
}
void Translator::NoteScaleHeight(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setHeight(s->getX() * b.amountOrPosition);
}
void Translator::CCSetHeight(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127;
	Sprite* s = a->sprites[i];
	s->setHeight(inCC);
}
#pragma endregion
#pragma region Size
void Translator::NoteSetSize(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setScale(b.amountOrPosition);
}
void Translator::NoteScaleSize(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setScale(s->getX() * b.amountOrPosition);
}
void Translator::CCSetSize(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127;
	Sprite* s = a->sprites[i];
	s->setScale(inCC);
}
#pragma endregion
#pragma region Rotation
void Translator::NoteSetRotation(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setRotation(b.amountOrPosition);
}
void Translator::NoteScaleRotation(NoteBinding b, RenderWindow* a, int i)
{
	Sprite* s = a->sprites[i];
	s->setRotation(s->getX() * b.amountOrPosition);
}
void Translator::CCSetRotation(CCBinding b, RenderWindow* a, int i, int ccValue)
{
	float inCC = (float)ccValue / (float)127;
	Sprite* s = a->sprites[i];
	s->setRotation(inCC);
}
#pragma endregion
//#pragma region Alpha
//	void scaleAlpha(Binding b, RenderWindow* a)
//	{
//
//	}
//	void setAlpha(Binding b, RenderWindow* a)
//	{
//
//	}
//#pragma endregion