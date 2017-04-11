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
	enum { Size = 14 };
	soldier soldiers[3];
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
	void setSoldiers(Cell board[Size][Size],int gamerNum);
	void setkeys(const char* keys);
	//int setCurrSolider(char ch, int _gamerNum);
	void notifyKeyHit(char ch);
	void setDirection(Direction d);
	void printGamerName();
	void printGamerScore();
	int getScore();
	void putScore(int _score);
	void drowSoldiers();
	int move(Cell board[Size][Size]);
	void updateOutSolider(int outSolider);
	void win() {
		clearScreen();
		cout << "The gamer: " << name << " won this game" << endl;
		score++;
	}

};
