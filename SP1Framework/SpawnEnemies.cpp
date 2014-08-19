#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>

ENEMY counter[26];
ENEMY Wew;

void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, bool Active, int hp, int score,int number)
{

	enemy.name = name;
	enemy.icon = icon;
	enemy.coordinates.X = coordinates.X;
	enemy.coordinates.Y = coordinates.Y;
	enemy.Active = Active;
	enemy.hp = hp;
	enemy.score = score;
	enemy.number = number;
}

void renderEnemies()
{
	for ( int i = 0; i<10; ++i)
	{

		if ( i%2 == 0)
		{
			std::cout << " ";
		}
		else
		{
			for ( int j = 0; j<12; ++j)
			{
				if ( j%2==0)
				{
					std::cout << " ";
				}
				else 
				{
					COORD coord;
					coord.X = 30 + i;
					coord.Y = 5 + j;
					EnemySpawn(Wew,"PongPong",(char)5,coord,true,1,10,i + j-1);
					gotoXY(Wew.coordinates.X,Wew.coordinates.Y);
					std::cout << Wew.icon;
				}
			}
		}
	}
}

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
				gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
				std::cout << counter[i].icon;
			}
		}
	}
}

void stateCheck()
{

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