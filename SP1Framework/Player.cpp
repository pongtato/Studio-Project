#include "Player.h"
#include "Shoot.h"
#include "game.h"
#include "leveldesign.h"
#include "MainMenu.h"
#include "SpawnEnemies.h"
#include "common.h"
#include <sstream>

PLAYER player;
SHIELD shield[3];
int PlayerActivefromtext;
int PlayerHpfromtext;
int PlayerIconfromtext;
int PlayerHeadIcon;
int PlayerWingIcon;
char PlayerMissileIcon;
int PowerupIcon;
extern GLOBAL combined;
extern BULLET powerUp;
extern double elapsedTime;
extern ENEMY counter[999];
extern BULLET enemyBullet[50];
extern BULLET missile[50];
extern int spawnno;
extern WORLD generator[999];
extern WORLD generator2[999];

int shieldfromtext;
int shieldhpfromtext;
int shieldSize;

extern COORD charLocation;

void loadPlayerFromText()
{
	std::ifstream indata;
		indata.open("GLD/Variables/Player.txt");
	
	if ( indata.is_open())
	{
		if (indata >> player.Active >> player.PowerUp >> PlayerIconfromtext >> PlayerWingIcon >> PlayerHeadIcon>>PlayerMissileIcon >> PowerupIcon >> player.Lives >> player.Special)
		{
			
		}
	}
	assignText();
}

void loadPlayer2FromText()
{
	std::ifstream indata;
		indata.open("GLD/Variables/Player2.txt");
	
	if ( indata.is_open())
	{
		if (indata >> player.Active >> player.PowerUp >> PlayerIconfromtext >> PlayerWingIcon >> PlayerHeadIcon>>PlayerMissileIcon >> PowerupIcon>> player.Lives >> player.Special)
		{
			
		}
	}
	assignText();
}
void assignText()
{
	player.icon = PlayerIconfromtext;
	player.headIcon = PlayerHeadIcon;
	player.wingIcon = PlayerWingIcon;
	player.playerMissleIcon = PlayerMissileIcon;
}

void renderPowerUp()
{
//	//colour(0xA0);
	if(powerUp.Active)
	{
		combined.enemySettings.droppowerup = false;
		static double timer_powerUp = elapsedTime;
		if ( elapsedTime - timer_powerUp > 0.5 )
		{
			timer_powerUp = elapsedTime;

			writeToBuffer(powerUp.corrdinates.X--,powerUp.corrdinates.Y,powerUp.icon,0xA0);
		}
		else
		{
			writeToBuffer(powerUp.corrdinates.X,powerUp.corrdinates.Y,powerUp.icon,0xA0);
		}
		//Check if out of bound
		if(powerUp.corrdinates.X <= 1)
		{
			powerUp.Active = false;
			combined.enemySettings.droppowerup = true;
		}
	}
}

void collision()
{	
	static double timer_spawn = elapsedTime;
	if ( elapsedTime - timer_spawn > 1 )
	{
		timer_spawn = elapsedTime;
		player.Invultimer--;
		if ( player.Invultimer <= 0)
		{
		player.Invul = 0;
		}
	}
	
	if(player.Active != true && player.Lives <= 0)
	{
		clearBuffer(0x0F);
		loseScreen();
		flushBufferToConsole();
		restartGame();
		system("pause");
		introscreen();
	}

	//Check Powerup collide
	if(powerUpPlayerCollision(charLocation,powerUp))
	{
		static double timer_spawn = elapsedTime;
		if ( elapsedTime - timer_spawn > 0.2 )
		{
			timer_spawn = elapsedTime;
			powerUp.Active = false;
			player.PowerUp++;
			combined.enemySettings.droppowerup = true;
		}
	}

	//Check Terrain collide
	for(int i = 0; i<100;i++)
	{
		if(deathByTerrain(charLocation,generator[i]))
		{
			if ( player.Lives != 0 && player.Invul != 1)
			{
				player.Lives--;
				player.Invul = 1;
				player.coordinates.X = 3;
				player.coordinates.Y = 10;
				player.Invultimer = 3;
			}
			else
			{
				player.Active = false;

			}
		}
	}

	//Check Terrain collide
	for(int i = 0; i<100;i++)
	{
		if(deathByTerrain(charLocation,generator2[i]))
		{
			if ( player.Lives != 0 && player.Invul != 1)
			{
				player.Lives--;
				player.Invul = 1;
				player.coordinates.X = 3;
				player.coordinates.Y = 10;
				player.Invultimer = 3;
			}
			else
			{
				player.Active = false;
			}
		}
	}
	// check collision
	for(unsigned int i = 0; i<combined.globalSettings.maxMissile;i++)
	{
		for(int j = 0; j<combined.enemySettings.enemyMaxMissile;j++)
		{
			if(checkPlayerDeath(charLocation,enemyBullet[j],counter[i]))
			{
				if ( player.Lives != 0 && player.Invul != 1)
				{
					player.Lives--;
					player.Invul = 1;
					player.coordinates.X = 3;
					player.coordinates.Y = 10;
					player.Invultimer = 3;
				}
				else
				{
					player.Active = false;

				}
			}
			

			for(int i = 0; i<3;i++)
			{
				if(shieldblock(shield[i],enemyBullet[j]))
				{
					//shield[i].hp--;
					enemyBullet[j].Active = false;
					
				}
			}

			if ( checkCollisionBullet(missile[i], counter[j],combined.enemySettings.droppowerup))
			{
				if ( counter[j].hp <= 0 )
				{
					combined.globalSettings.globalscore += (counter[j].score * combined.stats.combo);
					combined.enemySettings.enemieskilled++;
				}
			}

		}
	}
}

void renderCharacter()
{
	if ( player.Invul != 1)
	{
		writeToBuffer(charLocation,player.icon,0x0C);
	}
	else
	{
		writeToBuffer(charLocation,player.icon,0x0E);
	}
	
	// render character
	if (player.PowerUp == 1 || player.PowerUp >= 3)
	{
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0B);
	}
	else if ( player.PowerUp == 2)
	{
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0F);
	}


	if (player.PowerUp >= 2)
	{
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0B);
	}
	else
	{
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0F);
	}

	if (player.PowerUp >= 2)
	{

		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0B);
	}
	else
	{

		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0F);
	}

}

void PrintSpecial()
{
	std::stringstream Specialtemp;
	Specialtemp << "SPECIAL:" << player.Special;
	std::string stage = Specialtemp.str();
	writeToBuffer(50, 6, stage, 0x0E);
}

void renderShield()
{
	if ( shield[0].Active == true )
	{
		
		writeToBuffer(shield[0].coordinates,shield[0].icon,0x0A);
		writeToBuffer(shield[1].coordinates,shield[1].icon,0x0A);
		writeToBuffer(shield[2].coordinates,shield[2].icon,0x0A);
	}
	
	static double timer_shieldfade = elapsedTime;
	if( elapsedTime-timer_shieldfade > 1)
	{
		shield[0].shieldTick--;
		shield[1].shieldTick--;
		shield[2].shieldTick--;
		timer_shieldfade = elapsedTime;
		if ( shield[0].shieldTick <= 0 || shield[1].shieldTick <= 0 || shield[2].shieldTick <= 0)
		{
		shield[0].Active = false;
		shield[1].Active = false;
		shield[2].Active = false;
		shield[0].shieldTick = 5;	
		shield[1].shieldTick = 5;	
		shield[2].shieldTick = 5;			
		}
	}
}

void initshieldVar()
{
	std::ifstream indata;
	indata.open("GLD/Variables/Special(Shield).txt");
	if ( indata.is_open())
	{
		if (indata >> shieldhpfromtext >> shieldfromtext >> shieldSize )
		{
		}
	}
	for(int i = 0; i<3;i++)
	{
	shield[i].icon = shieldfromtext;
	shield[i].hp = shieldhpfromtext;
	shield[i].Active = false;
	}
	player.Special = 2;
}

void useSpecial()
{	
	if ( player.Special > 0 && shield[0].Active == false)
	{
		
		shield[0].coordinates.X = charLocation.X + 3;
		shield[0].coordinates.Y = charLocation.Y;
		shield[1].coordinates.X = charLocation.X + 3;
		shield[1].coordinates.Y = charLocation.Y-1;
		shield[2].coordinates.X = charLocation.X + 3;
		shield[2].coordinates.Y = charLocation.Y+1;
		player.Special--;
		shield[0].Active = true;
		shield[1].Active = true;
		shield[2].Active = true;
	}
}

void printLives()
{
	std::stringstream livestemp;
	livestemp << "Lives" << ": ";
	std::string live = livestemp.str();
	writeToBuffer(50, 2, live, 0x0F);
}

void printHearts()
{
	for (int i = 0; i < player.Lives; i++)
	{
	std::stringstream livestemp;
	livestemp << char(3);
	std::string live = livestemp.str();
	writeToBuffer(55+(i+1), 2, live, 0x0C);
	}
}