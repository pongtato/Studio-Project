#ifndef _SPAWNENEMIES_H
#define _SPAWNENEMIES_H

#include "Framework\console.h"
#include <fstream>
#include <string>



struct ENEMY
{
	std::string name;
	char icon;
	COORD coordinates;
	int Active;
	int hp;
	int score;
	int number;
	int state;
	
};

void moveEnemies();
void moveEnemiesUp();
void moveEnemiesDown();
void loadfromtext();
void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, int Active,int hp, int score,int number, int state);
void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY);



#endif // _SPAWNENEMIES_H

