#include "MainMenu.h"
#include "game.h"
#include <iostream>
#include "Framework\console.h"
#include <fstream>
#include <string>
#include "leveldesign.h"
#include <conio.h>  
string Instruction[99] = {"ESC: Pause Menu", "Space: Shoot", "ArrowKeys: Move"};
string pongMenu[99] = {"1:","2:","3:", "4:", 
"StartGame", "HighScores", "Instruction", "Exit",
"Welcome to the Pongtato Invasion Game!!!"};

char c;


void menuscreen()
{		
	
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[8],0x03);
	writeToBuffer(31,18,pongMenu[0],0x06);
	writeToBuffer(34,18,pongMenu[4],0x07);
	writeToBuffer(31,19,pongMenu[1],0x06);
	writeToBuffer(34,19,pongMenu[5],0x07);
	writeToBuffer(31,20,pongMenu[2],0x06);
	writeToBuffer(34,20,pongMenu[6],0x07);
	writeToBuffer(31,21,pongMenu[3],0x06);
	writeToBuffer(34,21,pongMenu[7],0x07);
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
	writeToBuffer(20,14,pongMenu[8],0x03);
	writeToBuffer(30,18, pongMenu[6],0x07);
	writeToBuffer(30,20, Instruction[0],0x07);
	writeToBuffer(30,21, Instruction[1],0x07);
	writeToBuffer(30,22, Instruction[2],0x07);
	writeToBuffer(30,23, Instruction[3],0x07);
	flushBufferToConsole();
}

void score()
{
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[8],0x03);
	writeToBuffer(30,18, Instruction[0],0x07);
	writeToBuffer(30,19, Instruction[1],0x07);
	writeToBuffer(30,20, Instruction[2],0x07);
	writeToBuffer(30,21, Instruction[3],0x07);
	flushBufferToConsole();
}