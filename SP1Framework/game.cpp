// This is the main file for the game logic and function
//
//
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

// Console size, width by height
COORD ConsoleSize = {80, 25};

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

extern BULLET powerUp;
extern PLAYER player;
extern int PowerupIcon;
extern int spawnno;
GLOBAL combined;

string display[5] = {"Score:"};

StopWatch b_timer; 
COORD charLocation;
COORD consoleSize;

void init()
{
    // Set precision for floating point output
    initConsole(ConsoleSize, "SP1 Framework");

    // set the character to be in the center of the screen.
	charLocation.X = 3;
    charLocation.Y = ConsoleSize.Y/2;
	


    elapsedTime = 0.0;

	loadPlayerFromText();
	powerUp.icon = PowerupIcon;
	powerUp.Active = false;
	combined.enemySettings.droppowerup = true;
	GameVariables();
	levelCheck();
}
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    shutDownConsole();
}
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_P] = isKeyPressed(0x50);
}
void update(double dt)
{
		// get the delta time
		elapsedTime += dt;
		deltaTime = dt;

		// update game
		updateGame();

		// Updating the location of the character based on the key press
		if (keyPressed[K_UP] && charLocation.Y > 3)
		{
			Beep(0, 0);
			charLocation.Y--; 
		}
		if (keyPressed[K_LEFT] && charLocation.X > 3)
		{
			Beep(0, 0);
			charLocation.X--; 
		}
		if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 4)
		{
			Beep(0, 0);
			charLocation.Y++; 
		}
		if (keyPressed[K_RIGHT] && charLocation.X <46)
		{
			Beep(0, 0);
			charLocation.X++; 
		}
		static double timer_player = elapsedTime;

		if(keyPressed[K_SPACE] && combined.globalSettings.currentMissile <combined.globalSettings.maxMissile-4)// && !missleFired1)
		{
			
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
				//missleFired1 = true;
			}
		}
		if(keyPressed[K_SPACE] && combined.globalSettings.currentMissile>=combined.globalSettings.maxMissile-4)// && !missleFired1)
		{
			if ( elapsedTime - timer_player > 0.5)
			{
				timer_player = elapsedTime;
				if(player.PowerUp >= 3)
				{
					combined.globalSettings.currentMissile=0;
					shootMissile2(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(combined.globalSettings.currentMissile,charLocation.X+2,charLocation.Y);
					shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
				}
				else if(player.PowerUp == 2)
				{
					combined.globalSettings.currentMissile=0;
					shootMissile2(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(combined.globalSettings.currentMissile,charLocation.X,charLocation.Y-1);
				}
				else  if(player.PowerUp == 1)
				{
					combined.globalSettings.currentMissile=0;
					shootMissile2(combined.globalSettings.currentMissile,charLocation);
				}
			}
		}
		// goes to menu 2 if player hits the escape key ( a way of pause )
		if (keyPressed[K_ESCAPE])
		{
			menuscreen();   
		}
		
		if (keyPressed[K_P])
		{
			clearBuffer(0x0F);
			pauseScreen();
			flushBufferToConsole();
			char c = '0';
			c = getch();
		}

}
void render()
{
    // Clears the buffer with this colour attribute
    clearBuffer(0x0F);
	
	
	
	leveldesign();
	Writetohighscore();

    // render time taken to calculate this frame
  /*  gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;*/

	/*gotoXY(50, 3);
    colour(0x03);
    std::cout << "Score:" << globalscore << std::endl;*/
	writeToBuffer(50,3,display[0],0x03);
	normalscore();

	/*gotoXY(50, 4);
    colour(0x03);
    std::cout << "Wave:" << loadlevel << std::endl;*/
	writeToBuffer(50,4,display[1],0x03);
	PrintWave();
	PrintStage();
    // render character
	renderCharacter();
	// render missiles
	 //colour(0x0B);
	renderMissile();
	// render enemies
	renderEnemies();
	//render boss
	//renderBoss();
	//render enemy bullet
	renderEnemyMissile();
	// render powerup
	renderPowerUp();
	// randomly generate terrain
	renderTerrain();

	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
void GameVariables()
{
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
	}
}
