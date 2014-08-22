#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include <fstream>
#include <string>

#define NO_OF_ENEMIES 25
#define BOSS_NO 1
#define Bonus 25

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


void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void renderCharacter();		// renders player character
void renderEnemies();
void renderBoss();
void leveldesign();
void updateGame();
void enemyMove();
void bossMove();
void enemySpawn();
void SpecialSpawn();
void bossSpawn();
void bonusSpawn();
void enemyShooting();
void bossShooting();
void stageclear();
void collision();
void enemycolour();
void renderPowerUp();


#endif // _GAME_H