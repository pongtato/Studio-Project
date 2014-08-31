#ifndef _SHOOT_H
#define _SHOOT_H

#include "Framework\console.h"
#include "SpawnEnemies.h"
#include "Player.h"




struct BULLET
{
	COORD corrdinates;
	char icon;
	bool Active;
	int number;
};

void renderMissile();		// renders missiles in the game
void shootMissile1(unsigned int &currentMissile, COORD charLocation);
void shootMissile1(unsigned int &currentMissile, int charLocationX, int charLocationY);
bool checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy,bool spawnpowerup);
void enemyShootBullet1(unsigned int &bulletCount, COORD enemyLocation);
void renderEnemyMissile();
bool checkPlayerDeath(COORD player, BULLET enemyBullet, ENEMY enemySpawn);
bool powerUpPlayerCollision(COORD player, BULLET powerPlayer);
bool shieldblock(COORD shield,BULLET enemyBullet);


#endif // _SHOOT_H