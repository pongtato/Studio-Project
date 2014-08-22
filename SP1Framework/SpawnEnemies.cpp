#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>



ENEMY counter[999];
BOSS Bcounter[10];
int enemycounter;
int activefromtext;
int hpfromtext;
int scorefromtext;
int iconfromtext;

//boss icon
int Bossfromtext;
int BossfromtextL;	// left
int BossfromtextR;	// right
int BossfromtextTL;	// top left
int BossfromtextTR;	// top right
int BossfromtextBL;	// bottom left
int BossfromtextBR;	//botom right
int BossfromtextU;	//up
int BossfromtextD; //down

int statefromtext;

void loadfromtext(int loadcase)
{
	std::ifstream indata;
	switch (loadcase)
	{
	case 1:	
		indata.open("GLD/Variables/enemy1.txt");
		break;
	case 2:	
		indata.open("GLD/Variables/enemy1.txt");
		break;
	case 3:	
		indata.open("GLD/Variables/enemy1.txt");
		break;
	}
	if ( indata.is_open())
	{
		if (indata >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext)
		{

		}
	}
}

void loadbossfromtext(int loadcase)
{

	std::ifstream indata;
	switch (loadcase)
	{
	case 4:	
		indata.open("GLD/Variables/boss1.txt");
		break;
	}
	if ( indata.is_open())
	{
		if (indata >> activefromtext >> hpfromtext >> scorefromtext >> BossfromtextTL >> BossfromtextU >> 
			BossfromtextTR >> BossfromtextL >> Bossfromtext >> BossfromtextR >> BossfromtextBL >> BossfromtextD >>
			BossfromtextBR >>  statefromtext)
		{
		}
	}
}

void moveEnemies()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X--,counter[i].coordinates.Y);
		}
	}
}

void moveEnemiesUp()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);
		}
	}
}

void moveEnemiesDown()
{
	for ( int i = 0; i  < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
		}
	}
}

void moveBoss()
{
	for ( int i = 0; i  < BOSS_NO; ++i)
	{
		//is enemy alive
		if(Bcounter[i].Active == true)
		{
			gotoXY(Bcounter[i].coordinates.X--,Bcounter[i].coordinates.Y);
		}
	}
}

void moveBossUp()
{
	for ( int i = 0; i  < BOSS_NO; ++i)
	{
		//is enemy alive
		if(Bcounter[i].Active == true)
		{
			gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y--);
		}
	}
}

void moveBossDown()
{
	for ( int i = 0; i  < BOSS_NO; ++i)
	{
		//is enemy alive
		if(Bcounter[i].Active == true)
		{
			gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y++);
		}
	}
}

void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY)
{
	enemycounter = 10;
	counter[currentEnemy].Active = activefromtext;
	counter[currentEnemy].coordinates.X = modX;
	counter[currentEnemy].coordinates.Y = modY;
	counter[currentEnemy].hp= hpfromtext;
	counter[currentEnemy].score= scorefromtext;
	counter[currentEnemy].icon= (char)(iconfromtext);
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = statefromtext;
	currentEnemy++;
}

void SpawnBoss(unsigned int &currentEnemy, int modX, int modY)
{
	enemycounter = 10;
	Bcounter[currentEnemy].Active = activefromtext;
	Bcounter[currentEnemy].coordinates.X = modX;
	Bcounter[currentEnemy].coordinates.Y = modY;
	Bcounter[currentEnemy].hp= hpfromtext;
	Bcounter[currentEnemy].score= scorefromtext;
	Bcounter[currentEnemy].icontopleft= (char)(BossfromtextTL);
	Bcounter[currentEnemy].iconup= (char)(BossfromtextU);
	Bcounter[currentEnemy].icontopright= (char)(BossfromtextTR);
	Bcounter[currentEnemy].iconleft= (char)(BossfromtextL);
	Bcounter[currentEnemy].iconcenter= (char)(Bossfromtext);
	Bcounter[currentEnemy].iconright= (char)(BossfromtextR);
	Bcounter[currentEnemy].iconbottomleft= (char)(BossfromtextBL);
	Bcounter[currentEnemy].icondown= (char)(BossfromtextD);
	Bcounter[currentEnemy].iconbottomright= (char)(BossfromtextBR);
	Bcounter[currentEnemy].number = currentEnemy;
	Bcounter[currentEnemy].state = statefromtext;
	currentEnemy++;
}









