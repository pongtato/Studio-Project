#include "Shoot.h"

#include "game.h"
#include <iostream>



BULLET missile[50];


void shootMissile1(unsigned int &currentMissile, COORD charLocation)
{
		missile[currentMissile].Active = true;
		missile[currentMissile].icon = '>';
		missile[currentMissile].corrdinates.X = charLocation.X+1;
		missile[currentMissile].corrdinates.Y = charLocation.Y;
		missile[currentMissile].number = currentMissile;
		currentMissile++;
}
void shootMissile2(unsigned int &currentMissile, COORD charLocation)
{
	currentMissile=0;
	missile[currentMissile].Active = true;
	missile[currentMissile].icon = '>';
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
			std::cout << missile[i].icon << std::endl;

			//Check if out of bound
			if(missile[i].corrdinates.X > 50)
			{
				missile[i].Active = false;
			}
		}
	}

}
void checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy)
{
	
	if(((missile.corrdinates.X+1 == checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y)//Check directly infront 
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y-1 == checkEnemy.coordinates.Y)//Check above
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y+1 == checkEnemy.coordinates.Y))&&checkEnemy.Active)//Check below
	{
		
 		missile.icon = ' ';
		missile.Active = false;
		
		checkEnemy.icon = ' ';
		checkEnemy.Active = false;
		//increase score
	}

}