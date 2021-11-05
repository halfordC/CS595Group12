#include <stdint.h>
#include <iostream>
#include <string>

typedef struct
{
	int trigger;
	std::string path; //Maybe? or an sdl texture or surface or something
	float x, y, size, alpha;
	int rotation;
	// float tempX, tempY, tempSize, tempAlpha; //to implement timed events
	// int tempRotation;
	bool type; //type of change T:set F:scale
	int property; //target of the adjustments 1:x 2:y 3:scale 4:rotation 5:alpha
	float sizeTarget, sizeScaleTarget, xTarget, xScaleTarget, yTarget, yScaleTarget, alphaTarget, alphaScaleTarget;
	int  rotationTarget, rotationScaleTarget;
} binding;

//These access and mutate their respective properties
void setX(binding b);
void scaleX(binding b);
void setY(binding b);
void scaleY(binding b);
void setSize(binding b);
void scaleSize(binding b);
void setRotation(binding b);
void scaleRotation(binding b);
void setAlpha(binding b);
void scaleAlpha(binding b);