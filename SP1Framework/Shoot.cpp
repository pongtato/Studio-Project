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
				combined.stats.bulletsmissed++;
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
			combined.stats.shotshit++;
			//Enemy death
			if (checkEnemy.hp <= 0)
			{
				combined.stats.timer = 3;
				combined.stats.timeCD = true;
				combined.stats.combo++;
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
		if(((missile.corrdinates.X == checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y && checkEnemy.midrow != "")//Check directly infront 
			|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y-1 && checkEnemy.toprow != "")//Check above
			|| (missile.corrdinates.X ==  checkEnemy.coordinates.X && missile.corrdinates.Y == checkEnemy.coordinates.Y+1 && checkEnemy.botrow != ""))//CheckBelow
			&&(checkEnemy.Active && missile.Active))
		{
			missile.Active = false;
			checkEnemy.hp--;		
			missile.icon = ' ';
			combined.stats.shotshit++;
			//Enemy death
			if (checkEnemy.hp <= 0)
			{
				combined.stats.timer = 3;
				combined.stats.timeCD = true;
				combined.stats.combo++;
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
	enemyBullet[bulletCount].icon = '<';
	enemyBullet[bulletCount].corrdinates.X = enemyLocation.X--;
	enemyBullet[bulletCount].corrdinates.Y = enemyLocation.Y;
	enemyBullet[bulletCount].number = bulletCount;
	bulletCount++;
}
void renderEnemyMissile()
{
	for(int i = 0; i<combined.enemySettings.enemyMaxMissile;i++)
	{
		if(enemyBullet[i].Active)
		{
			enemyBullet[i].corrdinates.X--;
			writeToBuffer(enemyBullet[i].corrdinates,enemyBullet[i].icon);

		}
		//Check if out of bound
		if(enemyBullet[i].corrdinates.X <= 1)
		{
			enemyBullet[i].Active = false;

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
bool shieldblock(SHIELD shield,BULLET enemyBullet)
{
	if((shield.coordinates.X == enemyBullet.corrdinates.X && shield.coordinates.Y == enemyBullet.corrdinates.Y) && (enemyBullet.Active && shield.Active))
	{
		return true;
	}
	else
	{
		return false;
	}
}
