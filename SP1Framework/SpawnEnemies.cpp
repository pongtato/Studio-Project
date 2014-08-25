#include "SpawnEnemies.h"
#include "game.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>

ENEMY counter[999];
ENEMY powerup[1];
BOSS Bcounter[10];
//top terrain
WORLD generator[999];
//bottom terrain
WORLD generator2[999];
extern GLOBAL combined;
extern double elapsedTime;
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
		indata.open("GLD/Variables/enemy2.txt");
		break;
	case 3:	
		indata.open("GLD/Variables/enemy3.txt");
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

void bonusesloadfromtext(int loadcase)
{
	std::ifstream indata;
	switch (loadcase)
	{
	case 5:
		indata.open("GLD/Variables/Bonus1.txt");
		break;
	}
	if ( indata.is_open())
	{
			if (indata >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext)
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

void SpawnBonus(unsigned int &currentEnemy, int modX, int modY)
{
	counter[currentEnemy].Active = activefromtext;
	counter[currentEnemy].coordinates.X = modX;
	counter[currentEnemy].coordinates.Y = modY;
	counter[currentEnemy].hp = hpfromtext;
	counter[currentEnemy].score = scorefromtext;
	counter[currentEnemy].icon = (char)(iconfromtext);
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = statefromtext;
	currentEnemy++;
}

void SpawnTerrain(unsigned int &currentTerrain, int terrainModX, int terrainModY, int terrainChar)
{
	generator[currentTerrain].icon = terrainChar;
	generator[currentTerrain].coordinates.X = terrainModX;
	generator[currentTerrain].coordinates.Y = terrainModY;
	generator[currentTerrain].level = 2;
	generator[currentTerrain].Active = true;
	currentTerrain++;
}

void moveTerrain()
{
	for ( int i = 0; i  < TERRAIN; ++i)
	{
		//is enemy alive
		if(generator[i].Active == true)
		{
			gotoXY(generator[i].coordinates.X--,generator[i].coordinates.Y);
		}
	}
}

void SpawnTerrainBot(unsigned int &currentTerrainBot, int terrainModX, int terrainBotModY, int terrainChar)
{
	generator2[currentTerrainBot].icon = terrainChar;
	generator2[currentTerrainBot].coordinates.X = terrainModX;
	generator2[currentTerrainBot].coordinates.Y = terrainBotModY;
	generator2[currentTerrainBot].level = 22;
	generator2[currentTerrainBot].Active = true;
	currentTerrainBot++;
}

void moveTerrainBot()
{
	for ( int i = 0; i  < TERRAIN; ++i)
	{
		//is enemy alive
		if(generator2[i].Active == true)
		{
			gotoXY(generator2[i].coordinates.X--,generator2[i].coordinates.Y);
		}
	}
}

void enemySpawn()
{
	// spawn enemies
	if ( combined.enemySettings.modifyX <48)
		{
			static double timer_spawn = elapsedTime;
			if ( elapsedTime - timer_spawn > 0.1 )
			{
				timer_spawn = elapsedTime;
				if ( combined.enemySettings.currentEnemy < NO_OF_ENEMIES )
				{
					SpawnEnemy(combined.enemySettings.currentEnemy,combined.enemySettings.modifyX,combined.enemySettings.modifyY);
					combined.enemySettings.spawncounter++;
					combined.enemySettings.moveState = 1;
					//per row
					if ( combined.enemySettings.modifyY < 14)
					{
						combined.enemySettings.modifyY=combined.enemySettings.modifyY+2;
					}
					//next row and spawn interval
					else
					{
						combined.enemySettings.modifyY = 6;	
						combined.enemySettings.modifyX = combined.enemySettings.modifyX + 2;
					}
				}
			}
		}
	else if ( combined.enemySettings.wew != 0)
		{
			combined.enemySettings.moveState=2;
			combined.enemySettings.spawnclear=0;
		}
}












