#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <fstream>
#include <string>

#define NO_OF_ENEMIES 25
#define BOSS_NO 1
#define BONUS 25
#define TERRAIN 999

extern StopWatch g_timer;
extern bool g_quitGame;


enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
	K_P,
    K_COUNT
};

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
	std::string spawnlevel;
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

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void mainLoop();
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void renderCharacter();		// renders player character
void renderEnemies();		// reneder enemies
//void renderBoss();			// render boss
void leveldesign();			// load game frame
void updateGame();			// all the functions in this functions
void enemyMove();			// move enemies
void bossMove();			// moves boss
void enemySpawn();			// enemy spawn
void bossSpawn();			// spawns boss
void bonusSpawn();			// spawbs bonus
void enemyShooting();		// enemy shooting
void bossShooting();		// boss shooting
void stageclear();			// is stage cleared?
void collision();			// collision duh
void renderPowerUp();		// renders power up drop
void GameVariables();		// settings of the game taken from text file
void FormTerrain();			//load terrain data
void renderTerrain();
void terrainMove(); 
void FormTerrainBot();


#endif // _GAME_H