// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Shoot.h"
#include "SpawnEnemies.h"
#include "leveldesign.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>


double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];


StopWatch b_timer; 
COORD charLocation;
COORD consoleSize;

unsigned int currentMissile = 0;
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
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        Beep(1440, 30);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
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
        g_quitGame = true;   
	}
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

	// render enemies
	renderEnemies();

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
	renderCharacter();
	// render missiles
	renderMissile();
	
	//leveldesign();
	
}
void renderCharacter()
{
	// render character
	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)1;
}
