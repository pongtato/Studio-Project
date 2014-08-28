#include "game.h"
#include "Framework\console.h"
#include "leveldesign.h"
#include <iostream>

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
			for(int j = 0; j<13;j++)
			{
				getline(indata, data);
				writeToBuffer(0,j,data, 0x06);
			}
	}
		indata.close();
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
				writeToBuffer(0,i,data, 0x06);
			}
			
		
		indata.close();
	}
}

void pauseScreen()
{
	ifstream indata;
	string data;

	indata.open ("GLD/Pause.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <23; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}
}

void exitScreen()
{
	ifstream indata;
	string data;

	indata.open ("GLD/Exit.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <18; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}
}