#include <stdint.h>
#include <iostream>
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
		while (!infile.eof) // To get you all the lines.
		{
			getline(infile, str); // Saves the line in str.
			txtbindings.push_back(str);
		}
		infile.close(); //saves lines in txtbindings

		//For each binding line tokenize and create bindings
		for (int i = 0; i < txtbindings.size(); i++)
		{
			str = strtok(txtbindings[i], ",");
			while (str != NULL)
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
				if (bindings[j].trigger != NULL && bindings[j].trigger == buffer[i].payload0)
				{
					switch (bindings[j].target)
					{
					case 0: //target = 1 | X
					{
						if (bindings[j].type == 0) //type = 0: Set
							sprites[j].setX(bindings[j].amount);
						else //Scale
							scaleX(bindings[j]);
						break;
					}
					case 1: //target = 2 | Y
					{
						if (bindings[j].type == 0) //type = 0: Set
							setY(bindings[j]);
						else //Scale
							scaleY(bindings[j]);
						break;
					}
					case 2: //target = 3 | Size
					{
						if (bindings[j].type == 0) //type = 0: Set
							setSize(bindings[j]);
						else //Scale
							scaleSize(bindings[j]);
						break;
					}
					case 3: //target = 4 | Rotation
					{
						if (bindings[j].type == 0) //type = 0: Set
							setRotation(bindings[j]);
						else //Scale
							scaleRotation(bindings[j]);
						break;
					}
					case 4: //target = 5 | Alpha
					{
						if (bindings[j].type == 0) //type = 0: Set
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
private:
	vector<Binding> bindings;
};