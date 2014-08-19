#include "MainMenu.h"
#include "game.h"
#include <iostream>
#include "Framework\console.h"



void menuscreen()
{
	const unsigned char FPS = 10; // FPS of this game
	const unsigned int frameTime = 1000 / FPS; // time for each frame
	
	
	std::cout<< "WELCOME TO PONGTATO INVASION GAME!\n\n";
	std::cout<< "OPTIONS:\nPlease Select\n\n";
	std::cout<< "1: Start Game\n";
	std::cout<< "2: Score\n";
	std::cout<< "3: Instructions\n";
	std::cout<< "4: Exit Game\n";


	long long choice = 0;
	MainMenu state = PLAYGAME;

	
	while (choice != EXITGAME)
	{
		if(choice != PLAYGAME)
		{
			std::cout<< "Your Number Choice: ";
			std::cin >> choice;
		}
		

		
		switch(choice)
		{

		case PLAYGAME:
			
			getInput();                         // get keyboard input
			update(g_timer.getElapsedTime());   // update the game
			render();
			g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms. // render the graphics output to screen
			break;

		case SCORE: std::cout<< "SCORE\n";
			break;
			
		case INSTRUCTION: std::cout<< "ESC: Main Menu\nP: Pause\nSpace: Shoot\nArrowKeys: Move\n";
			break;

		case EXITGAME: exit ( 0 );
			break;

		default: std::cout<< "Invalid Input, Please Reselect\n\n";
		
		}
	}
}

void menuscreen2()
{
	const unsigned char FPS = 10; // FPS of this game
	const unsigned int frameTime = 1000 / FPS; // time for each frame
	
	
	std::cout<< "GAME PAUSE!\n\n";
	std::cout<< "OPTIONS:\nPlease Select\n\n";
	std::cout<< "1: Resume Game\n";
	std::cout<< "2: Score\n";
	std::cout<< "3: Instructions\n";
	std::cout<< "4: Exit Game\n";


	long long choice = 0;
	MainMenu state = PLAYGAME;

	
	while (choice != EXITGAME)
	{
		if(choice != PLAYGAME)
		{
			std::cout<< "Your Number Choice: ";
			std::cin >> choice;
		}
		

		
		switch(choice)
		{

		case PLAYGAME:
			
			getInput();                         // get keyboard input
			update(g_timer.getElapsedTime());   // update the game
			render();
			g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms. // render the graphics output to screen
			break;

		case SCORE: std::cout<< "SCORE\n";
			break;
			
		case INSTRUCTION: std::cout<< "ESC: Main Menu\nP: Pause\nSpace: Shoot\nArrowKeys: Move\n";
			break;

		case EXITGAME: exit ( 0 );
			break;

		default: std::cout<< "Invalid Input, Please Reselect\n\n";
		
		}
	}
}

