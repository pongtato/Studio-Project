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
extern BULLET missile[60];
extern SHIELD shield[3];
extern ENEMY counter[999];
extern BULLET enemyBullet[50];
extern WORLD generator[999];
extern WORLD generator2[999];
extern PLAYER player;
extern int PowerupIcon;
extern unsigned int spawnno;
GLOBAL combined;
extern COORD charLocation;
extern double elapsedTime;



void GameVariables()
{
	combined.stats.accuracy = 100;
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
	comboBreaker();
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
		stageclearscreen();
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
			playGameSound(S_SHOOT3);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X+2,charLocation.Y);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
			combined.stats.bulletsfired+=3;
		}
		else if(player.PowerUp == 2)
		{
			playGameSound(S_SHOOT2);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
			shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
			combined.stats.bulletsfired+=2;
		}
		else  if(player.PowerUp == 1)
		{
			playGameSound(S_SHOOT1);
			shootMissile1(combined.globalSettings.currentMissile,charLocation);
			combined.stats.bulletsfired++;
		}
	}
}
//PRINT STATS
void PrintStats()
{
	std::stringstream temp;
	temp << "SHOTS FIRED: ";
	std::string result = temp.str();
	writeToBuffer(50, 7, result, 0x0F);
	std::stringstream temp4;
	temp4 << combined.stats.bulletsfired;
	std::string result4 = temp4.str();
	writeToBuffer(62, 7, result4, 0x0C);
	std::stringstream temp2;
	temp2 << "SHOTS MISSED: ";
	std::string result2 = temp2.str();
	writeToBuffer(50, 8, result2, 0x0F);
	std::stringstream temp3;
	temp3 << combined.stats.bulletsmissed;
	std::string result3 = temp3.str();
	writeToBuffer(63, 8, result3, 0x0C);

	if ( combined.stats.bulletsfired != 0 && combined.stats.bulletsmissed !=0)
	{
		combined.stats.accuracy = ((combined.stats.shotshit/(combined.stats.shotshit+combined.stats.bulletsmissed)) * 100);
	}
	std::stringstream temp5;
	temp5 << "ACCURACY: ";
	std::string result5 = temp5.str();
	writeToBuffer(50, 9, result5, 0x0F);

	std::stringstream temp6;
	temp6 << combined.stats.accuracy << "%";
	std::string result6 = temp6.str();
	writeToBuffer(59, 9, result6, 0x0C);

	std::stringstream combo1;
	combo1 << "COMBO: ";
	std::string resultcombo = combo1.str();
	writeToBuffer(50, 11, resultcombo, 0x0F);

	std::stringstream combo2;
	combo2 << combined.stats.combo;
	std::string resultcombo2 = combo2.str();
	writeToBuffer(56, 11, resultcombo2, 0x0C);

	std::stringstream wew;
	wew << char(219) << " ";
	std::string tests = wew.str();
	writeToBuffer(50, 12, tests, 0x08);

	std::stringstream testing;
	testing << char(219) << " "<< char(219) << " "<< char(219);
	std::string test = testing.str();
	writeToBuffer(52, 12, test, 0x0F);

	if ( combined.stats.timer == 1 )
	{
	std::stringstream combotimer;
	 combotimer << char(219);
	std::string  combotimertest =  combotimer.str();
	writeToBuffer(52, 12, combotimertest, 0x0C);
	}
	else if ( combined.stats.timer == 2 )
	{
	std::stringstream combotimer;
	combotimer << char(219);
	std::string  combotimertest =  combotimer.str();
	writeToBuffer(54, 12, combotimertest, 0x0C);
	}
	else if ( combined.stats.timer == 3 )
	{
	std::stringstream combotimer;
	 combotimer << char(219);
	std::string  combotimertest =  combotimer.str();
	writeToBuffer(56, 12, combotimertest, 0x0C);
	}
}

void comboBreaker()
{
	if ( combined.stats.timeCD == true )
	{
	static double timer_combo = elapsedTime;
		if ( elapsedTime - timer_combo > 1)
		{
			timer_combo = elapsedTime;
			combined.stats.timer--;
			if ( combined.stats.timer == 0)
			{
			combined.stats.combo = 1;
			combined.stats.timeCD = false;
			}
		}
	}
}

void restartBullet()
{
	for(unsigned int i = 0; i< combined.enemySettings.enemyMaxMissile;i++)
	{
		enemyBullet[i].Active = false;
		
	}
	for(unsigned int i = 0; i<combined.globalSettings.maxMissile;i++)
	{
		missile[i].Active = false;
	}
}

void restartEnemies()
{
	for(int i = 0; i< 999; i++)
	{
		counter[i].Active = false;
		generator[i].Active = false;
		generator2[i].Active = false;
	}
	combined.enemySettings.currentEnemy =0;
	combined.enemySettings.enemieskilled =0;
	combined.enemySettings.modifyX = 38;
	combined.enemySettings.modifyY = 6;
	combined.enemySettings.moveYUP = combined.enemySettings.modifyY;
	combined.enemySettings.moveYDOWN = 0;
	combined.enemySettings.wew = 1;
	combined.enemySettings.spawnclear = 1;
	combined.globalSettings.loadlevel =1;
	levelCheck();
}
void restartStats()
{
	
	combined.stats.bulletsfired = 0;
	combined.stats.bulletsmissed = 0;
	combined.stats.combo = 0;
	combined.stats.accuracy = 100;
	powerUp.Active = false;
	player.Invul = 0;
	for(int i = 0; i<3;i++)
	{
		shield[i].Active = false;
	}
}