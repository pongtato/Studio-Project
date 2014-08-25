#include "game.h"
#include "Framework\console.h"
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
		for(int i = 0; i < 80;i++)
		{
			for(int j = 0; j<25;j++)
			{
				getline(indata, data);
				writeToBuffer(i,j,data);
			}
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
void mainScreen()
{
	ifstream inData;
	string data;

	inData.open ("GLD/Header.txt");
	
	while (!inData.eof())
	{
		getline (inData, data);
		std::cout << data << "\n";
	}

	inData.close ();
}
void pauseScreen()
{
	ifstream inData;
	string data;

	inData.open ("GLD/Pause.txt");
	
	while (!inData.eof())
	{
		getline (inData, data);
		std::cout << data << "\n";
	}

	inData.close ();
}