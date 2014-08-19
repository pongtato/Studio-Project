// This is the main file to hold everthing together

#include "MainMenu.h"
#include "Framework\timer.h"
#include "game.h"
#include <string>

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game


void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.

	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{  
        menuscreen(); 
	}    
}
