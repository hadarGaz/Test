#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include "FilesMap.h"
#include "Gamers.h"
#include "Cell.h"
#include "Utils.h"


using namespace std;

class GameManeger {
	enum{ ESC = 27 };
	Gamers gamers[(int)Sizes::sizeOfGamers];
	Cell board[(int)Sizes::size][(int)Sizes::size];
	bool EXIT = 0;
	bool win = false;
	//new
	FilesMap boardFile, movesAFiles, movesBFiles;
	map<string, int>::iterator currFileMovesA , currFileMovesB, currFileBoard;
	bool ifBoardFile = false;
	bool ifMovesFile = false;
	char* path = nullptr;
	bool gamer1Active = false;
	bool gamer2Active = false;

	//counters for wrong setting to board that set from file 
	int SetACounter = 0, SetBCounter = 0;
	int setSol1 = 0, setSol2 = 0, setSol3 = 0, setSol7 = 0, setSol8 = 0, setSol9 = 0;
	string wrongCharsSet;

	bool opositeGame = false;
	bool recordGame = false;
	void printLetters();
	void printEndLine();
	void printNumber(int num);
public:
	GameManeger() { 
		setBoard();
		gamers[0].setkeys("wxad");
		gamers[1].setkeys("imjl");
		hideCursor();
		opositeGame = false;
	}
	void paramMenager();
	void justForTest();
	void setBoardFromFile(ifstream& inFile);
	bool isBoardFromFileOK();
	void updateSetSoliderCounter(int solider);
	void printBoardFromFileErrors(string fileName);
	void commandLine(int argc, char* argv[]);
	void menu();
	void seconderyMenu();
	void initialization();
	void run();
	void printBoard();
	void setBoard();
	void swapScore(int gamerTurn);
	void resetScore();
	void stopTheGame();
	void clearTheGame();
	void updateSoldierOut(int gamerTurn,int soliderOut);
	void printing();
	void divideToFile(char *buffer);
	void recordRandomBoard(Cell board[(int)Sizes::size][(int)Sizes::size]);
	char findCellType(Cell board[(int)Sizes::size][(int)Sizes::size], int j,int i)const;
	string findFileName();
	int cmpBetweenString(map<string, int>::iterator str1, map<string, int>::iterator str2);
	void updateFilePerGame();
	ifstream GameManeger::openfile(map<string, int>::iterator file, int numOfGamer);
	
};
