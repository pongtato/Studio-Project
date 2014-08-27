#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include "score.h"

using std::cout;

void normalscore()
{
	int a = combined.globalSettings.globalscore;
	string result;
	ostringstream convert;
	convert << a;
	result = convert.str();
	writeToBuffer(57, 3, result, 0x03);

}

void Writetohighscore(){
	ifstream indata;
	string data;
	ofstream scoree;
	int a, b, highscoree;
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