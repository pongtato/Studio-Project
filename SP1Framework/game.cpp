// This is the main file for the game logic and function
//
//
#include "MainMenu.h"
#include "game.h"
#include "Shoot.h"
#include "SpawnEnemies.h"
#include "leveldesign.h"
#include "Framework\console.h"
#include "MainMenu.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

extern ENEMY counter[26];
extern BULLET missile[50];
extern BULLET enemyBullet[50];

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
unsigned int currentMissile = 0;
unsigned int enemyCurrentMissile = 0;
unsigned int enemyMaxMissile = 0;
unsigned int currentEnemy = 0;
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

	loadfromtext();
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
		moveState=2;
		spawnclear = 0;
	}

	if ( spawncounter >=5)
	{
		spawncounter = 0;
		spawnclear = 0;
	}
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

	if (enemieskilled >= 25)
	{
		currentEnemy =0;
		enemieskilled =0;
		modifyX = 38;
		modifyY = 6;
		moveYUP = modifyY;
		moveYDOWN = 0;
		wew =1;
		spawnclear = 1;
	}

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
	if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 7)
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
	colour(0x07);
	renderEnemies();
	//render enemy bullet
	renderEnemyMissile();
}

void renderCharacter()
{
	// render character
	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)15;

	gotoXY(charLocation.X+1,charLocation.Y);
	colour(0x0F);
	std::cout << (char)16;

	gotoXY(charLocation.X,charLocation.Y-1);
	colour(0x0F);
	std::cout << (char)4;

	gotoXY(charLocation.X,charLocation.Y+1);
	colour(0x0F);
	std::cout << (char)4;
}

void renderEnemies()
{
	// render enemies
	for ( int i = 0; i < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;
		}
	}
}