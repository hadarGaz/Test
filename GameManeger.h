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
	enum { Size = 14,ESC = 27, SizeOfSoldier =2};
	enum { empty, sea, fr, flagA, flagB };

	Gamers gamers[SizeOfSoldier];
	Cell board[Size][Size];

	void printLetters();
	void printEndLine();
	void printNumber(int num);
public:
	GameManeger() { 
		setBoard();
		gamers[0].setkeys("wxad");
		gamers[1].setkeys("imjl");
		//hideCursor();
	}
	void menu();
	void seconderyMenu();
	void startGame();
	void run();
	void printBoard();
	void setBoard();
	void swapScore();
	void resetScore();
	void stopTheGame();
	void updateSoldierOut(int gamerTurn,int soliderOut);

};
