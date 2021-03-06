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
#include "Framework\sound.h"
#include "MainMenu.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <conio.h> 
#include "score.h"

// Console size, width by height
COORD ConsoleSize = {80, 25};
Sound sound;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

string display[5] = {"Score:"};

StopWatch b_timer; 
COORD charLocation;
COORD consoleSize;

void playGameSound(SoundType snd)
{
	switch (snd)
	{
	case S_HIT: sound.playSound("hit1");    
		break;
	case S_SHOOT1: sound.playSound("shoot1");
		break;
	case S_SHOOT2: sound.playSound("shoot2");
		break;
	case S_SHOOT3: sound.playSound("shoot3");
		break;
	case S_POWERUP: sound.playSound("powerup");
		break;
	case S_SELECT: sound.playSound("select");
		break;
	case S_HURT: sound.playSound("hurt");
		break;
	case S_MUSIC: sound.playSound("music");
		break;
	}
}

void init()
{
	
    // Set precision for floating point output
    initConsole(ConsoleSize, "SP1 Framework");

    // set the character to be in the center of the screen.
	charLocation.X = 3;
    charLocation.Y = ConsoleSize.Y/2;
	


    elapsedTime = 0.0;
	combined.enemySettings.droppowerup = true;
	GameVariables();
	initshieldVar();
	levelCheck();

	//Load sounds into .exe
	//Sound effects from Online Website provided by Mr Sim
	sound.loadWave("hit1", "Sounds/Hit1.wav");
	sound.loadWave("shoot1", "Sounds/Shoot1.wav");
	sound.loadWave("shoot2", "Sounds/Shoot2.wav");
	sound.loadWave("shoot3", "Sounds/Shoot3.wav");
	sound.loadWave("powerup", "Sounds/Powerup.wav");
	sound.loadWave("select", "Sounds/Select.wav");
	sound.loadWave("hurt", "Sounds/Hurt.wav");

	//Royalty Free Music from TeknoAXE
	//https://www.youtube.com/watch?v=UwEPn5LZlDY
	sound.loadWave("music", "Sounds/Music.wav");
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
	keyPressed[K_B] = isKeyPressed(VK_B);
}
void update(double dt)
{
		// get the delta time
		elapsedTime += dt;
		deltaTime = dt;

		// update game
		updateGame();
		static double timer_movement = elapsedTime;
		if( elapsedTime-timer_movement > 0.1)
		{
			timer_movement = elapsedTime;
			// Updating the location of the character based on the key press
			if (keyPressed[K_UP] && charLocation.Y > 3)
			{
				charLocation.Y--; 
			}
			if (keyPressed[K_LEFT] && charLocation.X > 3)
			{
				charLocation.X--; 
			}
			if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 4)
			{
				charLocation.Y++; 
			}
			if (keyPressed[K_RIGHT] && charLocation.X <46)
			{
				charLocation.X++; 
			}
		}
		if(keyPressed[K_SPACE] && combined.globalSettings.currentMissile <combined.globalSettings.maxMissile-4)
		{
			playerShoot();
		}
		if(keyPressed[K_SPACE] && combined.globalSettings.currentMissile>=combined.globalSettings.maxMissile-4)
		{
			combined.globalSettings.currentMissile = 0;
			playerShoot();
		}
		if (keyPressed[K_ESCAPE])
		{
			playGameSound(S_SELECT);
			pausescreen();   
		}
		if (keyPressed[K_B])
		{
			useSpecial();
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
	writeToBuffer(50,3,display[0],0x03);
	normalscore();
	writeToBuffer(50,4,display[1],0x03);
	PrintWave();
	PrintStage();
	PrintSpecial();
	PrintStats();
	printLives();
	printHearts();

    // render character
	renderCharacter();
	// render missile
	renderMissile();
	// render enemies
	renderEnemies();
	//render enemy bullet
	renderEnemyMissile();
	// render powerup
	renderPowerUp();
	// randomly generate terrain
	renderTerrain();
	//render shields
	renderShield();
	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
void restartGame()
{
	charLocation.X = 3;
    charLocation.Y = ConsoleSize.Y/2;
	
	combined.enemySettings.droppowerup = true;
	
	
	restartBullet();
	restartEnemies();
	restartStats();
}
