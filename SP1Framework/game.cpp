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

extern BOSS Bcounter[10]; 
extern ENEMY counter[26];
extern BULLET missile[50];
extern BULLET enemyBullet[50];
extern PLAYER player;
extern BULLET powerUp;
extern WORLD generator[999];
extern WORLD generator2[999];
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
		if (keyPressed[K_UP] && charLocation.Y > 5)
		{
			Beep(0, 0);
			charLocation.Y--; 
		}
		if (keyPressed[K_LEFT] && charLocation.X > 3)
		{
			Beep(0, 0);
			charLocation.X--; 
		}
		if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 8)
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
	//renderPowerUp();
	// randomly generate terrain
	//renderTerrain();

	// Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}

// GAME SETTINGS
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
// CHARACTERS
void renderCharacter()
{
	// render character
	/*gotoXY(charLocation);
	colour(0x0C);
	std::cout << player.icon;*/
	writeToBuffer(charLocation,player.icon,0x0C);

	//gotoXY(charLocation.X+1,charLocation.Y);
	if (player.PowerUp == 1 || player.PowerUp >= 3)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0B);
	}
	else if ( player.PowerUp == 2)
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0F);
	}

	//gotoXY(charLocation.X,charLocation.Y-1);
	if (player.PowerUp >= 2)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0B);
	}
	else
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0F);
	}
	//std::cout << player.wingIcon;

//	gotoXY(charLocation.X,charLocation.Y+1);
	if (player.PowerUp >= 2)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0B);
	}
	else
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0F);
	}
	//std::cout <<  player.wingIcon;
}
// ENEMIES
void renderEnemies()
{
	//enemycolour();
	// render enemies
	for ( int i = 0; i < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			/*gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;*/
			writeToBuffer(counter[i].coordinates,counter[i].icon);
		}
		if(counter[i].coordinates.X <=2)
		{
			counter[i].Active = false;
			counter[i].icon = ' ';
		}
	}
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
//void renderPowerUp()
//{
//	//colour(0xA0);
//	if(powerUp.Active)
//	{
//		droppowerup = false;
//		static double timer_powerUp = elapsedTime;
//		if ( elapsedTime - timer_powerUp > 0.5 )
//		{
//			timer_powerUp = elapsedTime;
//			//gotoXY(powerUp.corrdinates.X--,powerUp.corrdinates.Y);
//			//std::cout << powerUp.icon << std::endl;
//			writeToBuffer(powerUp.corrdinates.X--,powerUp.corrdinates.Y,powerUp.icon,0xA0);
//		}
//		else
//		{
//			/*gotoXY(powerUp.corrdinates.X,powerUp.corrdinates.Y);
//			std::cout << powerUp.icon << std::endl;*/
//			writeToBuffer(powerUp.corrdinates.X,powerUp.corrdinates.Y,powerUp.icon,0xA0);
//		}
//		//Check if out of bound
//		if(powerUp.corrdinates.X <= 1)
//		{
//			powerUp.Active = false;
//			droppowerup = true;
//		}
//	}
//}
//// BOSS MOVE
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
// ALL GAME FUNCTIONS
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
	//collision();
	//stageclear();
}
void enemySpawn()
{
	// spawn enemies
	if ( combined.enemySettings.modifyX <48)
		{
			static double timer_spawn = elapsedTime;
			if ( elapsedTime - timer_spawn > 0.1 )
			{
				timer_spawn = elapsedTime;
				if ( combined.enemySettings.currentEnemy < NO_OF_ENEMIES )
				{
					SpawnEnemy(combined.enemySettings.currentEnemy,combined.enemySettings.modifyX,combined.enemySettings.modifyY);
					combined.enemySettings.spawncounter++;
					combined.enemySettings.moveState = 1;
					//per row
					if ( combined.enemySettings.modifyY < 16)
					{
						combined.enemySettings.modifyY=combined.enemySettings.modifyY+2;
					}
					//next row and spawn interval
					else
					{
						combined.enemySettings.modifyY = 8;	
						combined.enemySettings.modifyX = combined.enemySettings.modifyX + 2;
					}
				}
			}
		}
	else if ( combined.enemySettings.wew != 0)
		{
			combined.enemySettings.moveState=2;
			combined.enemySettings.spawnclear=0;
		}
}
// ENEMY MOVE
void enemyMove()
{
	//check if row has spawned
	if ( combined.enemySettings.spawncounter >=5)
	{
		combined.enemySettings.spawncounter = 0;
		combined.enemySettings.spawnclear = 0;
	}
	//clear to move
	else if ( combined.enemySettings.spawncounter = 0)
	{
		combined.enemySettings.spawnclear = 1;
	}

	// move enemies
	if ( combined.enemySettings.spawnclear == 0)
	{
		static double timer_move = elapsedTime;
		if ( elapsedTime - timer_move > combined.enemySettings.enemymovespeed )
		{
			timer_move = elapsedTime;
			if (combined.enemySettings.moveState == 1)
			{
				//move towards left
				moveEnemies();
			}
			else if ( combined.enemySettings.moveState == 2)
			{
				//move upwards
				moveEnemiesUp();
				combined.enemySettings.moveYUP--;
				combined.enemySettings.moveYDOWN = combined.enemySettings.moveYUP;
				if (combined.enemySettings.moveYUP < 4)
				{
					combined.enemySettings.wew = 0;
					combined.enemySettings.moveState = 3;
					moveEnemies();
				}
			}
			else if (combined.enemySettings.moveState == 3)
			{
				moveEnemiesDown();
				combined.enemySettings.moveYDOWN++;
				if (combined.enemySettings.moveYDOWN > 8)
				{
					combined.enemySettings.moveYUP = combined.enemySettings.moveYDOWN;
					combined.enemySettings.moveState = 2;
					moveEnemies();
				}
			}
		}
	}
}
// ENEMY SHOOTS
void enemyShooting()
{
	//Enemy shooting
	static double timer_shoot = elapsedTime;
	for(int i =0; i<NO_OF_ENEMIES;i++)
	{
		if(counter[i].Active)
		{
			if ( elapsedTime - timer_shoot >rand()%combined.enemySettings.enemyshootspeedrange1 + combined.enemySettings.enemyshootspeedrange2 )
			{
				timer_shoot = elapsedTime;
				if(combined.enemySettings.enemyCurrentMissile < 50)
				{
					enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
				}
				else
				{
					enemyShootBullet2(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
				}
			}
		}
	}
}
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
////IS STAGE CLEARED?
//
//void stageclear()
//{
//		//if stage is clear, proceed
//	if (enemieskilled >= 25)
//	{
//		loadlevel++;
//		currentEnemy =0;
//		enemieskilled =0;
//		modifyX = 38;
//		modifyY = 8;
//		moveYUP = modifyY;
//		moveYDOWN = 0;
//		wew = 1;
//		spawnclear = 1;
//	}
//}
//// COLLOSION
//
void collision()
{
//	//Check Powerup collide
//	if(powerUpPlayerCollision(charLocation,powerUp))
//	{
//		static double timer_spawn = elapsedTime;
//		if ( elapsedTime - timer_spawn > 0.1 )
//		{
//			timer_spawn = elapsedTime;
//			powerUp.Active = false;
//			player.PowerUp++;
//			droppowerup = true;
//		}
//	}
	// check collision
	for(int i = 0; i<50;i++)
	{
		//
		//		if(checkPlayerDeath(charLocation,enemyBullet[i],counter[i]))
		//		{
		//			//PLAYER DEATH SCREEN
		//			cls();
		//			loseScreen();
		//			system("pause");
		//			menuscreen();
		//		}
		//		if ( loadlevel%4 != 0)
		//		{
		for(int j = 0; j<NO_OF_ENEMIES;j++)
		{
			if ( checkCollisionBullet(missile[i], counter[j],combined.enemySettings.droppowerup))
			{
				if ( counter[j].hp <= 0 )
				{
					combined.globalSettings.globalscore += counter[j].score;
					combined.enemySettings.enemieskilled++;
				}
			}

		}
	}
//		else
//		{
//			for(int j = 0; j<BOSS_NO;j++)
//			{
//				if ( BosscheckCollisionBullet(missile[i], Bcounter[j]))
//				{
//					if ( Bcounter[j].hp <= 0 )
//					{
//						globalscore += Bcounter[j].score;
//						enemieskilled = 25;
//					}
//				}
//
//			}
//		}
//	}
}
//// COLOURS OF ENEMIES
//
//void enemycolour()
//{
//	switch (loadlevel)
//	{
//	case 1:colour(0x0E);
//		break;
//	case 2:colour(0x06);
//		break;
//	case 3:colour(0x0F);
//		break;
//	case 4:colour(0x0C);
//		break;
//	case 5: colour(0x0D);
//		break;
//	}
//}
//






// RANDOMLY GENERATED TERRAIN TOP
void FormTerrain() 
{
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 0.2 )
	{
		timer_spawn = elapsedTime;
		if ( combined.terrainSettings.currentTerrain < TERRAIN )
		{
			SpawnTerrain(combined.terrainSettings.currentTerrain,combined.terrainSettings.terrainModX,combined.terrainSettings.terrainModY, combined.terrainSettings.terrainicon);
			if ( combined.terrainSettings.terrainModY < 3)
			{
				combined.terrainSettings.terrainModY++;
			}
			else if ( combined.terrainSettings.terrainModY == 3)
			{
				if ( rand()%3+1 == 1)
				{
					combined.terrainSettings.terrainModY--;
				}
				else if ( rand()%3+1 == 2)
				{	
				}
				else if ( rand()%3+1 == 3)
				{
					combined.terrainSettings.terrainModY++;
				}
			}
			else if ( combined.terrainSettings.terrainModY == 4)
			{
				combined.terrainSettings.terrainModY--;
			}
		}
	}	

}

// RANDOMLY GENERATED TERRAIN BOT
void FormTerrainBot() 
{
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 0.2 )
	{
		timer_spawn = elapsedTime;
		if ( combined.terrainSettings.currentTerrain < TERRAIN )
		{
			SpawnTerrainBot(combined.terrainSettings.currentTerrain,combined.terrainSettings.terrainModX, combined.terrainSettings.terrainBotModY, combined.terrainSettings.terrainicon);
			if ( combined.terrainSettings.terrainBotModY > 21)
			{
				combined.terrainSettings.terrainBotModY--;
			}
			else if ( combined.terrainSettings.terrainBotModY == 21)
			{
				if ( rand()%3+1 == 1)
				{
					combined.terrainSettings.terrainBotModY++;
				}
				else if ( rand()%3+1 == 2)
				{	
				}
				else if ( rand()%3+1 == 3)
				{
					combined.terrainSettings.terrainBotModY--;
				}
			}
			else if ( combined.terrainSettings.terrainBotModY == 20)
			{
				combined.terrainSettings.terrainBotModY++;
			}
		}
	}	

}

// RENDER TERRAIN
void renderTerrain()
{
	// render top terrain
	for ( int i = combined.terrainSettings.terraingo; i < TERRAIN; ++i)
	{
		//is terrain active?
		if(generator[i].Active)
		{
			/*gotoXY(generator[i].coordinates.X,generator[i].coordinates.Y);
			std::cout << generator[i].icon;*/
			writeToBuffer(generator[i].coordinates,generator[i].icon,0x0F);
		}
		if(generator[i].coordinates.X <=2)
		{
			generator[i].Active = false;
			generator[i].icon = ' ';
			combined.terrainSettings.terraindestory++;
		}
	}

	// render bot terrain
	for ( int i = combined.terrainSettings.terraingobot; i < TERRAIN; ++i)
	{
		//is terrain bot active?
		if(generator2[i].Active)
		{
			/*gotoXY(generator2[i].coordinates.X,generator2[i].coordinates.Y);
			std::cout << generator2[i].icon;*/
			writeToBuffer(generator2[i].coordinates,generator2[i].icon,0x0F);
		}
		if(generator2[i].coordinates.X <=2)
		{
			generator2[i].Active = false;
			generator2[i].icon = ' ';
			combined.terrainSettings.terraindestorybot++;
		}
	}

	//terrain top reset
	if (combined.terrainSettings.terraindestory >= 10)
	{
		combined.terrainSettings.terraingo = 0;
	}

	//terrain bot reset
	if (combined.terrainSettings.terraindestorybot >= 10)
	{
		combined.terrainSettings.terraingobot = 0;
	}
}

// SCROLL TERRAIN
void terrainMove()
{
	static double timer_move = elapsedTime;
	if ( elapsedTime - timer_move > 0.2 )
	{
		timer_move = elapsedTime;
		{
			//move towards left
			moveTerrain();
			moveTerrainBot();
		}
	}
}
