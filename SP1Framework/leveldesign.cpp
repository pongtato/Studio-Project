#include "game.h"
#include "leveldesign.h"
#include <iostream>

using std::cout;



void leveldesign()
{
	ifstream indata;
	string data; 
	indata.open("GLD/GLD.txt");
	if (indata.is_open())
	{
		while (getline(indata, data))
		{
			std::cout << data << endl;
		}
		indata.close();
	}
}
void loseScreen()
{
	ifstream indata;
	string data; 
	indata.open("GLD/Lose.txt");
	if (indata.is_open())
	{
		while (getline(indata, data))
		{
			std::cout << data << endl;
		}
		indata.close();
	}
}