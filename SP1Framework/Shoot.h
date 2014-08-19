#ifndef _SHOOT_H
#define _SHOOT_H

#include "Framework\console.h"

#include "SpawnEnemies.h"

extern ENEMY counter[26];

struct BULLET
{
	COORD corrdinates;
	char icon;
	bool Active;
	int number;
};

void renderMissile();		// renders missiles in the game
void shootMissile1(unsigned int &currentMissile, COORD charLocation);
void shootMissile2(unsigned int &currentMissile, COORD charLocation);
void checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy);



#endif // _SHOOT_H