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

int globalscore = 0;
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
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X%2;
    charLocation.Y = consoleSize.Y/2;
	
    elapsedTime = 0.0;
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
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 1 )
	{
		//Timer interval for spawn
		timer_spawn = elapsedTime;

		if ( currentEnemy < NO_OF_ENEMIES )
			SpawnEnemy(currentEnemy);


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
	// move enemies
	static double timer_move = elapsedTime;
	if ( elapsedTime - timer_move > 0.5 )
	{
		timer_move = elapsedTime;

		moveEnemies();
	}
	
	
	// check collision
	for(int i = 0; i<50;i++)
	{
		for(int j = 0; j<NO_OF_ENEMIES;j++)
		{
			if ( checkCollisionBullet(missile[i], counter[j]) )
			{
				globalscore += counter[j].score;
			}
		}
	}

	// Updating the location of the character based on the key press
	if (keyPressed[K_UP] && charLocation.Y > 0)
	{
		Beep(0, 0);
		charLocation.Y--; 
	}
	if (keyPressed[K_LEFT] && charLocation.X > 0)
	{
		Beep(0, 0);
		charLocation.X--; 
	}
	if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
	{
		Beep(0, 0);
		charLocation.Y++; 
	}
	if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
	{
		Beep(0, 0);
		charLocation.X++; 
	}
	if(keyPressed[K_SPACE] && currentMissile <maxMissile && !missleFired1)
	{
		shootMissile1(currentMissile,charLocation);
		missleFired1 = true;
	}
	if(keyPressed[K_SPACE] && currentMissile >=maxMissile && !missleFired1)
	{
		shootMissile2(currentMissile,charLocation);
		missleFired1 = true;
	}
	if(keyPressed[K_SPACE] == false)
	{
		missleFired1= false;
	}
    // quits the game if player hits the escape key
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

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

	gotoXY(60, 0);
    colour(0x03);
    std::cout << "Score:" << globalscore << std::endl;

    // render character
	renderCharacter();
	// render missiles
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
	std::cout << (char)1;
}

void renderEnemies()
{
	// render enemies
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;
		}
	}
}