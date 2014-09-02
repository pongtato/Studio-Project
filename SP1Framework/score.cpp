#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include "score.h"

using std::cout;

string Achievements[99] = { "Bronze Trophy!","Silver Trophy!","Gold Trophy!","Score","Combo","Accuracy"};

void normalscore()
{
	int a = combined.globalSettings.globalscore;
	string result;
	ostringstream convert;
	convert << a;
	result = convert.str();
	writeToBuffer(57, 3, result, 0x03);

}
void gameoverscore()
{
	int a = combined.globalSettings.globalscore;
	string result;
	ostringstream convert;
	convert << a;
	result = convert.str();
	writeToBuffer(56, 12, result, 0x07);
}

void Writetohighscore(){
	ifstream indata;
	string data;
	ofstream scoree;
	int a, b;
	a = combined.globalSettings.globalscore;

	indata.open("GLD/Variables/Highscore.txt");
	if (indata.is_open())
	{
		indata >> b;
	}

	if (b > a)
	{
		scoree.open("GLD/Variables/Highscore.txt");
		scoree << b;
	}
	if (a > b)
	{
		scoree.open("GLD/Variables/Highscore.txt");
		scoree << a;
	}

	indata.close();
}
void print(){
	ifstream indata2;
	string data;
	indata2.open("GLD/Variables/Highscore.txt");
	if (indata2.is_open())
	{
		getline(indata2, data);
		writeToBuffer(35, 20, data, 0x07);
	}
	indata2.close();

}
void trophyatlose()
{
	ifstream indata;
	string data;
	int a;
	a=combined.globalSettings.globalscore;
	indata.open("GLD/Variables/Trophies/Scoretrophy.txt");
	if (a > 10000 && a <= 20000 )
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(5, 14, Achievements[3]);
				writeToBuffer(0, j, data, 0x06);
				writeToBuffer(2, 22, Achievements[0],0x06);
			}
		}
	}
	if (a > 20000 && a < 40000)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(5, 14, Achievements[3]);
				writeToBuffer(0, j, data);
				writeToBuffer(2, 22, Achievements[1]);
			}
		}
	}
	if (a > 40000)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(5, 14, Achievements[3]);
				writeToBuffer(0, j, data,0x0E);
				writeToBuffer(2, 22, Achievements[2],0x0E);
			}
		}
	}
	indata.close();
}
void Acctrophy()
{
	ifstream indata;
	string data;
	double a;
	a = combined.stats.accuracy;
	indata.open("GLD/Variables/Trophies/Accuracytrophy.txt");
	if (a <= 70 && a >  50)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(23,14,Achievements[5]);
				writeToBuffer(0, j, data, 0x06);
				writeToBuffer(21, 22, Achievements[0], 0x06);
			}
		}
	}
	if (a > 70 && a< 100)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(23, 14, Achievements[5]);
				writeToBuffer(0, j, data);
				writeToBuffer(21, 22, Achievements[1]);
			}
		}
	}
	if (a == 100)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(23, 14, Achievements[5]);
				writeToBuffer(0, j, data, 0x0E);
				writeToBuffer(21, 22, Achievements[2], 0x0E);
			}
		}
	}
	indata.close();
}
void Combotrophy()
{
	ifstream indata;
	string data;
	int a;
	a = combined.stats.combo;
	indata.open("GLD/Variables/Trophies/Combotrophy.txt");
	if (a > 5 && a < 12)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(41, 14, Achievements[4]);
				writeToBuffer(0, j, data, 0x06);
				writeToBuffer(38, 22, Achievements[0], 0x06);
			}
		}
	}
	if (a > 12 && a <= 20)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(41, 14, Achievements[4]);
				writeToBuffer(0, j, data, 0x07);
				writeToBuffer(38, 22, Achievements[1], 0x07);
			}
		}
	}
	if (a > 20)
	{
		if (indata.is_open())
		{
			for (int j = 0; j<21; j++)
			{
				getline(indata, data);
				writeToBuffer(41, 14, Achievements[4]);
				writeToBuffer(0, j, data, 0x0E);
				writeToBuffer(37, 22, Achievements[2], 0x0E);
			}
		}
	}
	indata.close();
}