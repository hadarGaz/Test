#pragma once
//#include "Gamers.h"
#include "Direction.h"
#include <cstdlib>
#include <iostream>
#include "Utils.h"
#include "Cell.h"
using namespace std;

class soldier {
	enum Type { emptyType, sea, fr, flagA, flagB };
	enum GamerA { noGamerA, soldier1, soldier2, soldier3 };
	enum GamerB { noGamerB, soldier7 = 7, soldier8 = 8, soldier9 = 9 };
	enum { MIN_X = 1, MAX_X = 13, MIN_Y = 1, MAX_Y = 13 };
	enum { Size = 14 };
	int _x, _y;
	int _x_dir =0, _y_dir=0;
	int soldierNum;
	int seaPass = 0;
	int frPass = 0;
	bool isAlive = true;
	void draw(int ch);
	friend class Gamers;
public:
	void set(int x, int y, int ch);
	void draw() { draw(soldierNum); }
	void earse(int oldX, int oldY);
	int move(Cell board[Size][Size]);
	void move(int oldX, int oldY, Cell board[Size][Size]);
	void moveAfterWin(int oldX, int oldY, Cell board[Size][Size]);//consult with Hadar
	void moveAfterDefeat(int oldX, int oldY, Cell board[Size][Size]);//consult with Hadar
	void printSpecialCell(int oldX, int oldY, Cell board[Size][Size]);
	void setDirection(Direction d);
	void stop(int oldX, int oldY);
	void setCondition(int soldierNum);
	bool attack(int enemyNum);
	void stop();
	bool oneIsAttack();
	bool twoIsAttack(int enemyNum);
	bool treeIsAttack();
	bool sevenIsAttack(int enemyNum);
	bool eightIsAttack(int enemyNum);
	bool nineIsAttack(int enemyNum);

};
