#ifndef _COMMON_H
#define _COMMON_H

#include "Framework\timer.h"
#include <fstream>
#include <string>

#define VK_B 0x42

struct EnemySettings
{
	int modifyY;
	int modifyX;
	int moveYUP;
	int moveYDOWN;
	int upordown;
	int moveState;
	int wew;
	int enemieskilled;
	int spawncounter;
	int spawnclear;
	int enemyshootspeedrange1;
	int enemyshootspeedrange2;
	int enemycount;
	double enemymovespeed;
	double bossmovespeed;
	double bossshootspeed;
	unsigned int currentEnemy;
	unsigned int enemyCurrentMissile;
	unsigned int enemyMaxMissile;
	unsigned int powerupEnemy;
	std::string stagechecker[256];
	std::string bosschecker[256];
	std::string spawnlevel;
	int lvltospawn;
	bool droppowerup;
};
struct TerrainSettings
{
	int terrainModX;
	int terrainModY;
	int terrainBotModY;
	int terrainlevel;
	int terrainicon;
	int terraingo;
	int terraingobot;
	int terraindestory;
	int terraindestorybot;
	bool terrain;
	unsigned int currentTerrain;
	unsigned int currentTerrainBot;
};
struct GeneralSettings
{
	int globalscore;
	int loadlevel;
	int bonus;
	int boss;
	int stage;
	int lvl;
	unsigned int currentMissile;
	unsigned int currentShield;
	unsigned int shieldSize;
	unsigned int maxMissile;
	unsigned int playingField;
	bool nextstage;
};
struct StatTrak
{
	double bulletsfired;
	double shotshit;
	double bulletsmissed;
	double accuracy;
	int combo;
	double timer;
	bool timeCD;
};
struct GLOBAL
{
	EnemySettings enemySettings;
	TerrainSettings terrainSettings;
	GeneralSettings globalSettings;
	StatTrak stats;
}; 

void PrintStats();
void comboBreaker();
void restartBullet();
void restartEnemies();
void restartStats();

#endif // _COMMON_H