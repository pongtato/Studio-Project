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

int shieldfromtext;
int shieldhpfromtext;
int shieldSize;

extern COORD charLocation;

void loadPlayerFromText()
{
	std::ifstream indata;
		indata.open("GLD/Variables/Player2.txt");
	
	if ( indata.is_open())
	{
		if (indata >> PlayerActivefromtext >> PlayerHpfromtext >> PlayerIconfromtext >> PlayerWingIcon >> PlayerHeadIcon>>PlayerMissileIcon >> PowerupIcon)
		{
			
		}
	}
	player.Active = PlayerActivefromtext;
	player.PowerUp = PlayerHpfromtext;
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
	// check collision
	for(unsigned int i = 0; i<combined.globalSettings.maxMissile;i++)
	{
		for(int j = 0; j<spawnno;j++)
		{
			if(checkPlayerDeath(charLocation,enemyBullet[j],counter[i]))
			{
				clearBuffer(0x0F);
				loseScreen();
				flushBufferToConsole();
				system("pause");
				menuscreen();
			}

			for(int i = 0; i<3;i++)
			{
				if(shieldblock(shield[i].coordinates,enemyBullet[j]))
				{
					shield[i].hp--;
					enemyBullet[j].Active = false;
					
				}
			}

			if ( checkCollisionBullet(missile[i], counter[j],combined.enemySettings.droppowerup))
			{
				if ( counter[j].hp <= 0 )
				{
					combined.globalSettings.globalscore += counter[j].score;
					combined.enemySettings.enemieskilled++;
				}
			}

		}
	}
}

void renderCharacter()
{
	// render character

	writeToBuffer(charLocation,player.icon,0x0C);
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
	Specialtemp << "SPECIAL" << ": " << player.Special;
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
	if( elapsedTime-timer_shieldfade > 5)
	{
		timer_shieldfade = elapsedTime;
		shield[0].Active = false;
		shield[1].Active = false;
		shield[2].Active = false;
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