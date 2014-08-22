#include "Player.h"

PLAYER player;
int PlayerActivefromtext;
int PlayerHpfromtext;
int PlayerIconfromtext;
int PlayerHeadIcon;
int PlayerWingIcon;
int PlayerMissileIcon;
int PowerupIcon;

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
