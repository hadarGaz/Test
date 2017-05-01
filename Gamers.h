#pragma once
#include "soldier.h"
#include "Cell.h"
#include <conio.h>
#include <string>
#include "Utils.h"
using namespace std;
class GameManeger;

class Gamers {
	enum keyOption{ UP, DOWN, LEFT, RIGHT, keyOptionSize};
	soldier soldiers[(int)Sizes::sizeOfSoldier];
	char _keys[keyOptionSize];
	string name;
	int score = 0;
	int _gamerNum;
	static char defualtName;
	int currSoldier = -1;
	int soldierDead = 0;
	friend class GameManeger;
public:
	Gamers() { 
		name = defualtName++;
	}
	void setName();
	void setSoldiersRandom(Cell board[(int)Sizes::size][(int)Sizes::size],int gamerNum);
	void setSoldiersFromFile(Cell board[(int)Sizes::size][(int)Sizes::size], int solider, int x,int y);
	void setkeys(const char* keys);
	void notifyKeyHit(char ch);
	void setDirection(Direction d);
	void printGamerName();
	void printGamerScore();
	int getScore();
	void putScore(int _score);
	void drowSoldiers();
	int move(Cell board[(int)Sizes::size][(int)Sizes::size]);
	void updateOutSolider(int outSolider);
	void win();
	void readFromMovesFile(char buff[]);

};
