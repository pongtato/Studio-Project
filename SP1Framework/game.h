#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <fstream>
#include <string>

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
    K_COUNT,
	K_B
};


void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void mainLoop();
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void renderCharacter();		// renders player character
void renderEnemies();		// reneder enemies
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
void restartGame();


#endif // _GAME_H