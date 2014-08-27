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

// Console size, width by height
COORD ConsoleSize = {80, 25};

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

extern BULLET powerUp;
extern PLAYER player;
extern int PowerupIcon;
GLOBAL combined;

string display[5] = {"Score:","Wave:"};

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
			colour(0x0F);
			cls();
			menuscreen2();   
		}
		if (keyPressed[K_P])
		{
			system("PAUSE");
		}


}
void render()
{
    // Clears the buffer with this colour attribute
    clearBuffer(0x0F);

    

	leveldesign();

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

	/*gotoXY(50, 4);
    colour(0x03);
    std::cout << "Wave:" << loadlevel << std::endl;*/
	writeToBuffer(50,4,display[1],0x03);

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

//// BOSS
//void renderBoss()
//{
//	//enemycolour();
//	// render boss
//	for ( int i = 0; i < BOSS_NO; ++i)
//	{
//		//is boss alive
//		if(Bcounter[i].Active)
//		{
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].icontopleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y-1,Bcounter[i].iconbottomleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].iconup;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y-1,Bcounter[i].iconup,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].icontopright;*/
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y-1,Bcounter[i].icontopright,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y,Bcounter[i].iconleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconcenter;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y,Bcounter[i].iconcenter,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconright;*/
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y,Bcounter[i].iconright,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y+1);
//			std::cout << Bcounter[i].iconbottomleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y+1,Bcounter[i].iconbottomleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y+1);
//			std::cout << Bcounter[i].icondown;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y+1,Bcounter[i].icondown,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y+1); 
//			std::cout << Bcounter[i].iconbottomright; */
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y+1,Bcounter[i].iconbottomright,0x0F);
//		}
//		if(Bcounter[i].coordinates.X <=2)
//		{
//			Bcounter[i].Active = false;
//			Bcounter[i].icontopleft = ' ';
//			Bcounter[i].iconup = ' ';
//			Bcounter[i].icontopright = ' ';
//			Bcounter[i].iconleft = ' ';
//			Bcounter[i].iconcenter = ' ';
//			Bcounter[i].iconright = ' ';
//			Bcounter[i].iconbottomleft = ' ';
//			Bcounter[i].icondown = ' ';
//			Bcounter[i].iconbottomright = ' ';
//		}
//	}
//}
//// POWER UPS
// BOSS MOVE
//void bossMove()
//{
//
//	// move boss
//	if ( spawnclear == 0)
//	{
//		static double timer_move = elapsedTime;
//		if ( elapsedTime - timer_move > bossmovespeed )
//		{
//			timer_move = elapsedTime;
//			if (moveState == 1)
//			{
//				//move towards left
//				moveBoss();
//			}
//			else if ( moveState == 2)
//			{
//				//move upwards
//				moveBossUp();
//				moveYUP--;
//				moveYDOWN = moveYUP;
//				if (moveYUP < 6)
//				{
//					wew = 0;
//					moveState = 3;
//					moveEnemies();
//				}
//			}
//			else if ( moveState == 3)
//			{
//				moveBossDown();
//				moveYDOWN++;
//				if (moveYDOWN > 16)
//				{
//					moveYUP = moveYDOWN;
//					moveState = 2;
//					moveEnemies();
//				}
//			}
//		}
//	}
//}

// SPAWN ENEMIES
// SPAWN BOSS
//
//void bossSpawn()
//{
//		// spawn enemies
//		if ( modifyX <39)
//		{
//			static double timer_spawn = elapsedTime;
//			if ( elapsedTime - timer_spawn > 0.1 )
//			{
//				timer_spawn = elapsedTime;
//				if ( currentEnemy < BOSS_NO )
//				{
//					SpawnBoss(currentEnemy,modifyX,modifyY);
//					spawnclear = 0;
//					moveState = 1;
//					modifyY = 10;	
//					modifyX = modifyX + 2;
//				}
//			}
//		}
//		else if ( wew != 0)
//		{
//			moveState=2;
//			spawnclear = 0;
//		}
//}
//// SPAWN BONUS
//
//void bonusSpawn()
//{
//	//spawn enemines
//	if (combined.enemySettings.modifyX < 48)
//	{
//		static double timer_spawn = elapsedTime;
//		if (elapsedTime - timer_spawn > 0.1)
//		{
//			timer_spawn = elapsedTime;
//			if (combined.enemySettings.currentEnemy < BONUS)
//			{
//				SpawnBonus(currentEnemy, modifyX,combined.enemySettings.modifyY);
//				combined.enemySettings.spawncounter++;
//				//per row
//				combined.enemySettings.moveState = 1;
//				if (modifyY < 14)
//				{
//					modifyY = modifyY + 2;
//				}
//				else
//				{
//					modifyY = 6;	
//					modifyX = modifyX + 2;
//				}
//			}
//		}
//	}
//	else if (combined.enemySettings.wew != 0)
//	{
//		combined.enemySettings.moveState = 2;
//		combined.enemySettings.spawnclear = 0;
//	}
//}
////BOSS SHOOTS
//
//void bossShooting()
//{
//	//Enemy shooting
//	static double timer_shoot = elapsedTime;
//	for(int i =0; i<BOSS_NO;i++)
//	{
//		if(Bcounter[i].Active)
//		{
//			if ( elapsedTime - timer_shoot >bossshootspeed)
//			{
//				timer_shoot = elapsedTime;
//				if(enemyCurrentMissile < 50)
//				{
//					enemyShootBullet1(enemyCurrentMissile,Bcounter[i].coordinates);
//				}
//				else
//				{
//					enemyShootBullet2(enemyCurrentMissile,Bcounter[i].coordinates);
//				}
//			}
//		}
//	}
//}

// GAME SETTINGS
// VARIABLES FOR GLOBAL STRUCT
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
	//check if boss stage
	if (combined.globalSettings.loadlevel < 4)
	{
		loadfromtext(combined.globalSettings.loadlevel);
		enemySpawn();
		enemyMove();
		enemyShooting();
	}
	else if (combined.globalSettings.loadlevel%4 == 0)
	{
		loadbossfromtext(combined.globalSettings.loadlevel);
		//bossSpawn();
		//bossMove();
		//bossShooting();

	}
   /* else if (loadlevel == 5)
	{
		bonusesloadfromtext(loadlevel);
		bonusSpawn();
		enemyMove();
		enemyShooting();
	}*/
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
	if (combined.enemySettings.enemieskilled >= 25)
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
	}
}