#include "MainMenu.h"
#include "game.h"
#include "Shoot.h"
#include "SpawnEnemies.h"
#include "Player.h"
#include "leveldesign.h"
#include "Framework\console.h"
#include "MainMenu.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h> 
#include "score.h"
#include "common.h"

extern BULLET powerUp;
extern PLAYER player;
extern int PowerupIcon;
extern int spawnno;
GLOBAL combined;
extern COORD charLocation;
extern double elapsedTime;


void GameVariables()
{
	powerUp.icon = PowerupIcon;
	powerUp.Active = false;
	std::ifstream indata;
	indata.open("GLD/Variables/GameSettings.txt");
	if ( indata.is_open())
	{				//modifyY & X - spawning points X&Y 
					//modifyYDOWN - movement cap					
					//upordown - which direction? 
					//wew - move left				
					//spawncounter - spawn per row 
					//spawnclear - move on to next spawn
		if (indata >> combined.enemySettings.modifyY >> combined.enemySettings.modifyX >> combined.enemySettings.moveYUP >> combined.enemySettings.moveYDOWN >> combined.enemySettings.upordown >> combined.globalSettings.globalscore>> combined.enemySettings.moveState >> combined.enemySettings.wew>> combined.enemySettings.enemieskilled>> combined.enemySettings.spawncounter>> combined.enemySettings.spawnclear >>combined.globalSettings.loadlevel>> combined.enemySettings.enemymovespeed >> combined.enemySettings.enemyshootspeedrange1 >> combined.enemySettings.enemyshootspeedrange2>> combined.enemySettings.bossmovespeed>> combined.enemySettings.bossshootspeed>>combined.terrainSettings.terrainModX>>combined.terrainSettings.terrainModY>> combined.terrainSettings.terrainBotModY>> combined.terrainSettings.terrainicon>> combined.enemySettings.enemyMaxMissile >> combined.globalSettings.maxMissile >> combined.globalSettings.playingField )
		{
		}
	}
}
// FUNCTIONS COMBINED
void updateGame()
{
		loadfromtext(combined.globalSettings.loadlevel);
		enemySpawn();
		enemyMove();
		enemyShooting();

	FormTerrain();
	FormTerrainBot();
	terrainMove();
	collision();
	stageclear();
}
// IS STAGE CLEAR?
void stageclear()
{
		//if stage is clear, proceed
	if (combined.enemySettings.enemieskilled >= spawnno)
	{
		combined.globalSettings.loadlevel++;
		combined.enemySettings.currentEnemy =0;
		combined.enemySettings.enemieskilled =0;
		combined.enemySettings.modifyX = 38;
		combined.enemySettings.modifyY = 6;
		combined.enemySettings.moveYUP = combined.enemySettings.modifyY;
		combined.enemySettings.moveYDOWN = 0;
		combined.enemySettings.wew = 1;
		combined.enemySettings.spawnclear = 1;
		levelCheck();
		player.Special++;
	}
}

void playerShoot()
{
	static double timer_player = elapsedTime;
	if ( elapsedTime - timer_player > 0.5)
	{
		timer_player = elapsedTime;
		if(player.PowerUp >= 3)
		{
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X+2,charLocation.Y);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
		}
		else if(player.PowerUp == 2)
		{
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
		}
		else  if(player.PowerUp == 1)
		{
			shootMissile1(combined.globalSettings.currentMissile,charLocation);
		}
	}
}

