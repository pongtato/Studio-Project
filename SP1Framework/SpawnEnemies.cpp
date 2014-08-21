#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>



ENEMY counter[999];
int enemycounter;
int activefromtext;
int hpfromtext;
int scorefromtext;
int iconfromtext;
int statefromtext;

void loadfromtext()
{
	std::ifstream indata;
	indata.open("GLD/Variables/boss1.txt");
	if ( indata.is_open())
	{
		if (indata >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext)
		{

		}
	}
}

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

void moveEnemiesUp()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);
		}
	}
}

void moveEnemiesDown()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
		}
	}
}


void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY)
{
	enemycounter = 10;
	counter[currentEnemy].Active = activefromtext;
	counter[currentEnemy].coordinates.X = modX;
	counter[currentEnemy].coordinates.Y = modY;
	counter[currentEnemy].hp= hpfromtext;
	counter[currentEnemy].score= scorefromtext;
	counter[currentEnemy].icon= (char)(iconfromtext);
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = statefromtext;
	currentEnemy++;
}






