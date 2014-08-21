#ifndef _MAINMENU_H
#define _MAINMENU_H

void menuscreen();
void menuscreen2();
void instructions();
void score();

enum MainMenu
{
	PLAYGAME,
	SCORE,
	INSTRUCTION,
	EXITGAME
};

#endif