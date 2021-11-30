#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiModule.h"
#include "Binding.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"

extern MidiModule* myMidiModule;
extern std::vector<Sprite>* sprites;

using namespace std;
namespace fs = std::filesystem;

class Translator
{
public:
	Translator() //const RenderWindow &a maybe as a argument to get sprite data and match them with bindings
	{
		vector<string> txtbindings;
		vector<string> bindingtokens;

		string str;
		ifstream infile;
		infile.open("bindings.txt");
		while (!infile.eof()) // To get you all the lines.
		{
			getline(infile, str); // Saves the line in str.
			txtbindings.push_back(str);
		}
		infile.close(); //saves lines in txtbindings

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
			if (bindingtokens.size() >= 10)
			{
				//grab every other value since even ones are the labels
				string p;
				int trig;
				int tar;
				int typ;
				int amnt;

				Binding temp(bindingtokens[1], stoi(bindingtokens[3]), stoi(bindingtokens[5]), stoi(bindingtokens[7]), stof(bindingtokens[9]));
				bindings.push_back(temp);
			}
			else
				cout << "Incorrect Binding for Path: " << bindingtokens[0] << endl;
		}


	}

	void translate(const RenderWindow& a)
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
								setX(bindings[j]);
							else //Scale
								scaleX(bindings[j]);
							break;
						}
						case 1: //target = 2 | Y
						{
							if (bindings[j].getType() == 0) //type = 0: Set
								setY(bindings[j]);
							else //Scale
								scaleY(bindings[j]);
							break;
						}
						case 2: //target = 3 | Size
						{
							if (bindings[j].getType() == 0) //type = 0: Set
								setSize(bindings[j]);
							else //Scale
								scaleSize(bindings[j]);
							break;
						}
						case 3: //target = 4 | Rotation
						{
							if (bindings[j].getType() == 0) //type = 0: Set
								setRotation(bindings[j]);
							else //Scale
								scaleRotation(bindings[j]);
							break;
						}
						case 4: //target = 5 | Alpha
						{
							if (bindings[j].getType() == 0) //type = 0: Set
								setAlpha(bindings[j]);
							else //Scale
								scaleAlpha(bindings[j]);
							break;
						}
						default: // code to be executed if n doesn't match any cases
							cout << "Failed to execute Binding!" << endl;
						}
					}
				}
			}
		}
	}
#pragma region X
	void setX(Binding b)
	{

	}
	void scaleX(Binding b)
	{

	}
#pragma endregion
#pragma region Y
	void setY(Binding b)
	{

	}
	void scaleY(Binding b)
	{

	}
#pragma endregion
#pragma region Size
	void setSize(Binding b)
	{

	}
	void scaleSize(Binding b)
	{

	}
#pragma endregion
#pragma region Rotation
	void setRotation(Binding b)
	{

	}
	void scaleRotation(Binding b)
	{

	}
#pragma endregion
#pragma region Alpha
	void scaleAlpha(Binding b)
	{

	}
	void setAlpha(Binding b)
	{

	}
#pragma endregion
private:
	MidiModule* midimod;
	vector<Binding> bindings;
};