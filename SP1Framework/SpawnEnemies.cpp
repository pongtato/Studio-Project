#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>

ENEMY counter[26];
ENEMY Wew;
int state = 0;

void moveEnemies()
{
	for(int i = 0; i<1;i++)
	{
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);
			std::cout << counter[i].icon;
			
			if ( counter[i].coordinates.Y<=1 )
			{
				counter[i].Active = false;
				
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