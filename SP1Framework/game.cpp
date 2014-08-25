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

StopWatch b_timer; 
COORD charLocation;
COORD consoleSize;

int modifyY;
int modifyX;
int moveYUP;
int moveYDOWN;
int upordown;
int globalscore;
int moveState;
int wew;
int enemieskilled;
int spawncounter;
int spawnclear;
int loadlevel;
int terrainModX;
int terrainModY;
int terrainBotModY;
int terrainlevel;
int terrainicon;
int terraingo = 0;
int terraingobot = 0;
int terraindestory;
int terraindestorybot = 0;
bool terrain = true;
double enemymovespeed;
int enemyshootspeedrange1;
int enemyshootspeedrange2;
double bossmovespeed;
double bossshootspeed;
bool nextstage = true;
bool droppowerup = true;
unsigned int currentMissile = 0;
unsigned int enemyCurrentMissile = 0;
unsigned int enemyMaxMissile = 0;
unsigned int currentEnemy = 0;
unsigned int currentTerrain = 0;
unsigned int currentTerrainBot = 0;
unsigned int powerupEnemy = 0;
unsigned int maxMissile = 60;
unsigned int playingField = 50;
bool missleFired1 = false;
extern int PowerupIcon;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right;
    consoleSize.Y = csbi.srWindow.Bottom;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X%2+2;
    charLocation.Y = consoleSize.Y/2;
	
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
		if (keyPressed[K_UP] && charLocation.Y > 6)
		{
			Beep(0, 0);
			charLocation.Y--; 
		}
		if (keyPressed[K_LEFT] && charLocation.X > 3)
		{
			Beep(0, 0);
			charLocation.X--; 
		}
		if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 6)
		{
			Beep(0, 0);
			charLocation.Y++; 
		}
		if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 47)
		{
			Beep(0, 0);
			charLocation.X++; 
		}
		static double timer_player = elapsedTime;

		if(keyPressed[K_SPACE] && currentMissile <maxMissile-4)// && !missleFired1)
		{
			
			if ( elapsedTime - timer_player > 0.5)
			{
				timer_player = elapsedTime;
				if(player.PowerUp >= 3)
				{
					shootMissile1(currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(currentMissile,charLocation.X+2,charLocation.Y);
					shootMissile1(currentMissile,charLocation.X,charLocation.Y-1);
				}
				else if(player.PowerUp == 2)
				{
					shootMissile1(currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(currentMissile,charLocation.X,charLocation.Y-1);
				}
				else  if(player.PowerUp == 1)
				{
				shootMissile1(currentMissile,charLocation);
				}
				//missleFired1 = true;
			}
		}
		if(keyPressed[K_SPACE] && currentMissile >=maxMissile-4)// && !missleFired1)
		{
			if ( elapsedTime - timer_player > 0.5)
			{
				timer_player = elapsedTime;
				if(player.PowerUp >= 3)
				{
					currentMissile=0;
					shootMissile2(currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(currentMissile,charLocation.X+2,charLocation.Y);
					shootMissile1(currentMissile,charLocation.X,charLocation.Y-1);
				}
				else if(player.PowerUp == 2)
				{
					currentMissile=0;
					shootMissile2(currentMissile,charLocation.X,charLocation.Y+1);
					shootMissile1(currentMissile,charLocation.X,charLocation.Y-1);
				}
				else  if(player.PowerUp == 1)
				{
					currentMissile=0;
					shootMissile2(currentMissile,charLocation);
				}
			}
		}
		if(keyPressed[K_SPACE] == false)
		{
			missleFired1= false;
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
    // clear previous screen
    colour(0x0F);
    cls();

	leveldesign();

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	gotoXY(50, 3);
    colour(0x03);
    std::cout << "Score:" << globalscore << std::endl;

	gotoXY(50, 4);
    colour(0x03);
    std::cout << "Wave:" << loadlevel << std::endl;

    // render character
	renderCharacter();
	// render missiles
	 colour(0x0B);
	renderMissile();
	// render enemies
	renderEnemies();
	//render boss
	renderBoss();
	//render enemy bullet
	renderEnemyMissile();
	// render powerup
	renderPowerUp();
	// randomly generate terrain
	renderTerrain();
}
// CHARACTERS
void renderCharacter()
{
	// render character
	gotoXY(charLocation);
	colour(0x0C);
	std::cout << player.icon;

	gotoXY(charLocation.X+1,charLocation.Y);
	if (player.PowerUp == 1 || player.PowerUp >= 3)
	{
	colour(0x0B);
	}
	else if ( player.PowerUp == 2)
	{
	colour (0x0F);
	}
	std::cout << player.headIcon;

	gotoXY(charLocation.X,charLocation.Y-1);
	if (player.PowerUp >= 2)
	{
	colour(0x0B);
	}
	else
	{
	colour (0x0F);
	}
	std::cout << player.wingIcon;

	gotoXY(charLocation.X,charLocation.Y+1);
	if (player.PowerUp >= 2)
	{
	colour(0x0B);
	}
	else
	{
	colour (0x0F);
	}
	std::cout <<  player.wingIcon;
}
// ENEMIES
void renderEnemies()
{
	enemycolour();
	// render enemies
	for ( int i = 0; i < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;
		}
		if(counter[i].coordinates.X <=2)
		{
			counter[i].Active = false;
			counter[i].icon = ' ';
		}
	}
}
// BOSS
void renderBoss()
{
	enemycolour();
	// render boss
	for ( int i = 0; i < BOSS_NO; ++i)
	{
		//is boss alive
		if(Bcounter[i].Active)
		{
			gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y-1);
			std::cout << Bcounter[i].icontopleft;
			
			gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y-1);
			std::cout << Bcounter[i].iconup;

			gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y-1);
			std::cout << Bcounter[i].icontopright;

			gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y);
			std::cout << Bcounter[i].iconleft;

			gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y);
			std::cout << Bcounter[i].iconcenter;

			gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y);
			std::cout << Bcounter[i].iconright;

			gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y+1);
			std::cout << Bcounter[i].iconbottomleft;

			gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y+1);
			std::cout << Bcounter[i].icondown;
			
			gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y+1); 
			std::cout << Bcounter[i].iconbottomright; 
	
		}
		if(Bcounter[i].coordinates.X <=2)
		{
			Bcounter[i].Active = false;
			Bcounter[i].icontopleft = ' ';
			Bcounter[i].iconup = ' ';
			Bcounter[i].icontopright = ' ';
			Bcounter[i].iconleft = ' ';
			Bcounter[i].iconcenter = ' ';
			Bcounter[i].iconright = ' ';
			Bcounter[i].iconbottomleft = ' ';
			Bcounter[i].icondown = ' ';
			Bcounter[i].iconbottomright = ' ';
		}
	}
}
// POWER UPS
void renderPowerUp()
{
	colour(0xA0);
	if(powerUp.Active)
	{
		droppowerup = false;
		static double timer_powerUp = elapsedTime;
		if ( elapsedTime - timer_powerUp > 0.5 )
		{
			timer_powerUp = elapsedTime;
			gotoXY(powerUp.corrdinates.X--,powerUp.corrdinates.Y);
			std::cout << powerUp.icon << std::endl;
		}
		else
		{
			gotoXY(powerUp.corrdinates.X,powerUp.corrdinates.Y);
			std::cout << powerUp.icon << std::endl;
		}
		//Check if out of bound
		if(powerUp.corrdinates.X <= 1)
		{
			powerUp.Active = false;
			droppowerup = true;
		}
	}
}
// ALL GAME FUNCTIONS
void updateGame()
{
	//check if boss stage
	if ( loadlevel < 4)
	{
		loadfromtext(loadlevel);
		enemySpawn();
		enemyMove();
		enemyShooting();
	}
	else if (loadlevel%4 == 0)
	{
		loadbossfromtext(loadlevel);
		bossSpawn();
		bossMove();
		bossShooting();

	}
    else if (loadlevel == 5)
	{
		bonusesloadfromtext(loadlevel);
		bonusSpawn();
		enemyMove();
		enemyShooting();
	}
	FormTerrain();
	FormTerrainBot();
	terrainMove();
	collision();
	stageclear();
}
// ENEMY MOVE
void enemyMove()
{
	//check if row has spawned
	if ( spawncounter >=5)
	{
		spawncounter = 0;
		spawnclear = 0;
	}
	//clear to move
	else if ( spawncounter = 0)
	{
		spawnclear = 1;
	}

	// move enemies
	if ( spawnclear == 0)
	{
		static double timer_move = elapsedTime;
		if ( elapsedTime - timer_move > enemymovespeed )
		{
			timer_move = elapsedTime;
			if (moveState == 1)
			{
				//move towards left
				moveEnemies();
			}
			else if ( moveState == 2)
			{
				//move upwards
				moveEnemiesUp();
				moveYUP--;
				moveYDOWN = moveYUP;
				if (moveYUP < 4)
				{
					wew = 0;
					moveState = 3;
					moveEnemies();
				}
			}
			else if ( moveState == 3)
			{
				moveEnemiesDown();
				moveYDOWN++;
				if (moveYDOWN > 8)
				{
					moveYUP = moveYDOWN;
					moveState = 2;
					moveEnemies();
				}
			}
		}
	}
}
// BOSS MOVE
void bossMove()
{

	// move boss
	if ( spawnclear == 0)
	{
		static double timer_move = elapsedTime;
		if ( elapsedTime - timer_move > bossmovespeed )
		{
			timer_move = elapsedTime;
			if (moveState == 1)
			{
				//move towards left
				moveBoss();
			}
			else if ( moveState == 2)
			{
				//move upwards
				moveBossUp();
				moveYUP--;
				moveYDOWN = moveYUP;
				if (moveYUP < 6)
				{
					wew = 0;
					moveState = 3;
					moveEnemies();
				}
			}
			else if ( moveState == 3)
			{
				moveBossDown();
				moveYDOWN++;
				if (moveYDOWN > 16)
				{
					moveYUP = moveYDOWN;
					moveState = 2;
					moveEnemies();
				}
			}
		}
	}
}
// SPAWN ENEMY
void enemySpawn()
{
	// spawn enemies
		if ( modifyX <48)
		{
			static double timer_spawn = elapsedTime;
			if ( elapsedTime - timer_spawn > 0.1 )
			{
				timer_spawn = elapsedTime;
				if ( currentEnemy < NO_OF_ENEMIES )
				{
					SpawnEnemy(currentEnemy,modifyX,modifyY);
					spawncounter++;
					moveState = 1;
					//per row
					if ( modifyY < 16)
					{
						modifyY=modifyY+2;
					}
					//next row and spawn interval
					else
					{
						modifyY = 8;	
						modifyX = modifyX + 2;
					}
				}
			}
		}
		else if ( wew != 0)
		{
			moveState=2;
			spawnclear = 0;
		}
}
// SPAWN BOSS
void bossSpawn()
{
		// spawn enemies
		if ( modifyX <39)
		{
			static double timer_spawn = elapsedTime;
			if ( elapsedTime - timer_spawn > 0.1 )
			{
				timer_spawn = elapsedTime;
				if ( currentEnemy < BOSS_NO )
				{
					SpawnBoss(currentEnemy,modifyX,modifyY);
					spawnclear = 0;
					moveState = 1;
					modifyY = 10;	
					modifyX = modifyX + 2;
				}
			}
		}
		else if ( wew != 0)
		{
			moveState=2;
			spawnclear = 0;
		}
}
// SPAWN BONUS
void bonusSpawn()
{
	//spawn enemines
	if (modifyX < 48)
	{
		static double timer_spawn = elapsedTime;
		if (elapsedTime - timer_spawn > 0.1)
		{
			timer_spawn = elapsedTime;
			if (currentEnemy < BONUS)
			{
				SpawnBonus(currentEnemy, modifyX, modifyY);
				spawncounter++;
				//per row
				moveState = 1;
				if (modifyY < 14)
				{
					modifyY = modifyY + 2;
				}
				else
				{
					modifyY = 6;	
					modifyX = modifyX + 2;
				}
			}
		}
	}
	else if (wew != 0)
	{
		moveState = 2;
		spawnclear = 0;
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
			if ( elapsedTime - timer_shoot >rand()%enemyshootspeedrange1 + enemyshootspeedrange2 )
			{
				timer_shoot = elapsedTime;
				if(enemyCurrentMissile < 50)
				{
					enemyShootBullet1(enemyCurrentMissile,counter[i].coordinates);
				}
				else
				{
					enemyShootBullet2(enemyCurrentMissile,counter[i].coordinates);
				}
			}
		}
	}
}
//BOSS SHOOTS
void bossShooting()
{
	//Enemy shooting
	static double timer_shoot = elapsedTime;
	for(int i =0; i<BOSS_NO;i++)
	{
		if(Bcounter[i].Active)
		{
			if ( elapsedTime - timer_shoot >bossshootspeed)
			{
				timer_shoot = elapsedTime;
				if(enemyCurrentMissile < 50)
				{
					enemyShootBullet1(enemyCurrentMissile,Bcounter[i].coordinates);
				}
				else
				{
					enemyShootBullet2(enemyCurrentMissile,Bcounter[i].coordinates);
				}
			}
		}
	}
}
//IS STAGE CLEARED?
void stageclear()
{
		//if stage is clear, proceed
	if (enemieskilled >= 25)
	{
		loadlevel++;
		currentEnemy =0;
		enemieskilled =0;
		modifyX = 38;
		modifyY = 8;
		moveYUP = modifyY;
		moveYDOWN = 0;
		wew = 1;
		spawnclear = 1;
	}
}
// COLLOSION
void collision()
{
	//Check Powerup collide
	if(powerUpPlayerCollision(charLocation,powerUp))
	{
		static double timer_spawn = elapsedTime;
		if ( elapsedTime - timer_spawn > 0.1 )
		{
			timer_spawn = elapsedTime;
			powerUp.Active = false;
			player.PowerUp++;
			droppowerup = true;
		}
	}
	// check collision
	for(int i = 0; i<50;i++)
	{

		if(checkPlayerDeath(charLocation,enemyBullet[i],counter[i]))
		{
			//PLAYER DEATH SCREEN
			cls();
			loseScreen();
			system("pause");
			menuscreen();
		}
		if ( loadlevel%4 != 0)
		{
			for(int j = 0; j<NO_OF_ENEMIES;j++)
			{
				if ( checkCollisionBullet(missile[i], counter[j],droppowerup))
				{
					if ( counter[j].hp <= 0 )
					{
						globalscore += counter[j].score;
						enemieskilled++;
					}
				}

			}
		}
		else
		{
			for(int j = 0; j<BOSS_NO;j++)
			{
				if ( BosscheckCollisionBullet(missile[i], Bcounter[j]))
				{
					if ( Bcounter[j].hp <= 0 )
					{
						globalscore += Bcounter[j].score;
						enemieskilled = 25;
					}
				}

			}
		}
	}
}
// COLOURS OF ENEMIES
void enemycolour()
{
	switch (loadlevel)
	{
	case 1:colour(0x0E);
		break;
	case 2:colour(0x06);
		break;
	case 3:colour(0x0F);
		break;
	case 4:colour(0x0C);
		break;
	case 5: colour(0x0D);
		break;
	}
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
		if (indata >> modifyY >> modifyX >> moveYUP >> moveYDOWN >> upordown >> globalscore >> moveState >> wew >> enemieskilled >> spawncounter >> spawnclear >> loadlevel >> enemymovespeed >> enemyshootspeedrange1 >> enemyshootspeedrange2 >> bossmovespeed >> bossmovespeed >> terrainModX >> terrainModY >> terrainBotModY >> terrainicon)
		{
		}
	}
}
// RANDOMLY GENERATED TERRAIN TOP
void FormTerrain() 
{
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 0.2 )
	{
		timer_spawn = elapsedTime;
		if ( currentTerrain < TERRAIN )
		{
			SpawnTerrain(currentTerrain,terrainModX, terrainModY, terrainicon);
			if ( terrainModY < 3)
			{
				terrainModY++;
			}
			else if ( terrainModY == 3)
			{
				if ( rand()%3+1 == 1)
				{
					terrainModY--;
				}
				else if ( rand()%3+1 == 2)
				{	
				}
				else if ( rand()%3+1 == 3)
				{
					terrainModY++;
				}
			}
			else if ( terrainModY == 4)
			{
				terrainModY--;
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
		if ( currentTerrain < TERRAIN )
		{
			SpawnTerrainBot(currentTerrain,terrainModX, terrainBotModY, terrainicon);
			if ( terrainBotModY > 21)
			{
				terrainBotModY--;
			}
			else if ( terrainBotModY == 21)
			{
				if ( rand()%3+1 == 1)
				{
					terrainBotModY++;
				}
				else if ( rand()%3+1 == 2)
				{	
				}
				else if ( rand()%3+1 == 3)
				{
					terrainBotModY--;
				}
			}
			else if ( terrainBotModY == 20)
			{
				terrainBotModY++;
			}
		}
	}	

}
// RENDER TERRAIN
void renderTerrain()
{
	colour(0x0F);
	// render top terrain
	for ( int i = terraingo; i < TERRAIN; ++i)
	{
		//is terrain active?
		if(generator[i].Active)
		{
			gotoXY(generator[i].coordinates.X,generator[i].coordinates.Y);
			std::cout << generator[i].icon;
		}
		if(generator[i].coordinates.X <=2)
		{
			generator[i].Active = false;
			generator[i].icon = ' ';
			terraindestory++;
		}
	}

	// render bot terrain
	for ( int i = terraingobot; i < TERRAIN; ++i)
	{
		//is terrain bot active?
		if(generator2[i].Active)
		{
			gotoXY(generator2[i].coordinates.X,generator2[i].coordinates.Y);
			std::cout << generator2[i].icon;
		}
		if(generator2[i].coordinates.X <=2)
		{
			generator2[i].Active = false;
			generator2[i].icon = ' ';
			terraindestorybot++;
		}
	}

	//terrain top reset
	if (terraindestory >= 10)
	{
		terraingo = 0;
	}

	//terrain bot reset
	if (terraindestorybot >= 10)
	{
		terraingobot = 0;
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




