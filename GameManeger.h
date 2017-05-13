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
	bool quietMode = false;
	int delay = 20;
	string path = "NULL";
	bool gamer1Active = false;
	bool gamer2Active = false;
	bool GameOver = false;

	//counters for wrong setting to board that set from file 
	int SetACounter = 0, SetBCounter = 0;
	int setSol1 = 0, setSol2 = 0, setSol3 = 0, setSol7 = 0, setSol8 = 0, setSol9 = 0;
	string wrongCharsSet;

	bool opositeGame = false;
	bool recordGame = false;
	string recordBufferA;
	string recordBufferB;
	int GameNumber = 0;
	void printLetters() const;
	void printEndLine() const;
	void printNumber(int num)const;
public:
	GameManeger() { 
		setBoard();
		gamers[0].setkeys("wxad");
		gamers[1].setkeys("imjl");
		hideCursor();
		opositeGame = false;
		GameOver = false;
	}
	void paramMenager();
	void openFolder(char* tempPath);
	void setBoardFromFile(ifstream& inFile);
	void updateSetSoliderCounter(int solider);
	bool printAndCheckBoardFromFileErrors(string fileName) const;
	void commandLine(int argc, char* argv[]);
	void menu();
	void seconderyMenu();
	void initialization();
	void uploadBoardFromFile();
	void run();
	void runFromMovesFile();
	void runFromKeyBordMoves();
	void printBoard()const;
	void setBoard();
	void swapScore(int gamerTurn);
	void resetScore();
	void stopTheGame();
	void clearTheGame();
	char updateSoldierOut(int gamerTurn,int soliderOut);
	void printing() const;
	void divideToFile(char *buffer);
	void recordRandomBoard(string fileName);
	char findCellType(Cell board[(int)Sizes::size][(int)Sizes::size], int j,int i)const;
	string findFileName();
	int cmpBetweenString(map<string, int>::iterator str1, map<string, int>::iterator str2);
	void updateFilePerGame();
	ifstream openfile(map<string, int>::iterator file, int numOfGamer);
	void endMessage() const;
	ofstream openfileForRecord(map<string, int>::iterator file, int numOfGamer);
	ofstream openfileForRecord(int numOfGamer, string randomName);
	void GameManeger::uploadFiles();
	string RandomNameGenerator();
	void recordToFiles(ofstream& movesA, ofstream& movesB);
	void writeToMoveFiles(ofstream& movesA, ofstream& movesB);
	void endMessagePerGame(int GameCycle, int numOfMoves, char winner) const;


};
