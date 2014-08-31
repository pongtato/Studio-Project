#ifndef _COMMON_H
#define _COMMON_H

#include "Framework\timer.h"
#include <fstream>
#include <string>

#define TERRAIN 999
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
struct GLOBAL
{
	EnemySettings enemySettings;
	TerrainSettings terrainSettings;
	GeneralSettings globalSettings;
}; 


#endif // _COMMON_H