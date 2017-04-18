#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Gamers.h"
#include "Cell.h"
#include "Utils.h"



class GameManeger {
	enum{ ESC = 27 };
	Gamers gamers[(int)Sizes::sizeOfGamers];
	Cell board[(int)Sizes::size][(int)Sizes::size];
	bool EXIT = 0;
	bool win = false;
	void printLetters();
	void printEndLine();
	void printNumber(int num);
public:
	GameManeger() { 
		setBoard();
		gamers[0].setkeys("wxad");
		gamers[1].setkeys("imjl");
		hideCursor();
	}
	void menu();
	void seconderyMenu();
	void initialization();
	void run();
	void printBoard();
	void setBoard();
	void swapScore();
	void resetScore();
	void stopTheGame();
	void clearTheGame();
	void updateSoldierOut(int gamerTurn,int soliderOut);
	void printing();

};
