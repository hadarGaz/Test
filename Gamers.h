#pragma once
#include "soldier.h"
#include "Cell.h"
#include <conio.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include "Utils.h"
#include <fstream>
#include <map>
using namespace std;
class GameManeger;

class Gamers {
	enum keyOption{ UP, DOWN, LEFT, RIGHT, keyOptionSize};
	soldier soldiers[(int)Sizes::sizeOfSoldier];
	char _keys[keyOptionSize];
	string name;
	int score = 0;
	static int gamerNum;
	int _gamerNum;
	static char defualtName;
	int currSoldier = -1;
	int soldierDead = 0;
	bool isRecordOn = false;
	friend class GameManeger;
public:
	Gamers() { 
		name = defualtName++;
		_gamerNum = gamerNum++;
	}
	void setName();
	void setSoldiersRandom(Cell board[(int)Sizes::size][(int)Sizes::size]);
	void setSoldiersFromFile(Cell board[(int)Sizes::size][(int)Sizes::size], int solider, int x,int y);
	void setkeys(const char* keys);
	void notifyKeyHit(char ch);
	void setDirection(Direction d);
	void putScore(int _score);
	void drowSoldiers() const;
	int move(Cell board[(int)Sizes::size][(int)Sizes::size],string& recordBufferA, string& recordBufferB);
	void updateOutSolider(int outSolider);
	int win();
	bool readFromMovesFile(char* buff);
	void recordMoveToBuffer(int tool, int col, int row,string& buffer);
};
