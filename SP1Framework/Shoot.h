#ifndef _SHOOT_H
#define _SHOOT_H

#include "Framework\console.h"

struct BULLET
{
	COORD corrdinates;
	bool Active;
	int number;
};

void renderMissile();		// renders missiles in the game
void shootMissile1(unsigned int &currentMissile, COORD charLocation);
void shootMissile2(unsigned int &currentMissile, COORD charLocation);


#endif // _SHOOT_H