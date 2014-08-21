#include "MainMenu.h"
#include "game.h"
#include <iostream>
#include "Framework\console.h"
#include <fstream>
#include <string>
#include "leveldesign.h"
using namespace std;
long long choice = 0;
bool gameover = true;


  

void menuscreen()
{
	const unsigned char FPS = 10; // FPS of this game
	const unsigned int frameTime = 1000 / FPS; // time for each frame

	
	string Menu[4] = {"                                  Start Game",
		              "                                  High Scores", 
					  "                                  Instructions", 
					  "                                  Exit"};
	int pointer = 0;
	
	while(true)
	{
		cls();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		mainScreen();
		
		
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
		}
	
		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					while(true)
					{
						getInput();                         // get keyboard input
						update(g_timer.getElapsedTime());   // update the game
						render();
						g_timer.waitUntil(frameTime); // Frame rate limiter. Limits each frame to a specified time in ms. // render the graphics output to screen
					}
					break;
					
					case 1:
					colour(0x0F);
					cls();
					mainScreen();
					score();
			    	break;
						
					case 2:
					colour(0x0F);
					cls();
					mainScreen();
					instructions();
					break;

					
					case 3:
					colour(0x0F);
					cls();
					exit ( 0 );
					break;
				}
			}
		}
		Sleep(150);
		}	
	
}





void menuscreen2()
{
	const unsigned char FPS = 10; // FPS of this game
	const unsigned int frameTime = 1000 / FPS; // time for each frame

	
	string Menu[4] = {"                                  Resume Game",
		              "                                  High Scores", 
					  "                                  Instructions", 
					  "                                  Exit"};
	int pointer = 0;
	
	while(true)
	{
		cls();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		pauseScreen();
		
		
		for (int i = 0; i < 4; ++i)
		{
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				cout << Menu[i] << endl;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << Menu[i] << endl;
			}
		}
	
		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 3;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 4)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					while(true)
					{
						getInput();                         // get keyboard input
						update(g_timer.getElapsedTime());   // update the game
						render();
						g_timer.waitUntil(frameTime); // Frame rate limiter. Limits each frame to a specified time in ms. // render the graphics output to screen
					}
					break;
					
					case 1:
					colour(0x0F);
					cls();
					mainScreen();
					score();
			    	break;
						
					case 2:
					colour(0x0F);
					cls();
					mainScreen();
					instructions();
					break;

					
					case 3:
					colour(0x0F);
					cls();
					exit ( 0 );
					break;
				}
			}
		}
		Sleep(150);
		}	
	
}


void instructions()
{
	std::cout<< "                                ESC: Main Menu\n                                P: In-Game Pause\n                                Space: Shoot\n                                ArrowKeys: Move\n\n";	
}

void score()
{
	std::cout<< "score";
}