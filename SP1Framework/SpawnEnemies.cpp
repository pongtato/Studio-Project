#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>


ENEMY counter[999];
int state = 1;

void moveEnemies()
{
	// number of enemies
	for ( int i = 0; i < 20; ++i)
	{

		//is enemy alive
		if(counter[i].Active == true)
		{
			if ( state == 1)
			{
				gotoXY(counter[i].coordinates.X--,counter[i].coordinates.Y);
				gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);

				std::cout << counter[i].icon;

			/*	if ( counter[i].coordinates.Y< 5 )
				{
					counter[i].coordinates.X--;
					state=3;
				}*/
			}

			/*if ( state == 3)
			{
				gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
				std::cout << counter[i].icon;

				if ( counter[i].coordinates.Y>=15 )
				{
					counter[i].coordinates.X--;
					state=1;
				}
			}*/
		}
	}

}


void SpawnEnemy(unsigned int &currentEnemy)
{	
	counter[currentEnemy].Active = true;
	counter[currentEnemy].coordinates.X = 50;
	counter[currentEnemy].coordinates.Y = rand()%15 + 5;
	counter[currentEnemy].hp=1;
	counter[currentEnemy].score=10;
	counter[currentEnemy].icon=(char)5;
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = 0;
	currentEnemy++;
}

