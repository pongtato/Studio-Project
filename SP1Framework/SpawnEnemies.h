#ifndef _SPAWNENEMIES_H
#define _SPAWNENEMIES_H

#include "Framework\console.h"
#include <string>


struct ENEMY
{
	std::string name;
	char icon;
	COORD coordinates;
	bool Active;
	int hp;
	int score;
	int number;
	int state;
	
};

void renderEnemies();
void moveEnemies();
void stateCheck();
void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, bool Active,int hp, int score,int number, int state);
void SpawnEnemy(unsigned int &currentEnemy);



#endif // _SPAWNENEMIES_H

