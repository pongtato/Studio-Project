#include "Player.h"
#include "Shoot.h"
#include "game.h"

PLAYER player;
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
extern ENEMY counter[25];
extern BULLET enemyBullet[50];
extern BULLET missile[50];

extern COORD charLocation;

void loadPlayerFromText()
{
	std::ifstream indata;
		indata.open("GLD/Variables/Player.txt");
	
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
			//gotoXY(powerUp.corrdinates.X--,powerUp.corrdinates.Y);
			//std::cout << powerUp.icon << std::endl;
			writeToBuffer(powerUp.corrdinates.X--,powerUp.corrdinates.Y,powerUp.icon,0xA0);
		}
		else
		{
			/*gotoXY(powerUp.corrdinates.X,powerUp.corrdinates.Y);
			std::cout << powerUp.icon << std::endl;*/
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
		if ( elapsedTime - timer_spawn > 0.1 )
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
		if(checkPlayerDeath(charLocation,enemyBullet[i],counter[i]))
		{
			counter[i].Active = false;
			enemyBullet[i].Active = false;
			system("pause");
		}
		if ( combined.globalSettings.loadlevel%4 != 0)
		{
			for(int j = 0; j<NO_OF_ENEMIES;j++)
			{
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
		//		else
		//		{
		//			for(int j = 0; j<BOSS_NO;j++)
		//			{
		//				if ( BosscheckCollisionBullet(missile[i], Bcounter[j]))
		//				{
		//					if ( Bcounter[j].hp <= 0 )
		//					{
		//						globalscore += Bcounter[j].score;
		//						enemieskilled = 25;
		//					}
		//				}
		//
		//			}
		//		}
		//	}
	}
}

void renderCharacter()
{
	// render character
	/*gotoXY(charLocation);
	colour(0x0C);
	std::cout << player.icon;*/
	writeToBuffer(charLocation,player.icon,0x0C);

	//gotoXY(charLocation.X+1,charLocation.Y);
	if (player.PowerUp == 1 || player.PowerUp >= 3)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0B);
	}
	else if ( player.PowerUp == 2)
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X+1,charLocation.Y,player.headIcon,0x0F);
	}

	//gotoXY(charLocation.X,charLocation.Y-1);
	if (player.PowerUp >= 2)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0B);
	}
	else
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X,charLocation.Y-1,player.wingIcon,0x0F);
	}
	//std::cout << player.wingIcon;

//	gotoXY(charLocation.X,charLocation.Y+1);
	if (player.PowerUp >= 2)
	{
	//colour(0x0B);
		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0B);
	}
	else
	{
	//colour (0x0F);
		writeToBuffer(charLocation.X,charLocation.Y+1,player.wingIcon,0x0F);
	}
	//std::cout <<  player.wingIcon;
}