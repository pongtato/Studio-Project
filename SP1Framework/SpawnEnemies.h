#ifndef _SPAWNENEMIES_H
#define _SPAWNENEMIES_H

#include "Framework\console.h"
#include <fstream>
#include <string>



struct ENEMY
{
	std::string name;
	char icon;
	COORD coordinates;
	int Active;
	int hp;
	int score;
	int number;
	int state;
	
};

struct BOSS
{
	std::string name;
	char iconcenter;
	char iconleft;
	char icontopleft;
	char iconright;
	char icontopright;
	char iconbottomright;
	char iconbottomleft;
	char iconup;
	char icondown;
	COORD coordinates;
	int Active;
	int hp;
	int score;
	int number;
	int state;
	
};
void moveBoss();
void moveBossUp();
void moveBossDown();
void moveEnemies();
void moveEnemiesUp();
void moveEnemiesDown();
void loadfromtext(int loadcase);
void loadbossfromtext(int loadbosscase);
void EnemySpawn(ENEMY& enemy,std::string name,char icon, COORD coordinates, int Active,int hp, int score,int number, int state);
void SpawnEnemy(unsigned int &currentEnemy, int modX, int modY);
void SpawnBoss(unsigned int &currentEnemy, int modX, int modY);



#endif // _SPAWNENEMIES_H

