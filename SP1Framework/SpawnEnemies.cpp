#include "SpawnEnemies.h"
#include "game.h"
#include "Shoot.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "common.h"
#include <string>
ENEMY powerup[1];
ENEMY counter[999];
//top terrain
WORLD generator[999];
//bottom terrain
WORLD generator2[999];
extern GLOBAL combined;
extern double elapsedTime;
extern ENEMY currentEnemy;
int enemycounter;
int activefromtext;
int hpfromtext;
int scorefromtext;
int iconfromtext;
int spawnno;
std::string tpatternfromtext;
std::string mpatternfromtext;
std::string bpatternfromtext;
std::string typefromtext;
std::string stagename;
std::string idfromtext;
using std::ostringstream;


int statefromtext;

void loadfromtext(int loadcase)
{
	std::stringstream s;
	s << "GLD/Variables/LEVELS/"<< combined.enemySettings.stagechecker[combined.globalSettings.loadlevel] << ".txt";
	std::string result = s.str();
	int i = 1;
	std::ifstream indata;
		//indata.open(intandtext);
		indata.open(result);
	if ( indata.is_open())
	{
		if (indata >> stagename >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext >> spawnno >> typefromtext >> idfromtext)
		{
		}
	}

	if (typefromtext == "BOSS")
	{
		std::stringstream bosstemp;
		bosstemp << "GLD/Variables/LEVELS/" << idfromtext << "PATTERN.txt";
		std::string final = bosstemp.str();
		bossPattern(final);
	}
}
void moveEnemies()
{
	for ( int i = 0; i  < spawnno; ++i)
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
	for ( int i = 0; i  < spawnno; ++i)
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
	for ( int i = 0; i  < spawnno; ++i)
	{
		//is enemy alive
		if(counter[i].Active == true)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y++);
		}
	}
}
void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY)
{
	if(typefromtext != "BOSS")
	{
	counter[currentEnemy].Active = activefromtext;
	counter[currentEnemy].coordinates.X = modX;
	counter[currentEnemy].coordinates.Y = modY;
	counter[currentEnemy].hp= hpfromtext;
	counter[currentEnemy].score= scorefromtext;
	counter[currentEnemy].icon= (char)(iconfromtext);
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = statefromtext;
	}
	else
	{
	counter[currentEnemy].Active = activefromtext;
	counter[currentEnemy].coordinates.X = modX;
	counter[currentEnemy].coordinates.Y = modY;
	counter[currentEnemy].hp= hpfromtext;
	counter[currentEnemy].score= scorefromtext;
	counter[currentEnemy].toprow= tpatternfromtext;
	counter[currentEnemy].midrow= mpatternfromtext;
	counter[currentEnemy].botrow= bpatternfromtext;
	counter[currentEnemy].number = currentEnemy;
	counter[currentEnemy].state = statefromtext;
	}
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
	if(typefromtext != "BOSS")
	{
		// spawn enemies
		static double timer_spawn = elapsedTime;
		if ( elapsedTime - timer_spawn > 0.1 )
		{
			timer_spawn = elapsedTime;
			if ( combined.enemySettings.currentEnemy < spawnno )
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

			else if ( combined.enemySettings.wew != 0)
			{
				combined.enemySettings.moveState=2;
				combined.enemySettings.spawnclear=0;
			}
		}
	}
	else
	{
		if ( combined.enemySettings.modifyX <39)
		{
			static double timer_spawn = elapsedTime;
			if ( elapsedTime - timer_spawn > 0.1 )
			{
				timer_spawn = elapsedTime;
				if ( combined.enemySettings.currentEnemy < spawnno )
				{
					SpawnEnemy(combined.enemySettings.currentEnemy,combined.enemySettings.modifyX,combined.enemySettings.modifyY);
					combined.enemySettings.spawnclear=0;
					combined.enemySettings.moveState = 1;
					combined.enemySettings.modifyY = 10;
					combined.enemySettings.modifyX = combined.enemySettings.modifyX + 2;
				}
			}
		}
		else if ( combined.enemySettings.wew != 0)
		{
			combined.enemySettings.moveState=2;
			combined.enemySettings.spawnclear=0;
		}
	}
}
void renderEnemies()
{
	// render enemies
	for ( int i = 0; i < spawnno; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			/*gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;*/
			if (typefromtext != "BOSS")
			{
			writeToBuffer(counter[i].coordinates,counter[i].icon);
			}
			else
			{
			writeToBuffer(counter[i].coordinates.X,counter[i].coordinates.Y-1,counter[i].toprow);
			writeToBuffer(counter[i].coordinates,counter[i].midrow);
			writeToBuffer(counter[i].coordinates.X,counter[i].coordinates.Y+1,counter[i].botrow);
			}
		}
		if(counter[i].coordinates.X <=2)
		{
			counter[i].Active = false;
			counter[i].icon = ' ';
		}
	}
}
void enemyMove()
{
	//check if row has spawned
	if ( combined.enemySettings.spawncounter >=5)
	{
		combined.enemySettings.spawncounter = 0;
		combined.enemySettings.spawnclear = 0;
	}
	//clear to move
	else if ( combined.enemySettings.spawncounter = 0)
	{
		combined.enemySettings.spawnclear = 1;
	}
	if (typefromtext != "BOSS")
	{
		// move enemies
		if ( combined.enemySettings.spawnclear == 0)
		{
			static double timer_move = elapsedTime;
			if ( elapsedTime - timer_move > combined.enemySettings.enemymovespeed )
			{
				timer_move = elapsedTime;
				if (combined.enemySettings.moveState == 1)
				{
					//move towards left
					moveEnemies();
				}
				else if ( combined.enemySettings.moveState == 2)
				{
					//move upwards
					moveEnemiesUp();
					combined.enemySettings.moveYUP--;
					combined.enemySettings.moveYDOWN = combined.enemySettings.moveYUP;
					if (combined.enemySettings.moveYUP < 6)
					{
						combined.enemySettings.wew = 0;
						combined.enemySettings.moveState = 3;
						moveEnemies();
					}
				}
				else if (combined.enemySettings.moveState == 3)
				{
					moveEnemiesDown();
					combined.enemySettings.moveYDOWN++;
					if (combined.enemySettings.moveYDOWN > 10)
					{
						combined.enemySettings.moveYUP = combined.enemySettings.moveYDOWN;
						combined.enemySettings.moveState = 2;
						moveEnemies();
					}
				}
			}
		}
	}
	else
	{
		static double timer_move = elapsedTime;
		if ( elapsedTime - timer_move > combined.enemySettings.enemymovespeed )
		{
			timer_move = elapsedTime;
			if (combined.enemySettings.moveState == 1)
			{
				//move towards left
				moveEnemies();
			}
			else if ( combined.enemySettings.moveState == 2)
			{
				//move upwards
				moveEnemiesUp();
				combined.enemySettings.moveYUP--;
				combined.enemySettings.moveYDOWN = combined.enemySettings.moveYUP;
				if (combined.enemySettings.moveYUP < 7)
				{
					combined.enemySettings.wew = 0;
					combined.enemySettings.moveState = 3;
					moveEnemies();
				}
			}
			else if (combined.enemySettings.moveState == 3)
			{
				moveEnemiesDown();
				combined.enemySettings.moveYDOWN++;
				if (combined.enemySettings.moveYDOWN > 17)
				{
					combined.enemySettings.moveYUP = combined.enemySettings.moveYDOWN;
					combined.enemySettings.moveState = 2;
					moveEnemies();
				}
			}
		}
	}

}
void enemyShooting()
{
	//Enemy shooting
	static double timer_shoot = elapsedTime;
	if (typefromtext != "BOSS")
	{
		for(int i =0; i<spawnno;i++)
		{
			if(counter[i].Active)
			{
				if ( elapsedTime - timer_shoot >rand()%combined.enemySettings.enemyshootspeedrange1 + combined.enemySettings.enemyshootspeedrange2 )
				{
					timer_shoot = elapsedTime;
					if(combined.enemySettings.enemyCurrentMissile < 50)
					{
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
					else
					{
						enemyShootBullet2(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
				}
			}
		}
	}
	else
	{
		for(int i =0; i<spawnno;i++)
		{
			if(counter[i].Active)
			{
				if ( elapsedTime - timer_shoot >combined.enemySettings.bossshootspeed)
				{
					timer_shoot = elapsedTime;
					if(combined.enemySettings.enemyCurrentMissile < 50)
					{
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
					else
					{
						enemyShootBullet2(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
				}
			}
		}
	}
}
// RANDOMLY GENERATED TERRAIN TOP
void FormTerrain() 
{
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 0.2 )
	{
		timer_spawn = elapsedTime;
		if ( combined.terrainSettings.currentTerrain < TERRAIN )
		{
			SpawnTerrain(combined.terrainSettings.currentTerrain,combined.terrainSettings.terrainModX,combined.terrainSettings.terrainModY, combined.terrainSettings.terrainicon);
			if ( combined.terrainSettings.terrainModY < 3)
			{
				if ( rand()%2+1 == 1)
				{
				combined.terrainSettings.terrainModY++;
				}
			}
			else if ( combined.terrainSettings.terrainModY == 3)
			{
				if ( rand()%3+1 == 1)
				{
					combined.terrainSettings.terrainModY--;
				}
				else if ( rand()%3+1 == 3)
				{
					combined.terrainSettings.terrainModY++;
				}
			}
			else if ( combined.terrainSettings.terrainModY == 4)
			{
				if ( rand()%2+1 == 1)
				{
				combined.terrainSettings.terrainModY--;
				}
			}
		}
	}	

}
// RANDOMLY GENERATED TERRAIN BOT
void FormTerrainBot() 
{
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 0.2 )
	{
		timer_spawn = elapsedTime;
		if ( combined.terrainSettings.currentTerrain < TERRAIN )
		{
			SpawnTerrainBot(combined.terrainSettings.currentTerrain,combined.terrainSettings.terrainModX, combined.terrainSettings.terrainBotModY, combined.terrainSettings.terrainicon);
			if ( combined.terrainSettings.terrainBotModY > 21)
			{
				if ( rand()%2+1 == 1)
				{
					combined.terrainSettings.terrainBotModY--;
				}
			}
			else if ( combined.terrainSettings.terrainBotModY == 21)
			{
				if ( rand()%3+1 == 1)
				{
					combined.terrainSettings.terrainBotModY++;
				}
				else if ( rand()%3+1 == 3)
				{
					combined.terrainSettings.terrainBotModY --;
				}
			}
			else if ( combined.terrainSettings.terrainBotModY == 20)
			{
				if ( rand()%2+1 == 1)
				{
					combined.terrainSettings.terrainBotModY++;
				}
			}
		}
	}	

}
// RENDER TERRAIN
void renderTerrain()
{
	// render top terrain
	for ( int i = combined.terrainSettings.terraingo; i < TERRAIN; ++i)
	{
		//is terrain active?
		if(generator[i].Active)
		{
			/*gotoXY(generator[i].coordinates.X,generator[i].coordinates.Y);
			std::cout << generator[i].icon;*/
			writeToBuffer(generator[i].coordinates,generator[i].icon,0x0F);
		}
		if(generator[i].coordinates.X <=1)
		{
			generator[i].Active = false;
			generator[i].icon = ' ';
			combined.terrainSettings.terraindestory++;
		}
	}

	// render bot terrain
	for ( int i = combined.terrainSettings.terraingobot; i < TERRAIN; ++i)
	{
		//is terrain bot active?
		if(generator2[i].Active)
		{
			/*gotoXY(generator2[i].coordinates.X,generator2[i].coordinates.Y);
			std::cout << generator2[i].icon;*/
			writeToBuffer(generator2[i].coordinates,generator2[i].icon,0x0F);
		}
		if(generator2[i].coordinates.X <=1)
		{
			generator2[i].Active = false;
			generator2[i].icon = ' ';
			combined.terrainSettings.terraindestorybot++;
		}
	}

	//terrain top reset
	if (combined.terrainSettings.terraindestory >= 10)
	{
		combined.terrainSettings.terraingo = 0;
	}

	//terrain bot reset
	if (combined.terrainSettings.terraindestorybot >= 10)
	{
		combined.terrainSettings.terraingobot = 0;
	}
}
// SCROLL TERRAIN
void terrainMove()
{
	static double timer_move = elapsedTime;
	if ( elapsedTime - timer_move > 0.2 )
	{
		timer_move = elapsedTime;
		{
			//move towards left
			moveTerrain();
			moveTerrainBot();
		}
	}
}
void levelCheck()
{
	std::ifstream indata2;
	indata2.open("GLD/Variables/LEVELS/STAGES.txt");
	if (combined.globalSettings.stage < 1)
	combined.globalSettings.stage++;
	for ( int i = 0; indata2.good(); ++i)
	{
		 getline(indata2, combined.enemySettings.stagechecker[i]);
	}

	if (combined.enemySettings.stagechecker[combined.globalSettings.loadlevel] == "STAGE")
	{
		combined.globalSettings.stage++;
		combined.globalSettings.loadlevel++;
	}
}
void PrintWave()
{
	std::stringstream temp;
	temp << stagename;
	std::string result = temp.str();
	writeToBuffer(50, 5, result, 0x0C);
}
void PrintStage()
{
	std::stringstream stagetemp;
	stagetemp << "Stage" << ": " << combined.globalSettings.stage;
	std::string stage = stagetemp.str();
	writeToBuffer(50, 4, stage, 0x03);
}
void bossPattern(std::string input)
{
	std::ifstream indata3;
	indata3.open(input);
	for ( int i = 0; indata3.good(); ++i)
	{
		 getline(indata3, combined.enemySettings.bosschecker[i]);
	}
	tpatternfromtext = combined.enemySettings.bosschecker[0];
	mpatternfromtext = combined.enemySettings.bosschecker[1];
	bpatternfromtext = combined.enemySettings.bosschecker[2];	
}
