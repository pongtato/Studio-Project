#include "SpawnEnemies.h"
#include "game.h"
#include "Shoot.h"
#include "leveldesign.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include "common.h"
#include <string>
#include "MainMenu.h"
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
unsigned int spawnno;
std::string tpatternfromtext;
std::string mpatternfromtext;
std::string bpatternfromtext;
std::string typefromtext;
std::string stagename;
std::string idfromtext;
using std::ostringstream;
unsigned int terrainfromtext = 100;

int statefromtext;
// CHOOSES AND READS FROM REQUIRED FILE
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
			if (typefromtext != "BOSS")
			{
				if (indata >> stagename >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext >> spawnno >> typefromtext >> combined.enemySettings.enemymovespeed >> combined.enemySettings.enemyshootspeedrange1 >> combined.enemySettings.enemyshootspeedrange2)
				{
				}
			}
			else
			{
				if (indata >> stagename >> activefromtext >> hpfromtext >> scorefromtext >> iconfromtext >> statefromtext >> spawnno >> typefromtext >> combined.enemySettings.bossmovespeed>> combined.enemySettings.bossshootspeed >> idfromtext)
				{
				}
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
	for (unsigned int i = 0; i  < spawnno; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			gotoXY(counter[i].coordinates.X--,counter[i].coordinates.Y);
		}
	}
}
void moveEnemiesUp()
{
	for (unsigned int i = 0; i  < spawnno; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y--);
		}
	}
}
void moveEnemiesDown()
{
	for (unsigned int i = 0; i  < spawnno; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
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
	for (unsigned int i = 0; i  < terrainfromtext; ++i)
	{
		//is enemy alive
		if(generator[i].Active)
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
	for (unsigned int i = 0; i  < terrainfromtext; ++i)
	{
		//is enemy alive
		if(generator2[i].Active)
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
	for (unsigned int i = 0; i < spawnno; ++i)
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
			writeToBuffer(counter[i].coordinates.X,counter[i].coordinates.Y-1,counter[i].toprow, 0x0D);
			writeToBuffer(counter[i].coordinates,counter[i].midrow, 0x0C);
			writeToBuffer(counter[i].coordinates.X,counter[i].coordinates.Y+1,counter[i].botrow, 0x0D);
			}
			if(counter[i].coordinates.X <=2)
			{
				counter[i].Active = false;
			    counter[i].icon = ' ';
				clearBuffer(0x0F);
				loseScreen();
				flushBufferToConsole();
				Sleep(3000);
				menuscreen();
			}
		}
		if(counter[i].coordinates.X <=1)
		{
			

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
		for(unsigned int i =0; i<spawnno;i++)
		{
			if(counter[i].Active)
			{
				if ( elapsedTime - timer_shoot >rand()%combined.enemySettings.enemyshootspeedrange1 + combined.enemySettings.enemyshootspeedrange2 )
				{
					timer_shoot = elapsedTime;
					if(combined.enemySettings.enemyCurrentMissile < combined.enemySettings.enemyMaxMissile)
					{
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
					else
					{
						combined.enemySettings.enemyCurrentMissile = 0;
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
				}
			}
		}
	}
	else
	{
		for(int i=0; i<1;i++)
		{
			if(counter[i].Active)
			{
				if ( elapsedTime - timer_shoot >combined.enemySettings.bossshootspeed)
				{
					timer_shoot = elapsedTime;
					if(combined.enemySettings.enemyCurrentMissile <combined.enemySettings.enemyMaxMissile)
					{
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
					}
					else
					{
						combined.enemySettings.enemyCurrentMissile = 0;
						enemyShootBullet1(combined.enemySettings.enemyCurrentMissile,counter[i].coordinates);
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
		if ( combined.terrainSettings.currentTerrain < terrainfromtext )
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
		else 
		{
			combined.terrainSettings.currentTerrain = 0;
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
		if ( combined.terrainSettings.currentTerrain < terrainfromtext )
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
	for (unsigned int i = combined.terrainSettings.terraingo; i < terrainfromtext; ++i)
	{
		//is terrain active?
		if(generator[i].Active)
		{
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
	for (unsigned int i = combined.terrainSettings.terraingobot; i < terrainfromtext; ++i)
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
// GETS WHICH LEVEL TO LOAD FROM TEXT
void levelCheck()
{
	int i = 0;
	std::ifstream indata2;
	indata2.open("GLD/Variables/LEVELS/STAGES.txt");
	if (combined.globalSettings.stage < 1)
	combined.globalSettings.stage++;
	for (i; indata2.good(); ++i)
	{
		 getline(indata2, combined.enemySettings.stagechecker[i]);
	}

	if (combined.enemySettings.stagechecker[combined.globalSettings.loadlevel] == "STAGE")
	{
		combined.globalSettings.stage++;
		combined.globalSettings.loadlevel++;
	}
	else if (combined.enemySettings.stagechecker[combined.globalSettings.loadlevel] == "STAGEEND")
	{
		stageclearscreen();
	}
	else if (combined.enemySettings.stagechecker[combined.globalSettings.loadlevel] == "END")
	{
		combined.globalSettings.stage++;
		combined.globalSettings.loadlevel++;
	}
}
// PRINT WAVE STATS TO THE GAME
void PrintWave()
{
	std::stringstream tempz;
	tempz << "ENEMY INFO";
	std::string resultz = tempz.str();
	writeToBuffer(50, 15, resultz, 0x0C);

	std::stringstream temp;
	temp << stagename;
	std::string result = temp.str();
	writeToBuffer(50, 17, result, 0x0C);

	std::stringstream temp2;
	temp2 << "HP: " << hpfromtext;
	std::string result2 = temp2.str();
	writeToBuffer(50, 19, result2, 0x0C);

	std::stringstream temp3;
	temp3 << "WORTH: " << scorefromtext;
	std::string result3 = temp3.str();
	writeToBuffer(50, 21, result3, 0x0C);
}
// PRINT STAGE STATS TO THE GAME
void PrintStage()
{
	std::stringstream stagetemp;
	stagetemp << "Stage" << ": " << combined.globalSettings.stage;
	std::string stage = stagetemp.str();
	writeToBuffer(50, 4, stage, 0x03);
}
// READ BOSS PATTERN FROM TEXT
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
