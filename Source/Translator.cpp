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

using namespace std;
namespace fs = std::filesystem;

class Translator
{
public:
	Translator(const RenderWindow& a) //const RenderWindow &a maybe as a argument to get sprite data and match them with bindings
	{
		vector<Sprite*> sprites = a.sprites;
		vector<string> txtbindings;
		vector<string> bindingtokens;
		//midiModule = a.midiModule;

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

	void translate(const RenderWindow& a)
	{
		if (myMidiModule->hasNewMidiMessage())
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

	vector<string> getImages()
	{
		vector<string> out;
		fs::path cwd = fs::current_path();

#ifdef __APPLE__
	cwd += "/scenes";
#elif _WIN32
	cwd += "\\scenes";
#endif
		
		int i = 0;
		int w, h;
		for (auto& dir_entry : fs::directory_iterator(cwd))
		{
			if (!fs::is_directory(dir_entry))
			{
				/* Pull file extension and set to upper case for string comparison. */
				string ext = dir_entry.path().extension().string();
				std::for_each(ext.begin(), ext.end(), [](char& c) {
					c = ::toupper(c);
					});

				/* Only allow JPEG or PNG at this time as I am a lazy POS */
				if (ext.compare(".JPEG") == 0 || ext.compare(".PNG") == 0)
				{
					out.push_back(dir_entry.path().filename().string());
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