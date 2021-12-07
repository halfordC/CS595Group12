#include <stdint.h>
#include <iostream>
#include <string>

class CCBinding 
{
public:
	CCBinding();
	~CCBinding();
	int param; //Which property to target: 0=x, 1=y, 2=width, 3=heigt, 4=rotation, 5=scale
	uint8_t CCnumber;
	uint8_t CCChannel;
private:
	

};