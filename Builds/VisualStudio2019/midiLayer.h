#include <stdint.h>
#include <iostream>
#include <string>

#define noteOff 0
#define noteOn 1
#define controlChange 2

typedef struct
{
	uint8_t midiMessageType;
	uint8_t midiChannel;
	uint8_t payload0;
	uint8_t payload1;
} midiMessage;



void fillTestArray(); //just for testing. should be moved to a testing library later.
void initMidi(); //initializes what's neccesary for midi functionality
std::string getPortNames(); //get the names of all availible midi input ports
void setMidiPort(int midiPort); //sets the current midi Port
midiMessage* pollMidiBuffer(); //returns an array of current Midi Messages 
uint16_t getMessageCount();
std::string printMidiMessage(midiMessage inputMidiMessage); //returns a Text version of a midi message