#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>


ENEMY counter[999];
int enemycounter;

void moveEnemies()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X--,counter[i].coordinates.Y);
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


