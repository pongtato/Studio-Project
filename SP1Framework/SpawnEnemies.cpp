#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>

ENEMY counter[999];
ENEMY Wew;
int state = 1;

void moveEnemies()
{
	// number of enemies
		int i=1;
		//is enemy alive
		if(counter[i].Active == true)
		{
			if ( state == 1)
			{
				gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);
				std::cout << counter[i].icon;

				if ( counter[i].coordinates.Y< 5 )
				{
					counter[i].coordinates.X--;
					state=3;
				}
			}

			if ( state == 3)
			{
				gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
				std::cout << counter[i].icon;

				if ( counter[i].coordinates.Y>=15 )
				{
					counter[i].coordinates.X--;
					state=1;
				}
			}
		}
	
}

void enemyMove(unsigned int &currentEnemy)
{
	counter[currentEnemy].Active = true;
	counter[currentEnemy].coordinates.X = 30;
	counter[currentEnemy].coordinates.Y = 10;
	counter[currentEnemy].hp=1;
	counter[currentEnemy].score=10;
	counter[currentEnemy].icon=(char)5;
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = 0;
	currentEnemy++;
}