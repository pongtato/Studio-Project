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
void shootMissile2(unsigned int &currentMissile, COORD charLocation);
bool checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy,bool spawnpowerup);
bool BosscheckCollisionBullet(BULLET &missile, BOSS &checkEnemy);
void enemyShootBullet1(unsigned int &bulletCount, COORD enemyLocation);
void enemyShootBullet2(unsigned int &bulletCount, COORD enemyLocation);
void renderEnemyMissile();
bool checkPlayerDeath(COORD player, BULLET enemyBullet, ENEMY enemySpawn);

bool powerUpPlayerCollision(COORD player, BULLET powerPlayer);

#endif // _SHOOT_H