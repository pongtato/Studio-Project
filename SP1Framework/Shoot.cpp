#include "Shoot.h"
#include "game.h"
#include <iostream>

extern PLAYER player;
extern double elapseTime;
BULLET powerUp;
BULLET missile[50];
BULLET enemyBullet[50];

void shootMissile1(unsigned int &currentMissile, COORD charLocation)
{
		missile[currentMissile].Active = true;
		missile[currentMissile].icon = player.playerMissleIcon;
		missile[currentMissile].corrdinates.X = charLocation.X+1;
		missile[currentMissile].corrdinates.Y = charLocation.Y;
		missile[currentMissile].number = currentMissile;
		currentMissile++;
}
void shootMissile2(unsigned int &currentMissile, COORD charLocation)
{
	currentMissile=0;
	missile[currentMissile].Active = true;
	missile[currentMissile].icon = player.playerMissleIcon;
	missile[currentMissile].corrdinates.X = charLocation.X+1;
	missile[currentMissile].corrdinates.Y = charLocation.Y;
	missile[currentMissile].number = currentMissile;
}
void renderMissile()
{
	for(int i = 0; i<50;i++)
	{

		if(missile[i].Active)
		{
			gotoXY(missile[i].corrdinates.X++,missile[i].corrdinates.Y);
			std::cout << missile[i].icon << std::endl;

			//Check if out of bound
			if(missile[i].corrdinates.X > 47)
			{
				missile[i].Active = false;
			}
		}
	}

}
bool checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy)
{

	if(((missile.corrdinates.X+1 == checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y)//Check directly infront 
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y))//Check above
		&&(checkEnemy.Active && missile.Active))//Check below
	{
		missile.Active = false;
		checkEnemy.hp--;		
		missile.icon = ' ';
		//Enemy death
		if (checkEnemy.hp <= 0)
		{
			checkEnemy.Active = false;
			checkEnemy.icon = ' ';

			//Chance to spawn powerup at enemy death
			if(rand()%2 == 1)
			{
				powerUp.Active = true;
				powerUp.corrdinates = checkEnemy.coordinates;
			}
		}
		
		//increase score

		return true;
	}
	else
	{
		return false;
	}
}
bool BosscheckCollisionBullet(BULLET &missile, BOSS &checkEnemy)
{

	if(((missile.corrdinates.X+1 == checkEnemy.coordinates.X-1 && missile.corrdinates.Y == checkEnemy.coordinates.Y)//Check directly infront 
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X-1 && missile.corrdinates.Y == checkEnemy.coordinates.Y)
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X+1 && missile.corrdinates.Y == checkEnemy.coordinates.Y)//Check above
		|| (missile.corrdinates.X ==  checkEnemy.coordinates.X-1 && missile.corrdinates.Y == checkEnemy.coordinates.Y-1))//Check above
		&&(checkEnemy.Active && missile.Active))//Check below
	{
		missile.Active = false;
		checkEnemy.hp--;		
		missile.icon = ' ';
		if (checkEnemy.hp <= 0)
		{
			checkEnemy.Active = false;
			checkEnemy.iconbottomleft = ' ';
			checkEnemy.iconbottomright = ' ';
			checkEnemy.iconcenter = ' ';
			checkEnemy.iconup = ' ';
			checkEnemy.icondown = ' ';
			checkEnemy.iconbottomleft = ' ';
			checkEnemy.iconbottomright = ' ';
		}
		
		//increase score

		return true;
	}
	else
	{
		return false;
	}
}
void enemyShootBullet1(unsigned int &bulletCount, COORD enemyLocation)
{
	enemyBullet[bulletCount].Active = true;
	enemyBullet[bulletCount].icon = '~';
	enemyBullet[bulletCount].corrdinates.X = enemyLocation.X--;
	enemyBullet[bulletCount].corrdinates.Y = enemyLocation.Y;
	enemyBullet[bulletCount].number = bulletCount;
	bulletCount++;
}
void enemyShootBullet2(unsigned int &bulletCount, COORD enemyLocation)
{
	bulletCount=0;
	enemyBullet[bulletCount].Active = true;
	enemyBullet[bulletCount].icon = '~';
	enemyBullet[bulletCount].corrdinates.X = enemyLocation.X--;
	enemyBullet[bulletCount].corrdinates.Y = enemyLocation.Y;
	enemyBullet[bulletCount].number = bulletCount;
	
}
void renderEnemyMissile()
{
	for(int i = 0; i<50;i++)
	{

		if(enemyBullet[i].Active)
		{
			gotoXY(enemyBullet[i].corrdinates.X-=2,enemyBullet[i].corrdinates.Y);
			std::cout << enemyBullet[i].icon << std::endl;

			//Check if out of bound
			if(enemyBullet[i].corrdinates.X <= 1)
			{
				enemyBullet[i].Active = false;
			}
		}
	}

}
bool checkPlayerDeath(COORD player, BULLET enemyBullet, ENEMY enemySpawn)
{
	if((player.X == enemyBullet.corrdinates.X && player.Y == enemyBullet.corrdinates.Y)
		|| player.X  == enemyBullet.corrdinates.X+1 && player.Y == enemyBullet.corrdinates.Y)
	{
		return true;
	}
	if((player.X == enemySpawn.coordinates.X && player.Y == enemySpawn.coordinates.Y)
		|| player.X  == enemySpawn.coordinates.X+1 && player.Y == enemySpawn.coordinates.Y)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool powerUpPlayerCollision(PLAYER &player, BULLET powerPlayer)
{
	if((player.coordinates.X == powerUp.corrdinates.X && player.coordinates.Y == powerUp.corrdinates.Y)&& powerUp.Active)//Check below
	{
		powerUp.Active = false;
		player.PowerUp++;
		return true;
	}
	else
	{
		return false;
	}
}