#include "Shoot.h"
#include "game.h"
#include <iostream>

bool missleFired1 = false;
unsigned int lastFired = 0;
unsigned int currentTime;

BULLET missile[50];


void shootMissile1(unsigned int &currentMissile, COORD charLocation)
{
		missile[currentMissile].Active = true;
		missile[currentMissile].corrdinates.X = charLocation.X+1;
		missile[currentMissile].corrdinates.Y = charLocation.Y;
		missile[currentMissile].number = currentMissile;
		currentMissile++;
}
void shootMissile2(unsigned int &currentMissile, COORD charLocation)
{
	currentMissile=0;
	missile[currentMissile].Active = true;
	missile[currentMissile].corrdinates.X = charLocation.X+1;
	missile[currentMissile].corrdinates.Y = charLocation.Y;
	missile[currentMissile].number = currentMissile;
}
void renderMissile()
{
	for(int i = 0; i<50;i++)
	{

		if(missile[i].Active)
		{
			gotoXY(missile[i].corrdinates.X++,missile[i].corrdinates.Y);
			std::cout << '>'<< std::endl;

			if(missile[i].corrdinates.X > 50)
			{
				missile[i].Active = false;
			}
		}
	}

}