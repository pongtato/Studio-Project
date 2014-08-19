#ifndef _SPAWNENEMIES_H
#define _SPAWNENEMIES_H

#include "Framework\console.h"
#include <string>


struct ENEMY
{
	std::string name;
	COORD corrdinates;
	bool Active;
	int number;
	int score;
};



#endif // _SPAWNENEMIES_H

