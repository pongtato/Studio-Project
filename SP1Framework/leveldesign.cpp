#include "game.h"
#include "Framework\console.h"
#include "leveldesign.h"
#include <iostream>
#include "Player.h"


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


}

