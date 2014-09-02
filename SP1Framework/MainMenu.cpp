#include "MainMenu.h"
#include "game.h"
#include <iostream>
#include "Framework\console.h"
#include <fstream>
#include <string>
#include "leveldesign.h"
#include <conio.h>  
#include "score.h"
#include "Player.h"
char c;
string Instruction[99] = {"ESC: Pause Screen", "Space: Shoot", "ArrowKeys: Move"};
string pongMenu[99] = {"1:","2:","3:", "4:",  /// 0 1 2 3
	                   "StartGame", "HighScores", "Instruction", "Exit",  // 4 5 6 7
	                   "Welcome to the Pongtato Invasion Game!!!", "Game Paused! Please Select your options.", "ResumeGame", "RestartGame", //8 9 10 11
                       "5:", "Stages", "Exit(Menu)"}; //12 13 14
string SelectStage[99] = {"0", "1:", "2:", "3:", "4:", "5:", "6:", "7","8","9","10","11","12","13"};
string StageInfo[99] = {"0", "Wave 1-3", "Boss1", "Bonus1", "Wave 4-6", "Boss2", "Bonus2"}; 

void introscreen()
{
	
	intro();
	selection();
}
void intro()
{
	clearBuffer(0x0F);
	mainScreenIntro();
	writeToBuffer(20,14,pongMenu[8],0x03);
	flushBufferToConsole(); Sleep(50);
	writeToBuffer(31,18,pongMenu[0],0x06);
	writeToBuffer(34,18,pongMenu[4],0x07);
	writeToBuffer(31,19,pongMenu[1],0x06);
	writeToBuffer(34,19,pongMenu[13],0x07);
	writeToBuffer(31,20,pongMenu[2],0x06);
	writeToBuffer(34,20,pongMenu[5],0x07);
	writeToBuffer(31,21,pongMenu[3],0x06);
	writeToBuffer(34,21,pongMenu[6],0x07);
	writeToBuffer(31,22,pongMenu[12],0x06);
	writeToBuffer(34,22,pongMenu[7],0x07);
	flushBufferToConsole();

}

void menuscreen()
{
	mainmenu();
	selection();
}
void mainmenu()
{
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[8],0x03);
	writeToBuffer(31,18,pongMenu[0],0x06);
	writeToBuffer(34,18,pongMenu[4],0x07);
	writeToBuffer(31,19,pongMenu[1],0x06);
	writeToBuffer(34,19,pongMenu[13],0x07);
	writeToBuffer(31,20,pongMenu[2],0x06);
	writeToBuffer(34,20,pongMenu[5],0x07);
	writeToBuffer(31,21,pongMenu[3],0x06);
	writeToBuffer(34,21,pongMenu[6],0x07);
	writeToBuffer(31,22,pongMenu[12],0x06);
	writeToBuffer(34,22,pongMenu[7],0x07);
	flushBufferToConsole();
}
void selection()
{
	c = _getch();
	switch (c)
	{
	case '1': 
		restartGame();
		playGameSound(S_SELECT);
		combined.globalSettings.selection = '1';
		planeselection();
		mainLoop();
		break;

	case '2':
		playGameSound(S_SELECT);
		combined.globalSettings.selection = '2';
		stagemenu();
		stageselection();
		break;

	case '3':
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		score();
		c = '0';
		c = _getch();

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
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		instructions();
		c = '0';
		c = _getch();
		if ( c = 27 )
		{
			menuscreen();
		}

		else
		{
			menuscreen();
		}
		break;

	case '5':
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		exitScreen();
		flushBufferToConsole();	
		Sleep(1200);
		exit( 0 );
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
	flushBufferToConsole();
}
void score()
{
	clearBuffer(0x0F);
	mainScreen();
	writeToBuffer(20,14,pongMenu[8],0x03);
	writeToBuffer(32, 18, pongMenu[5], 0x07);
	print();
	flushBufferToConsole();
}
void planeselection()
{
	
	
	clearBuffer(0x0F);
	planeScreen();
	flushBufferToConsole();

	c = _getch();
	
	switch (c)
	{
	case '1':
		playGameSound(S_SELECT);
		loadPlayerFromText();  
		break;

	case '2': 
		playGameSound(S_SELECT);
		loadPlayer2FromText();  
		break;

	default: 
		playGameSound(S_SELECT);
		menuscreen();
		break;
	}
}


void pausescreen()
{
	pausemenu();
	pSelection();
}
void pausemenu()
{
	clearBuffer(0x0F);
	pauseScreen();
	writeToBuffer(20,14,pongMenu[9],0x03);
	writeToBuffer(31,18,pongMenu[0],0x06);
	writeToBuffer(34,18,pongMenu[11],0x07);
	writeToBuffer(31,19,pongMenu[1],0x06);
	writeToBuffer(34,19,pongMenu[10],0x07);
	writeToBuffer(31,20,pongMenu[2],0x06);
	writeToBuffer(34,20,pongMenu[5],0x07);
	writeToBuffer(31,21,pongMenu[3],0x06);
	writeToBuffer(34,21,pongMenu[6],0x07);
	writeToBuffer(31,22,pongMenu[12],0x06);
	writeToBuffer(34,22,pongMenu[14],0x07);
	flushBufferToConsole();
}
void pSelection()
{
	c = _getch();
	playGameSound(S_SELECT);
	switch (c)
	{
	case '1':
		playGameSound(S_SELECT);
		restartGame();
		clearBuffer(0x0F);
		mainLoop();
		break;



	case '2': 
		playGameSound(S_SELECT);
		mainLoop();
		break;

	case '3':
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		pScore();
		c = '0';
		c = _getch();

		if ( c = 27 )
		{
			pausescreen();
		}

		else
		{
			pausescreen();
		}

		break;

	case '4':
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		pInstructions();
		c = '0';
		c = _getch();
		if ( c = 27 )
		{
			pausescreen();
		}

		else
		{
			pausescreen();
		}
		break;

	case '5':
		playGameSound(S_SELECT);
		clearBuffer(0x0F);
		returntomenu();
		flushBufferToConsole();	
		Sleep(1000);
		introscreen();
		break;

	default:
		clearBuffer(0x0F);
		pausescreen();
		break;
	}
}
void pInstructions()
{
	clearBuffer(0x0F);
	pauseScreen();
	writeToBuffer(20,14,pongMenu[9],0x03);
	writeToBuffer(30,18, pongMenu[6],0x07);
	writeToBuffer(30,20, Instruction[0],0x07);
	writeToBuffer(30,21, Instruction[1],0x07);
	writeToBuffer(30,22, Instruction[2],0x07);
	flushBufferToConsole();
}
void pScore()
{
	clearBuffer(0x0F);
	pauseScreen();
	writeToBuffer(20,14,pongMenu[9],0x03);
	writeToBuffer(32, 18, pongMenu[5], 0x07);
	print();
	flushBufferToConsole();
}

void stageselection()
{
	c = _getch();
	
	switch (c)
	{
	case '1': 
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 1;
		mainLoop();
		break;

	case '2':
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 4;
		mainLoop();
		break;

	case '3':
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 5;
		mainLoop();
		break;

	case '4':
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 7;
		mainLoop();
		break;

	case '5':
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 10;
		mainLoop();
		break;

	case '6':
		playGameSound(S_SELECT);
		restartGame();
		planeselection();
		combined.globalSettings.loadlevel = 11;
		mainLoop();
		break;

	default:
		clearBuffer(0x0F);
		menuscreen();
		break;
	}
}
void stagemenu()
	{
		clearBuffer(0x0F);
		stagesScreen();	
		writeToBuffer(11,8,SelectStage[1],0x06);
		writeToBuffer(13,8,StageInfo[1],0x07);
		writeToBuffer(11,9,SelectStage[2],0x06);
		writeToBuffer(13,9,StageInfo[2],0x07);
		writeToBuffer(11,10,SelectStage[3],0x06);
		writeToBuffer(13,10,StageInfo[3],0x07);
		writeToBuffer(11,11,SelectStage[4],0x06);
		writeToBuffer(13,11,StageInfo[4],0x07);
		writeToBuffer(11,12,SelectStage[5],0x06);
		writeToBuffer(13,12,StageInfo[5],0x07);
		writeToBuffer(11,13,SelectStage[6],0x06);
		writeToBuffer(13,13,StageInfo[6],0x07);

	
		flushBufferToConsole();
	}