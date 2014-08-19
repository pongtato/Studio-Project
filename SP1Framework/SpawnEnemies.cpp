#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>



void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, bool Active, int hp, int score)
{

	enemy.name = name;
	enemy.icon = icon;
	enemy.coordinates.X = coordinates.X;
	enemy.coordinates.Y = coordinates.Y;
	enemy.Active = Active;
	enemy.hp = hp;
	enemy.score = score;
}

void renderEnemies()
{
	for ( int i = 1; i<10; ++i)
	{

		if ( i%2 == 0)
		{
			std::cout << " ";
		}
		else
		{
			for ( int j = 1; j<12; ++j)
			{
				if ( j%2==0)
				{
					std::cout << " ";
				}
				else 
				{
					ENEMY Wew;
					COORD coord;
					coord.X = 30 + i;
					coord.Y = 5 + j;
					EnemySpawn(Wew,"PongPong",(char)5,coord,true,1,10);
					gotoXY((Wew.coordinates.X),Wew.coordinates.Y);
					std::cout << Wew.icon;
				}
			}
		}
	}
}