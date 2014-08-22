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

StopWatch b_timer; 
COORD charLocation;
COORD consoleSize;

int modifyY =6;
int modifyX =38;
int moveYUP = modifyY;
int moveYDOWN = 0;
int upordown = 1;
int globalscore = 0;
int moveState = 1;
int wew = 1;
int enemieskilled =0;
int spawncounter = 0;
int spawnclear = 1;
int loadlevel = 5;
int powerupclear =0;
unsigned int currentMissile = 0;
unsigned int enemyCurrentMissile = 0;
unsigned int enemyMaxMissile = 0;
unsigned int currentEnemy = 0;
unsigned int powerupEnemy = 0;
unsigned int maxMissile = 50;
unsigned int playingField = 50;
bool missleFired1 = false;

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
		if (keyPressed[K_UP] && charLocation.Y > 3)
		{
			Beep(0, 0);
			charLocation.Y--; 
		}
		if (keyPressed[K_LEFT] && charLocation.X > 2)
		{
			Beep(0, 0);
			charLocation.X--; 
		}
		if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 8)
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

		if(keyPressed[K_SPACE] && currentMissile <maxMissile)// && !missleFired1)
		{
			if ( elapsedTime - timer_player > 0.5)
			{
				timer_player = elapsedTime;
				shootMissile1(currentMissile,charLocation);
				//missleFired1 = true;
			}
		}
		if(keyPressed[K_SPACE] && currentMissile >=maxMissile)// && !missleFired1)
		{
			if ( elapsedTime - timer_player > 0.5)
			{
				timer_player = elapsedTime;
				shootMissile2(currentMissile,charLocation);
				//missleFired1 = true;
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
}

void renderCharacter()
{
	// render character
	gotoXY(charLocation);
	colour(0x0C);
	std::cout << player.icon;

	gotoXY(charLocation.X+1,charLocation.Y);
	colour(0x0F);
	std::cout << player.headIcon;

	gotoXY(charLocation.X,charLocation.Y-1);
	colour(0x0F);
	std::cout << player.wingIcon;

	gotoXY(charLocation.X,charLocation.Y+1);
	colour(0x0F);
	std::cout <<  player.wingIcon;
}

void renderEnemies()
{
	enemycolour();
	// render enemies
	for ( int i = 0; i < NO_OF_ENEMIES; ++i)
	{
		if ( i < 5)
		{
			enemycolour();
		}
		else
		{
			colour(0x0F);
		}
		//is enemy alive
		if(counter[i].Active == true)
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

void renderBoss()
{
	enemycolour();
	// render boss
	for ( int i = 0; i < BOSS_NO; ++i)
	{
		//is boss alive
		if(Bcounter[i].Active == true)
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

void updateGame()
{
	//check if boss stage
	if ( loadlevel%4 != 0)
	{
		loadfromtext(loadlevel);
		enemySpawn();
		enemyMove();
	}
	else if (loadlevel ==4)
	{
		loadbossfromtext(loadlevel);
		bossSpawn();
		bossMove();

	}
    else if (loadlevel == 5)
	{
		bonusesloadfromtext(loadlevel);
		bonusSpawn();
	}

	enemyShooting();
	collision();
	stageclear();
}

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
		if ( elapsedTime - timer_move > 0.2 )
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
				if (moveYUP < 3)
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
				if (moveYDOWN > 9)
				{
					moveYUP = moveYDOWN;
					moveState = 2;
					moveEnemies();
				}
			}
		}
	}
}

void bossMove()
{

	// move boss
	if ( spawnclear == 0)
	{
		static double timer_move = elapsedTime;
		if ( elapsedTime - timer_move > 0.5 )
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
				if (moveYUP < 4)
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
					if ( modifyY < 14)
					{
						modifyY=modifyY+2;
					}
					//next row and spawn interval
					else
					{
						modifyY = 6;	
						modifyX = modifyX + 2;
					}
				}
			}
		}
		else if ( wew != 0)
		{
			powerupclear = 0;
			moveState=2;
			spawnclear = 0;
		}
}

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
void bonusSpawn()
{
	//spawn enemines
	if (modifyX <48)
	{
		static double timer_spawn = elapsedTime;
		if (elapsedTime - timer_spawn > 0.1)
		{
			timer_spawn = elapsedTime;
			if (currentEnemy < Bonus)
			{
				SpawnBonus(currentEnemy, modifyX, modifyY);
				spawncounter++;
				//per row
				if (modifyY < 14)
				{
					modifyY = modifyY + 2;
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

void enemyShooting()
{
	//Enemy shooting
	static double timer_shoot = elapsedTime;
	for(int i =0; i<NO_OF_ENEMIES;i++)
	{
		if(counter[i].Active)
		{
			if ( elapsedTime - timer_shoot >rand()%6+1)
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

void stageclear()
{
		//if stage is clear, proceed
	if (enemieskilled >= 25)
	{
		currentEnemy =0;
		enemieskilled =0;
		modifyX = 38;
		modifyY = 6;
		moveYUP = modifyY;
		moveYDOWN = 0;
		wew = 1;
		spawnclear = 1;
		loadlevel++;
		powerupclear = 1;
	}
}

void collision()
{
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
				if ( checkCollisionBullet(missile[i], counter[j]) )
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
				if ( BosscheckCollisionBullet(missile[i], Bcounter[j]) )
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

void enemycolour()
{
	colour(0x09);
}