#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "midiLayer.h"
#include "Binding.hpp"
#include "RenderWindow.hpp"
#include "Sprite.hpp"

using namespace std;

class Translator
{
public:
	Translator(const RenderWindow& a) //const RenderWindow &a maybe as a argument to get sprite data and match them with bindings
	{
		vector<Sprite> sprites = a.sprites;
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
			str = strtok(&*txtbindings[i].begin(), ",");
			while (str.size() != NULL)
			{
				bindingtokens.push_back(str);
				str = strtok(NULL, ",");
			}

			Binding temp(stoi(bindingtokens[1]), stoi(bindingtokens[2]), stoi(bindingtokens[3]), stof(bindingtokens[4]));

			bindings.push_back(temp);
		}
	}

	void translate()
	{
		//Grab the offered up midiMessage from the midi input/controller
		midiMessage* buffer = pollMidiBuffer();
		int bufferlength = getMessageCount();
		//int bufferLength = pollMidiBufferLength();
		for (int i = 0; i < bufferlength; i++)
		{
			for (int j = 0; j < bindings.size(); j++)
			{
				if (bindings[j].getTrigger() != NULL && bindings[j].getTrigger() == buffer[i].payload0)
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
	vector<Binding> bindings;
};