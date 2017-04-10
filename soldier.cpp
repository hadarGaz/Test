#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "soldier.h"

//returns 0 if there is no attack and solider num of the solider who fall if attack occured
int soldier::move(Cell board[Size][Size])
{
	int oldX = _x;
	int oldY = _y;
	_x = _x + _x_dir;
	_y = _y + _y_dir;

	//make sure there is a direction for movment 
	if (_x_dir == 0 && _y_dir == 0)
		return 0;
	//check the board bounderies 
	if (_x < MIN_X || _x > MAX_X || _y < MIN_Y || _y > MAX_Y) {
		stop(oldX, oldY);
		return 0;
	}
	//check if the cell is empty and clear to movement
	if ((board[_x][_y]).isCellEmpty())
	{
		move(oldX, oldY, board);
		return 0;

	}
	else //if not empty
	{
		int typeReturnd = (board[_x][_y]).returnedCellType();
		if (typeReturnd == sea) {
			if (seaPass == 1){
				move(oldX, oldY, board);
			}
			else 
				stop(oldX, oldY);
			return 0;
		}
		else if (typeReturnd == fr){
			if(frPass== 1)
			{
				move(oldX, oldY, board);
			}
			else {
				stop(oldX, oldY);
			}
			return 0;
			
		}
		else if (typeReturnd == flagA) {
			if (soldierNum >= 7 && soldierNum <= 9)
				return -1;
			else {
				stop(oldX, oldY);
				return 0;
			}
		}
	
		else if (typeReturnd == flagB) {
			if (soldierNum >= 1 && soldierNum <= 3)
				return -1;
			else {
				stop(oldX, oldY);
				return 0;
			}
		}
		else //if its a soldier
		{
			int numOfGamer;
			int enemySoldierNumber;
			bool win = false;
			enemySoldierNumber = (board[_x][_y]).returndGamer(numOfGamer);
			if (numOfGamer == 1) {
				if (enemySoldierNumber >= 1 && enemySoldierNumber <= 3 && soldierNum <= 3) {
					stop(oldX, oldY);
					return 0;
				}
				else {
					win = attack(enemySoldierNumber);
				}
			}
			
			else{
				if (enemySoldierNumber >= 7 && enemySoldierNumber <= 9 && soldierNum >= 7) {
					stop(oldX, oldY);
					return 0;
				}
				else {
					win = attack(enemySoldierNumber);
				}
			}
			if (win) {
				moveAfterWin(oldX, oldY, board);
				return enemySoldierNumber;
				
			}
			else {
				moveAfterDefeat(oldX, oldY, board);
				return soldierNum;
			}	
		}
	}
}


void soldier::setDirection(Direction d)
{
	switch (d)
	{
	case Direction::UP:
		_x_dir = 0;
		_y_dir = -1;
		break;
	case Direction::DOWN:
		_x_dir = 0;
		_y_dir = 1;
		break;
	case Direction::LEFT:
		_x_dir = -1;
		_y_dir = 0;
		break;
	case Direction::RIGHT:
		_x_dir = 1;
		_y_dir = 0;
		break;
	}
}

void soldier::stop(int oldX, int oldY)
{
	_x_dir = 0;
	_y_dir = 0;
	_x = oldX;
	_y = oldY;
}

void soldier::stop()
{
	_x_dir = 0;
	_y_dir = 0;
}
void soldier::set(int x, int y, int ch)
{
	_x = x;
	_y = y;
	soldierNum = ch;
}

void soldier::draw(int soldierNum)
{
	gotoxy(4 * _x + 1, 2 * _y);
	if (soldierNum == 0)
		cout << " ";
	else
		cout << " " << soldierNum << " ";

	cout.flush();
}

void soldier::earse(int oldX, int oldY) {
	gotoxy(4 * oldX + 2, 2 * oldY);
	cout << " ";
}

void soldier::setCondition(int soldierNum)
{
	switch (soldierNum)
	{
	case 1:
		seaPass = 0;
		frPass = 0;
		break;
	case 2:
		seaPass = 1;
		frPass = 1;
		break;
	case 3:
		seaPass = 1;
		frPass = 0;
		break;
	case 7:
		seaPass = 1;
		frPass = 1;
		break;
	case 8:
		seaPass = 0;
		frPass = 1;
		break;
	case 9:
		seaPass = 0;
		frPass = 0;
		break;
	}
}

bool soldier::attack(int enemyNum) {
	switch (soldierNum) {
	case 1:
		return oneIsAttack();
		break;
	case 2:
		return twoIsAttack(enemyNum);
		break;
	case 3:
		return treeIsAttack();
		break;
	case 7:
		return sevenIsAttack(enemyNum);
		break;
	case 8:
		return eightIsAttack(enemyNum);
		break;
	case 9:
		return nineIsAttack(enemyNum);
		break;
	default:
		return true;
	}

}

void soldier::move(int oldX, int oldY, Cell board[Size][Size])
{
	earse(oldX, oldY);
	(board[oldX][oldY]).clear();
	draw();
	(board[_x][_y]).update(soldierNum);
}

void soldier::moveAfterWin(int oldX, int oldY, Cell board[Size][Size]) {
	earse(_x, _y);
	earse(oldX, oldY);
	(board[oldX][oldY]).clear();
	(board[_x][_y]).clear();
	draw();
	(board[_x][_y]).update(soldierNum);
}

void soldier::moveAfterDefeat(int oldX, int oldY, Cell board[Size][Size]) {
	stop(oldX, oldY);
	earse(oldX, oldY);
	(board[oldX][oldY]).clear();
	isAlive = false;
}
//Attack results per solider conditions 
bool soldier::oneIsAttack() {
	if ((_y >= 10 && _y <= 13) || _x == 4)
		return false;
	else
		return true;
}
bool soldier::twoIsAttack(int enemyNum) {
	if (enemyNum == 9)
		return false;
	else if ((enemyNum == 7 || enemyNum == 8) && ((_y >= 3 && _y <= 4) || _x == 11))
		return true;
	else
		return false;
}
bool soldier::treeIsAttack() {
	if (_y == 8 || _x == 7)
		return true;
	else
		return false;
}
bool soldier::sevenIsAttack(int enemyNum) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(((_y != 4 && _y != 3) && _x != 11) && enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}
bool soldier::eightIsAttack(int enemyNum) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(((_y != 4 && _y != 3) && _x != 11) && enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}
bool soldier::nineIsAttack(int enemyNum) {
	if ((((_y >= 10 && _y <= 13) || (_x == 4)) && enemyNum == 1) ||
		(enemyNum == 2) ||
		((_y != 8 && _x != 7) && enemyNum == 3))
		return true;
	else
		return false;
}
