#include <stdint.h>
#include <iostream>
#include <string>

#include "midiModule.h"
#include "Binding.h"

binding parsedBindings[10];

void translate(MidiModule *midiIn)
{
    //is there a new Message?
    if (midiIn->hasNewMidiMessage()) {
        //Grab the offered up midiMessage from the midi input/controller
        std::vector<juce::MidiMessage> buffer = midiIn->getMidiBuffer();
        midiIn->messagesParsed(); //we want to do this here, so that we can recieved new messages whil we are parsing them. 
        for (int i = 0; i < buffer.size(); i++)
        {
            for (int j = 0; j < 10; j++)
            {
                uint8_t payload0;
                if (buffer[i].isController()) 
                {
                    payload0 = buffer[i].getControllerNumber();
                }
                else if (buffer[i].isNoteOnOrOff()) 
                {
                    payload0 = buffer[i].getNoteNumber();
                }
                if (parsedBindings[j].trigger != NULL && parsedBindings[j].trigger == payload0)
                {
                    switch (parsedBindings[j].property)
                    {
                    case 1: //type = 1 | X
                    {
                        if (parsedBindings[j].type == true)
                            setX(parsedBindings[j]);
                        else
                            scaleX(parsedBindings[j]);
                        break;
                    }
                    case 2: //type = 2 | Y
                    {
                        if (parsedBindings[j].type == true)
                            setY(parsedBindings[j]);
                        else
                            scaleY(parsedBindings[j]);
                        break;
                    }
                    case 3: //type = 3 | Size
                    {
                        if (parsedBindings[j].type == true)
                            setSize(parsedBindings[j]);
                        else
                            scaleSize(parsedBindings[j]);
                        break;
                    }
                    case 4: //type = 4 | Rotation
                    {
                        if (parsedBindings[j].type == true)
                            setRotation(parsedBindings[j]);
                        else
                            scaleRotation(parsedBindings[j]);
                        break;
                    }
                    case 5: //type = 5 | Alpha
                    {
                        if (parsedBindings[j].type == true)
                            setAlpha(parsedBindings[j]);
                        else
                            scaleAlpha(parsedBindings[j]);
                        break;
                    }
                    default: // code to be executed if n doesn't match any cases
                        std::cout << "Failed to execute Binding!" << std::endl;
                    }
                }
            }

        }
    }
}

void setX(binding b)
{
	b.x = b.xTarget;
}
void scaleX(binding b)
{
	b.x = b.x * b.xScaleTarget;
}
void setY(binding b)
{
	b.y = b.yTarget;
}
void scaleY(binding b)
{
	b.y = b.y * b.yScaleTarget;
}
void setSize(binding b)
{
	b.size = b.sizeTarget;
}
void scaleSize(binding b)
{
	b.size = b.size * b.sizeScaleTarget;
}
void setRotation(binding b)
{
	b.rotation = b.rotationTarget;
}
void scaleRotation(binding b)
{
	b.rotation = b.rotation * b.rotationScaleTarget;
}
void setAlpha(binding b)
{
	b.alpha = b.alphaTarget;
}
void scaleAlpha(binding b)
{
	b.alpha = b.alpha * b.alphaScaleTarget;
}