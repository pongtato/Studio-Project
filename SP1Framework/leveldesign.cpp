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
			for(int j = 0; j<25;j++)
			{
				getline(indata, data);
				writeToBuffer(0,j,data);
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
void mainScreen()
{
	ifstream indata;
	string data; 
	indata.open("GLD/Header.txt");
	if (indata.is_open())
	{
		
			for(int i = 0; i <12; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data);
			}
			
		
		indata.close();
	}
}
void pauseScreen()
{
	ifstream inData;
	string data;

	inData.open ("GLD/Pause.txt");

	while (!inData.eof())
	{
		getline (inData, data);
		writeToBuffer(0,0,data);
	}

	inData.close ();
}