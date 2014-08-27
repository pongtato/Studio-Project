#include "SpawnEnemies.h"
#include "game.h"
#include "Shoot.h"
#include "Framework\console.h"
#include <iomanip>
#include <iostream>
#include <sstream>

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
	std::stringstream s;
	s << "GLD/Variables/LEVELS/"<< combined.enemySettings.spawnlevel << combined.globalSettings.lvl << ".txt";
	std::string result = s.str();
	int i = 1;
	std::ifstream indata;
		//indata.open(intandtext);
		indata.open(result);
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

void renderEnemies()
{
	// render enemies
	for ( int i = 0; i < NO_OF_ENEMIES; ++i)
	{
		//is enemy alive
		if(counter[i].Active)
		{
			/*gotoXY(counter[i].coordinates.X,counter[i].coordinates.Y);
			std::cout << counter[i].icon;*/
			writeToBuffer(counter[i].coordinates,counter[i].icon);
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

void enemyShooting()
{
	//Enemy shooting
	static double timer_shoot = elapsedTime;
	for(int i =0; i<NO_OF_ENEMIES;i++)
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
	for ( int i = 0; indata2.good(); ++i)
	{
		getline(indata2, combined.enemySettings.stagechecker[i]);
	}

	if (combined.enemySettings.stagechecker[(combined.globalSettings.loadlevel)] == "STAGE")
	{
		combined.globalSettings.stage++;
	}
	else if (combined.enemySettings.stagechecker[(combined.globalSettings.loadlevel)] == "WAVE" )
	{
		combined.globalSettings.lvl++;
		combined.enemySettings.spawnlevel = "enemy";
	}
	else if ( combined.enemySettings.stagechecker[(combined.globalSettings.loadlevel)] == "BOSS" )
	{
		combined.globalSettings.boss++;
		combined.enemySettings.spawnlevel = "boss";
	}
	else if (combined.enemySettings.stagechecker[(combined.globalSettings.loadlevel)] == "BONUS" )
	{
		combined.globalSettings.bonus++;
		combined.enemySettings.spawnlevel = "bonus";
	}
}

//// BOSS
//void renderBoss()
//{
//	//enemycolour();
//	// render boss
//	for ( int i = 0; i < BOSS_NO; ++i)
//	{
//		//is boss alive
//		if(Bcounter[i].Active)
//		{
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].icontopleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y-1,Bcounter[i].iconbottomleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].iconup;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y-1,Bcounter[i].iconup,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y-1);
//			std::cout << Bcounter[i].icontopright;*/
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y-1,Bcounter[i].icontopright,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y,Bcounter[i].iconleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconcenter;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y,Bcounter[i].iconcenter,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y);
//			std::cout << Bcounter[i].iconright;*/
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y,Bcounter[i].iconright,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y+1);
//			std::cout << Bcounter[i].iconbottomleft;*/
//			writeToBuffer(Bcounter[i].coordinates.X-1,Bcounter[i].coordinates.Y+1,Bcounter[i].iconbottomleft,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y+1);
//			std::cout << Bcounter[i].icondown;*/
//			writeToBuffer(Bcounter[i].coordinates.X,Bcounter[i].coordinates.Y+1,Bcounter[i].icondown,0x0F);
//			/*gotoXY(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y+1); 
//			std::cout << Bcounter[i].iconbottomright; */
//			writeToBuffer(Bcounter[i].coordinates.X+1,Bcounter[i].coordinates.Y+1,Bcounter[i].iconbottomright,0x0F);
//		}
//		if(Bcounter[i].coordinates.X <=2)
//		{
//			Bcounter[i].Active = false;
//			Bcounter[i].icontopleft = ' ';
//			Bcounter[i].iconup = ' ';
//			Bcounter[i].icontopright = ' ';
//			Bcounter[i].iconleft = ' ';
//			Bcounter[i].iconcenter = ' ';
//			Bcounter[i].iconright = ' ';
//			Bcounter[i].iconbottomleft = ' ';
//			Bcounter[i].icondown = ' ';
//			Bcounter[i].iconbottomright = ' ';
//		}
//	}
//}
//// POWER UPS
// BOSS MOVE
//void bossMove()
//{
//
//	// move boss
//	if ( spawnclear == 0)
//	{
//		static double timer_move = elapsedTime;
//		if ( elapsedTime - timer_move > bossmovespeed )
//		{
//			timer_move = elapsedTime;
//			if (moveState == 1)
//			{
//				//move towards left
//				moveBoss();
//			}
//			else if ( moveState == 2)
//			{
//				//move upwards
//				moveBossUp();
//				moveYUP--;
//				moveYDOWN = moveYUP;
//				if (moveYUP < 6)
//				{
//					wew = 0;
//					moveState = 3;
//					moveEnemies();
//				}
//			}
//			else if ( moveState == 3)
//			{
//				moveBossDown();
//				moveYDOWN++;
//				if (moveYDOWN > 16)
//				{
//					moveYUP = moveYDOWN;
//					moveState = 2;
//					moveEnemies();
//				}
//			}
//		}
//	}
//}

// SPAWN ENEMIES
// SPAWN BOSS
//
//void bossSpawn()
//{
//		// spawn enemies
//		if ( modifyX <39)
//		{
//			static double timer_spawn = elapsedTime;
//			if ( elapsedTime - timer_spawn > 0.1 )
//			{
//				timer_spawn = elapsedTime;
//				if ( currentEnemy < BOSS_NO )
//				{
//					SpawnBoss(currentEnemy,modifyX,modifyY);
//					spawnclear = 0;
//					moveState = 1;
//					modifyY = 10;	
//					modifyX = modifyX + 2;
//				}
//			}
//		}
//		else if ( wew != 0)
//		{
//			moveState=2;
//			spawnclear = 0;
//		}
//}
//// SPAWN BONUS
//
//void bonusSpawn()
//{
//	//spawn enemines
//	if (combined.enemySettings.modifyX < 48)
//	{
//		static double timer_spawn = elapsedTime;
//		if (elapsedTime - timer_spawn > 0.1)
//		{
//			timer_spawn = elapsedTime;
//			if (combined.enemySettings.currentEnemy < BONUS)
//			{
//				SpawnBonus(currentEnemy, modifyX,combined.enemySettings.modifyY);
//				combined.enemySettings.spawncounter++;
//				//per row
//				combined.enemySettings.moveState = 1;
//				if (modifyY < 14)
//				{
//					modifyY = modifyY + 2;
//				}
//				else
//				{
//					modifyY = 6;	
//					modifyX = modifyX + 2;
//				}
//			}
//		}
//	}
//	else if (combined.enemySettings.wew != 0)
//	{
//		combined.enemySettings.moveState = 2;
//		combined.enemySettings.spawnclear = 0;
//	}
//}
////BOSS SHOOTS
//
//void bossShooting()
//{
//	//Enemy shooting
//	static double timer_shoot = elapsedTime;
//	for(int i =0; i<BOSS_NO;i++)
//	{
//		if(Bcounter[i].Active)
//		{
//			if ( elapsedTime - timer_shoot >bossshootspeed)
//			{
//				timer_shoot = elapsedTime;
//				if(enemyCurrentMissile < 50)
//				{
//					enemyShootBullet1(enemyCurrentMissile,Bcounter[i].coordinates);
//				}
//				else
//				{
//					enemyShootBullet2(enemyCurrentMissile,Bcounter[i].coordinates);
//				}
//			}
//		}
//	}
//}

// GAME SETTINGS
// VARIABLES FOR GLOBAL STRUCT














