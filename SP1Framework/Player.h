#ifndef _PLAYER_H
#define _PLAYER_H
#include <iostream>
#include <fstream>
#include "Framework\console.h"

struct PLAYER
{
	char icon;
	char headIcon;
	char wingIcon;
	char playerMissleIcon;
	COORD coordinates;
	int Active;
	int PowerUp;
	int Special;
};

struct SHIELD
{
	char icon;
	int hp;
	bool Active;
	COORD coordinates;
};

void loadPlayerFromText();
void PrintSpecial();
void renderShield();
void initshieldVar();
void useSpecial();

#endif // _PLAYER_H