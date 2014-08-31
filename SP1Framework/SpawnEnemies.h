#ifndef _SPAWNENEMIES_H
#define _SPAWNENEMIES_H

#include "Framework\console.h"
#include <fstream>
#include <string>



struct ENEMY
{
	std::string name;
	std::string toprow;
	std::string midrow;
	std::string botrow;
	char icon;
	COORD coordinates;
	int Active;
	int hp;
	int score;
	int number;
	int state;
};
struct WORLD
{
	char icon;
	int level;
	COORD coordinates;
	int Active;
};

void moveBoss();
void moveBossUp();
void moveBossDown();



void moveEnemies();
void moveEnemiesUp();
void moveEnemiesDown();
void loadfromtext(int loadcase);
void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, int Active,int hp, int score,int number, int state);
void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY);
void SpawnTerrain(unsigned int &currentTerrain, int terrainModX, int terrainModY, int terrainChar);
void moveTerrain();
void SpawnTerrainBot(unsigned int &currentTerrainBot, int terrainModX, int terrainBotModY, int terrainChar);
void moveTerrainBot();
void enemySpawn();
void renderEnemies();
void enemyMove();
void enemyShooting();
void FormTerrain();
void FormTerrainBot();
void renderTerrain();
void terrainMove();
void levelCheck();
void PrintWave();
void PrintStage();
void bossPattern();






#endif // _SPAWNENEMIES_H

