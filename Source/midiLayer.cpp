#include <stdint.h>
#include <iostream>
#include <string>

#include "midiLayer.h"

midiMessage midiBuffer[1024];
uint16_t messageCount = 0; //This 
extern uint8_t frameCounter;
//This is just for testing, the full messages will arrive in midiBuffer. 
//at 120 BPM, we're at 2 beats a second, 1 beat every 15 frames
/*
our test pattern looks like this:
Kick 	|---|---|---|---
Snare	----|-------|---
HiHat	|-|-|-|-|-|-|-|-

This happens over 60 frames at 30 fps.


*/
midiMessage kick = { noteOn, 10, 36, 127 };
midiMessage snare = { noteOn, 10, 40, 127 };
midiMessage hiHat = { noteOn, 10, 42, 127 };

midiMessage beat1[3] = { kick, hiHat, {0} };
midiMessage beat2[3] = { hiHat, {0}, {0} };
midiMessage beat3[3] = { kick, snare, hiHat };
midiMessage nothing[3] = { {0},{0}, {0} };

void copyMidiMessage(midiMessage copyTo, midiMessage copyFrom)
{
	copyTo.midiMessageType = copyFrom.midiMessageType;
	copyTo.midiChannel = copyFrom.midiChannel;
	copyTo.payload0 = copyFrom.payload0;
	copyTo.payload1 = copyFrom.payload1;
}

void fillTestArray()
{
	for (int i = 0; i < 1024; i++)
	{
		midiBuffer[i] = { 0 };
	}

}

void initMidi()
{
	//currently does nothing, this is a stub
	//this is where we put our setup code
}

void getPortNames(std::string* portNames)
{
	//This will be a single string with a ; deleminator. 
	*portNames = "myMidi Device 1 ; myMidi Device 2";
}


void setMidiPort(int midiPort)
{
	//this function doesn't do anything at the moment, just takes 

}

midiMessage* pollMidiBuffer()
{
	//This is currently only for testing. The real version of this will return real stuff. 
	if (frameCounter % 7 == 0)
	{
		messageCount = 1;

		for (int i = 0; i < 4; i++)
		{
			copyMidiMessage(midiBuffer[i], beat2[i]);
		}
	}

	if (frameCounter % 15 == 0) //happens every 0 and 15
	{
		messageCount = 2;
		for (int i = 0; i < 4; i++)
		{
			copyMidiMessage(midiBuffer[i], beat1[i]);
		}
	}

	if (frameCounter % 30 == 0) //happens on beat 0 and 30.
	{
		messageCount = 3;
		for (int i = 0; i < 4; i++)
		{
			copyMidiMessage(midiBuffer[i], beat3[i]);
		}
	}
	else
	{
		messageCount = 0;
		for (int i = 0; i < 4; i++)
		{
			copyMidiMessage(midiBuffer[i], nothing[i]);
		}
	}

	frameCounter++;

	if (frameCounter >= 31)
	{
		frameCounter = 1;
	}


	return midiBuffer;
}


std::string printMidiMessage(midiMessage inputMidiMessage)
{
	std::string returnMe = "Channel is: " + std::to_string(inputMidiMessage.midiMessageType) +
		"\n Message type is: " + std::to_string(inputMidiMessage.midiChannel) +
		"\n payload0 is : " + std::to_string(inputMidiMessage.payload0) +
		"\n payload1 is : " + std::to_string(inputMidiMessage.payload1) +
		"\n frameCounter is : " + std::to_string(frameCounter);

	return returnMe;
}

uint16_t getMessageCount()
{
	return messageCount;

}