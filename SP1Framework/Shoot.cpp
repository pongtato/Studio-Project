#include "Shoot.h"
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include "common.h"
#include <fstream>
#include <iostream>

extern PLAYER player;
extern double elapsedTime;
BULLET powerUp;
BULLET missile[60];
BULLET enemyBullet[50];
extern GLOBAL combined;
extern std::string typefromtext;
extern SHIELD shield[3];
extern std::string tpatternfromtext;
extern std::string mpatternfromtext;
extern std::string bpatternfromtext;


void shootMissile1(unsigned int &currentMissile, COORD charLocation)
{
		missile[currentMissile].Active = true;
		missile[currentMissile].icon = player.playerMissleIcon;
		missile[currentMissile].corrdinates.X = charLocation.X++;
		missile[currentMissile].corrdinates.Y = charLocation.Y;
		missile[currentMissile].number = currentMissile;
		currentMissile++;
}
void shootMissile1(unsigned int &currentMissile, int charLocationX, int charLocationY)
{
		missile[currentMissile].Active = true;
		missile[currentMissile].icon = player.playerMissleIcon;
		missile[currentMissile].corrdinates.X = charLocationX++;
		missile[currentMissile].corrdinates.Y = charLocationY;
		missile[currentMissile].number = currentMissile;
		currentMissile++;
}
void shootMissile2(unsigned int &currentMissile, COORD charLocation)
{
	missile[currentMissile].Active = true;
	missile[currentMissile].icon = player.playerMissleIcon;
	missile[currentMissile].corrdinates.X = charLocation.X+1;
	missile[currentMissile].corrdinates.Y = charLocation.Y;
	missile[currentMissile].number = currentMissile;
	currentMissile++;
}
void shootMissile2(unsigned int &currentMissile,  int charLocationX, int charLocationY)
{
	
	missile[currentMissile].Active = true;
	missile[currentMissile].icon = player.playerMissleIcon;
	missile[currentMissile].corrdinates.X = charLocationX+1;
	missile[currentMissile].corrdinates.Y = charLocationY;
	missile[currentMissile].number = currentMissile;
	currentMissile++;
}
void renderMissile()
{
	for(int i = 0; i<combined.globalSettings.maxMissile;i++)
	{

		if(missile[i].Active)
		{
			/*gotoXY(missile[i].corrdinates.X++,missile[i].corrdinates.Y);
			std::cout << missile[i].icon << std::endl;*/
			missile[i].corrdinates.X++;
			writeToBuffer(missile[i].corrdinates,missile[i].icon,0x0B);
			//Check if out of bound
			if(missile[i].corrdinates.X >46)
			{
				missile[i].Active = false;
			}
		}
	}

}
bool checkCollisionBullet(BULLET &missile, ENEMY &checkEnemy, bool spawnpowerup)
{
	if( typefromtext != "BOSS")
	{
		if(((missile.corrdinates.X+1 == checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y)//Check directly infront 
			|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y))//Check above
			&&(checkEnemy.Active && missile.Active))
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
				if(rand()%2 == 1 && spawnpowerup == true)
				{
					powerUp.Active = true;
					powerUp.corrdinates.X = checkEnemy.coordinates.X;
					powerUp.corrdinates.Y = checkEnemy.coordinates.Y;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(((missile.corrdinates.X == checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y && tpatternfromtext != "")//Check directly infront 
			|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y-1 && mpatternfromtext != "")//Check above
			|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y+1 && bpatternfromtext != ""))//CheckBelow
			&&(checkEnemy.Active && missile.Active))
		{
			missile.Active = false;
			checkEnemy.hp--;		
			missile.icon = ' ';
			//Enemy death
			if (checkEnemy.hp <= 0)
			{
				checkEnemy.Active = false;
				checkEnemy.midrow = ' ';
				checkEnemy.toprow = ' ';
				checkEnemy.botrow = ' ';
			}
			return true;
		}
		else
		{
			return false;
		}
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
	
	static double timer_enemyBullet = elapsedTime;
	static double timer_enemyBullet2 = elapsedTime;
	static double timer_enemyBullet3 = elapsedTime;
	static double timer_enemyBullet4 = elapsedTime;
	for(int i = 0; i<combined.enemySettings.enemyMaxMissile;i+=4)
	{

		if(enemyBullet[i].Active)
		{
			if( elapsedTime-timer_enemyBullet > 0.01)
			{
				
				timer_enemyBullet = elapsedTime;
				enemyBullet[i].corrdinates.X--;
			}
			writeToBuffer(enemyBullet[i].corrdinates,enemyBullet[i].icon);
			//Check if out of bound

			if(enemyBullet[i].corrdinates.X <= 1)
			{
				enemyBullet[i].Active = false;
			}
		}
	}
	for(int i = 1; i<combined.enemySettings.enemyMaxMissile;i+=4)
	{

		if(enemyBullet[i].Active)
		{
			if( elapsedTime-timer_enemyBullet2 > 0.01)
			{
				
				timer_enemyBullet2 = elapsedTime;
				enemyBullet[i].corrdinates.X--;
			}
			writeToBuffer(enemyBullet[i].corrdinates,enemyBullet[i].icon);
			//Check if out of bound

			if(enemyBullet[i].corrdinates.X <= 1)
			{
				enemyBullet[i].Active = false;
			}
		}
	}
	for(int i = 2; i<combined.enemySettings.enemyMaxMissile;i+=4)
	{

		if(enemyBullet[i].Active)
		{
			if( elapsedTime-timer_enemyBullet3 > 0.01)
			{
				
				timer_enemyBullet3 = elapsedTime;
				enemyBullet[i].corrdinates.X--;
			}
			writeToBuffer(enemyBullet[i].corrdinates,enemyBullet[i].icon);
			//Check if out of bound

			if(enemyBullet[i].corrdinates.X <= 1)
			{
				enemyBullet[i].Active = false;
			}
		}
	}
	for(int i = 3; i<combined.enemySettings.enemyMaxMissile;i+=4)
	{

		if(enemyBullet[i].Active)
		{
			if( elapsedTime-timer_enemyBullet4 > 0.01)
			{
				
				timer_enemyBullet4  = elapsedTime;
				enemyBullet[i].corrdinates.X--;
			}
			writeToBuffer(enemyBullet[i].corrdinates,enemyBullet[i].icon);
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
	if(((player.X == enemyBullet.corrdinates.X && player.Y == enemyBullet.corrdinates.Y)
		|| player.X  == enemyBullet.corrdinates.X+1 && player.Y == enemyBullet.corrdinates.Y)&& (enemyBullet.Active))
	{
		enemySpawn.Active = false;
		return true;
	}

	if(((player.X == enemySpawn.coordinates.X && player.Y == enemySpawn.coordinates.Y)
		|| player.X  == enemySpawn.coordinates.X+1 && player.Y == enemySpawn.coordinates.Y)&& (enemySpawn.Active))
	{
		enemyBullet.Active = false;
		return true;
	}
	else
	{
		return false;
	}
}
bool powerUpPlayerCollision(COORD player, BULLET powerPlayer)
{
	if((player.X == powerPlayer.corrdinates.X && player.Y == powerPlayer.corrdinates.Y)
		&&powerPlayer.Active)//Check below
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool shieldblock(COORD shield,BULLET enemyBullet)
{
	if(((shield.X == enemyBullet.corrdinates.X && shield.Y == enemyBullet.corrdinates.Y)
		|| shield.X == enemyBullet.corrdinates.X && shield.Y+1 == enemyBullet.corrdinates.Y 
		|| shield.X == enemyBullet.corrdinates.X && shield.Y+2 == enemyBullet.corrdinates.Y) && (enemyBullet.Active))
	{
		return true;
	}
	else
	{
		return false;
	}
}
