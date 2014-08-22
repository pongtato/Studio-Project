#ifndef _PLAYER_H
#define _PLAYER_H


#include <string>
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
	int hp;
};

void loadPlayerFromText();

#endif // _PLAYER_H