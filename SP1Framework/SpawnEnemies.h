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
	
};

void renderEnemies();
void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, bool Active,int hp, int score);



#endif // _SPAWNENEMIES_H

