#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiModule.h"
#include "Binding.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"
#include "Translator.h"

extern std::vector<Sprite>* sprites;

using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

//using namespace std;
//namespace fs = std::filesystem;
	Translator::Translator() //const RenderWindow &a maybe as a argument to get sprite data and match them with bindings
	{
		vector<std::string> txtbindings;
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
	}

	void Translator::updateBindings()
	{
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
	}

	void Translator::translate(RenderWindow* a, MidiModule* myMidiModule)
	{
		if (midimod->hasNewMidiMessage())
		{
			//Grab the offered up midiMessage from the midi input/controller
			vector<juce::MidiMessage> buffer = myMidiModule->getMidiBuffer();
			int bufferlength = buffer.size();
			//int bufferLength = pollMidiBufferLength();
			for (int i = 0; i < bufferlength; i++)
			{
				for (int j = 0; j < bindings.size(); j++)
				{
					if (bindings[j].getTrigger() != NULL && bindings[j].getTrigger() == buffer[i].getNoteNumber())
					{
						switch (bindings[j].getTarget())
						{
							case 0: //target = 1 | X
							{
								if (bindings[j].getType() == 0) //type = 0: Set
									setX(bindings[j], a, j);
								else //Scale
									scaleX(bindings[j], a, j);
								break;
							}

							case 1: //target = 2 | Y
							{
								if (bindings[j].getType() == 0) //type = 0: Set
									setY(bindings[j], a, j);
								else //Scale
									scaleY(bindings[j], a, j);
								break;
							}

							case 2: //target = 3 | Size
							{
								if (bindings[j].getType() == 0) //type = 0: Set
									setSize(bindings[j], a, j);
								else //Scale
									scaleSize(bindings[j], a, j);
								break;
							}

							case 3: //target = 4 | Rotation
							{
								if (bindings[j].getType() == 0) //type = 0: Set
									setRotation(bindings[j], a, j);
								else //Scale
									scaleRotation(bindings[j], a, j);
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
		}
	}

#pragma region X
	void Translator::setX(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setX(b.getAmount());
	}
	void scaleX(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setX(s->getX() * b.getAmount());
	}
#pragma endregion
#pragma region Y
	void Translator::setY(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setY(b.getAmount());
	}
	void Translator::scaleY(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setY(s->getX() * b.getAmount());
	}
#pragma endregion
#pragma region Width
	void Translator::setWidth(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setWidth(b.getAmount());
	}
	void Translator::scaleWidth(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setWidth(s->getX() * b.getAmount());
	}
#pragma endregion
#pragma region Height
	void Translator::setHeight(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setHeight(b.getAmount());
	}
	void Translator::scaleHeight(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setHeight(s->getX() * b.getAmount());
	}
#pragma endregion
#pragma region Size
	void Translator::setSize(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setScale(b.getAmount());
	}
	void Translator::scaleSize(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setScale(s->getX() * b.getAmount());
	}
#pragma endregion
#pragma region Rotation
	void Translator::setRotation(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setRotation(b.getAmount());
	}
	void Translator::scaleRotation(Binding b, RenderWindow* a, int i)
	{
		Sprite* s = a->sprites[i];
		s->setRotation(s->getX() * b.getAmount());
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