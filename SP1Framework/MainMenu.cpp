#include "MainMenu.h"
#include "game.h"
#include <iostream>
#include "Framework\console.h"
#include <fstream>
#include <string>
#include "leveldesign.h"
#include <conio.h>  
string Instruction[99] = {"ESC: Pause Menu", "Space: Shoot", "ArrowKeys: Move"};
string pongMenu[5] = {"1:StartGame", "2:HighScores", "3:Instruction", "4:Exit", "Welcome to the Pongtato Invasion Game!!!"};

char c;


void menuscreen()
{		
	
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[4],0x03);
	writeToBuffer(30,18,pongMenu[0],0x07);
	writeToBuffer(30,19,pongMenu[1],0x07);
	writeToBuffer(30,20,pongMenu[2],0x07);
	writeToBuffer(30,21,pongMenu[3],0x07);
	flushBufferToConsole();

		c = getch();

		switch (c)
		{
		case '1': 
			mainLoop();
			break;

		case '2':
			clearBuffer(0x0F);
			score();
			c = '0';
			c = getch();
			if ( c = 27 )
			{
				menuscreen();
			}

			else
			{
				menuscreen();
			}
			break;

		case '3':
			clearBuffer(0x0F);
			instructions();
			c = '0';
			c = getch();
			if ( c = 27 )
			{
				menuscreen();
			}

			else
			{
				menuscreen();
			}
			break;

		case '4':
			clearBuffer(0x0F);
			g_quitGame = true;
			break;

		default:
			clearBuffer(0x0F);
			menuscreen();
			break;

		}
}







void instructions()
{
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[4],0x03);
	writeToBuffer(30,18, Instruction[0],0x07);
	writeToBuffer(30,19, Instruction[1],0x07);
	writeToBuffer(30,20, Instruction[2],0x07);
	writeToBuffer(30,21, Instruction[3],0x07);
	flushBufferToConsole();
}

void score()
{
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[4],0x03);
	writeToBuffer(30,18, Instruction[0],0x07);
	writeToBuffer(30,19, Instruction[1],0x07);
	writeToBuffer(30,20, Instruction[2],0x07);
	writeToBuffer(30,21, Instruction[3],0x07);
	flushBufferToConsole();
}