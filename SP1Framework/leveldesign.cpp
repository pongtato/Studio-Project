#include "game.h"
#include "Framework\console.h"
#include "leveldesign.h"
#include <iostream>
#include "Player.h"
#include "common.h"
#include "Shoot.h"
#include "MainMenu.h"
#include <conio.h> 
string n[99] = { "Please Press 'n' to continue..."};
string Score[99] = { "Score :"};

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
void winScreen()
{
	ifstream indata;
	string data; 
	indata.open("GLD/Win.txt");
	if (indata.is_open())
	{
			for(int j = 0; j<13;j++)
			{
				getline(indata, data);
				writeToBuffer(0,j,data, 0x06);
			}
			writeToBuffer(48,12,Score[0],0x04);
	}
	gameoverscore();
	Combotrophy();
	Acctrophy();
	trophyatlose();
	indata.close();
	writeToBuffer(23,23,n[0],0x07);
	flushBufferToConsole();

	char c = _getch();
		switch (c)
		{
		case 'n':
		break;
		default:
		winScreen();
		break;
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
			writeToBuffer(48,12,Score[0],0x04);
	}
	gameoverscore();
	Combotrophy();
	Acctrophy();
	Scoretrophy();
	indata.close();
	writeToBuffer(23,23,n[0],0x07);
	flushBufferToConsole();

	char c = _getch();
		switch (c)
		{
		case 'n':
		break;
		default:
		loseScreen();
		break;
		}
}
void mainScreenIntro()
{
	
	string bullet = " - ";

	string pongtato1 = "   ___   ___  _   _  ____ _____  _  _____ ___";
	string pongtato2 = " |  _ \\ / _ \\| \\ | |/ ___|_   _|/ \\|_   _/ _ \\  ";          
    string pongtato3 = " | |_) | | | |  \\| | |  _  | | / _ \\ | || | | |";         
    string pongtato4 = " |  __/| |_| | |\\  | |_| | | |/ ___ \\| || |_| |";         
    string pongtato5 = " |_|    \\___/|_| \\_|\\____| |_/_/   \\_|_| \\___/";         
                
    string invasion1 = "  ___ _   ___     ___    ____ ___ ___  _   _";                                                        
    string invasion2 = " |_ _| \\ | \\ \\   / / \\  / ___|_ _/ _ \\| \\ | |";            
    string invasion3 = "  | ||  \\| |\\ \\ / / _ \\ \\___ \\| | | | |  \\| |";             
    string invasion4 = "  | || |\\  | \\ V / ___ \\ ___) | | |_| | |\\  |";              
    string invasion5 = " |___|_| \\_|  \\_/_/   \\_|____|___\\___/|_| \\_|";



	writeToBuffer(16,1,pongtato1,0x06);
	flushBufferToConsole(); Sleep(100);
	writeToBuffer(16,1,bullet,0x0F);
	writeToBuffer(16,1,pongtato1,0x03);
	flushBufferToConsole(); Sleep(200);
	
	writeToBuffer(16,2,pongtato2,0x06);
	flushBufferToConsole(); Sleep(75);
	writeToBuffer(16,2,pongtato2,0x03);
	flushBufferToConsole(); Sleep(200);

	writeToBuffer(16,3,pongtato3,0x06);
	flushBufferToConsole(); Sleep(75);
	writeToBuffer(16,3,pongtato3,0x03);
	flushBufferToConsole(); Sleep(200);

	writeToBuffer(16,4,pongtato4,0x06);
	flushBufferToConsole(); Sleep(75);
	writeToBuffer(16,4,pongtato4,0x03);
	flushBufferToConsole(); Sleep(200);

	writeToBuffer(16,5,pongtato5,0x06);
	flushBufferToConsole(); Sleep(75);
	writeToBuffer(16,5,pongtato5,0x03);
	flushBufferToConsole(); Sleep(400);

	writeToBuffer(16,1,pongtato1,0x06);
	writeToBuffer(16,2,pongtato2,0x06);
	writeToBuffer(16,3,pongtato3,0x06);
	writeToBuffer(16,4,pongtato4,0x06);
	writeToBuffer(16,5,pongtato5,0x06);
	flushBufferToConsole(); Sleep(1000);

	writeToBuffer(17,6,invasion1,0x06);
	writeToBuffer(17,7,invasion2,0x06);
	writeToBuffer(17,8,invasion3,0x06);
	writeToBuffer(17,9,invasion4,0x06);
	writeToBuffer(17,10,invasion5,0x06);
	flushBufferToConsole();

	Sleep(1000);
	
	playGameSound(S_MUSIC);
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
	//playGameSound(S_MUSIC);

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
void planeScreen()
{
	ifstream indata;
	string data;

	indata.open ("GLD/Plane.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <18; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}

	ifstream indata2;
	string data2;

	indata2.open ("GLD/Planeimage.txt");

	if (indata2.is_open())
	{
		
			for(int i = 0; i <25; i++)
			{
				getline(indata2, data2);
				writeToBuffer(0,i,data2,0x08);
			}
			
		
		indata2.close();

		 
		COORD c = {24, 17};
		writeToBuffer(c.X,c.Y, (char)15,0x0C); // icon
		writeToBuffer(c.X+1,c.Y,(char)16,0x0B); //head
		writeToBuffer(c.X,c.Y+1,(char)4,0x0B); //wings
		writeToBuffer(c.X,c.Y-1,(char)4,0x0B);  //wings

		COORD d = {52,17};
		writeToBuffer(d.X,d.Y, (char)10,0x0C);
		writeToBuffer(d.X+1,d.Y,(char)228,0x0B);
		writeToBuffer(d.X,d.Y+1,(char)204,0x0F);
		writeToBuffer(d.X,d.Y-1,(char)204,0x0F);

	}



}
void stagesScreen()
{
	ifstream indata;
	string data;

	indata.open ("GLD/Stages.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <20; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}
}
void stageclearscreen()
{
	clearBuffer(0x0F);
	ifstream indata;
	string data;

	indata.open ("GLD/stageclear.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <6; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}
	//Clear existing Bullets on screen
	restartBullet();
	
	std::stringstream temp;
	temp << "SHOTS FIRED: ";
	std::string result = temp.str();
	writeToBuffer(19, 7, result, 0x0F);
	std::stringstream temp4;
	temp4 << combined.stats.bulletsfired;
	std::string result4 = temp4.str();
	writeToBuffer(32, 7, result4, 0x0C);
	std::stringstream temp2;
	temp2 << "SHOTS MISSED: ";
	std::string result2 = temp2.str();
	writeToBuffer(42, 7, result2, 0x0F);
	std::stringstream temp3;
	temp3 << combined.stats.bulletsmissed;
	std::string result3 = temp3.str();
	writeToBuffer(55, 7, result3, 0x0C);

	if ( combined.stats.bulletsfired != 0 && combined.stats.bulletsmissed !=0)
	{
		combined.stats.accuracy = ((combined.stats.shotshit/(combined.stats.shotshit+combined.stats.bulletsmissed)) * 100);
	}
	std::stringstream temp5;
	temp5 << "ACCURACY: ";
	std::string result5 = temp5.str();
	writeToBuffer(19, 9, result5, 0x0F);

	std::stringstream temp6;
	temp6 << combined.stats.accuracy << "%";
	std::string result6 = temp6.str();
	writeToBuffer(28, 9, result6, 0x0C);

	std::stringstream combo1;
	combo1 << "COMBO: ";
	std::string resultcombo = combo1.str();
	writeToBuffer(42, 9, resultcombo, 0x0F);

	std::stringstream combo2;
	combo2 << combined.stats.combo;
	std::string resultcombo2 = combo2.str();
	writeToBuffer(49, 9, resultcombo2, 0x0C);

	Combotrophy();

	Acctrophy();
	Scoretrophy();

	writeToBuffer(23,23,n[0],0x07);

	flushBufferToConsole();

	char c = _getch();
	switch (c)
	{
	case 'n':
	break;
	default:
	stageclearscreen();
	break;
	}
			
}
void returntomenu()
{
	ifstream indata;
	string data;

	indata.open ("GLD/Returnmenu.txt");

	if (indata.is_open())
	{
		
			for(int i = 0; i <20; i++)
			{
				getline(indata, data);
				writeToBuffer(0,i,data,0x06);
			}
			
		
		indata.close();
	}
}