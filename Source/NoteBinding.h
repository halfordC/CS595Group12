#include <stdint.h>
#include <iostream>
#include <string>
#include <stdio.h>


class NoteBinding 
{
public:
	NoteBinding();
	~NoteBinding();

	uint8_t noteNumber; //value from 0 to 127
	uint8_t noteChannel; //value from 0 to 15
	uint8_t noteOffOn; // 0 = off, 1 = On
	uint8_t param; //Which property to target: 0=x, 1=y, 2=width, 3=heigt, 4=rotation, 5=scale, 6=Layer On
	uint8_t setOrScale; //Type of change: 0=Set, 1=Scale
	float amountOrPosition; //value to scale by, or to set to. 
private:

};