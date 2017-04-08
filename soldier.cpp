#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "soldier.h"

void soldier::move(Cell board[Size][Size])
{
	void earse();
	_x = _x + _y_dir;
	_y = _y + _x_dir;
	if (_x < MIN_X || _x > MAX_X || _y < MIN_Y || _y > MAX_Y)
		this->stop();
	
	else if ((board[_x][_y]).isCellEmpty())
	{
		move();
		(board[_x][_y]).update(soldierNum);
	}
	else
	{
		int typeReturnd = (board[_x][_y]).returnedCellType();
		if (typeReturnd == sea) {
			if (seaPass == 1)
			{
				move();
				(board[_x][_y]).update(soldierNum);
			}
			else
				stop();
		}
		else if (typeReturnd == fr)
		{
			if(frPass== 1)
			{
				move();
				(board[_x][_y]).update(soldierNum);
			}
			else
				stop();
		}
		else if (typeReturnd == flagA)
			stop();
		else if (typeReturnd == flagB)
			stop();
		else
		{
			int numOfGamer;
			typeReturnd = (board[_x][_y]).returndGamer(numOfGamer);

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
	//gotoxy(4*_x+2,2*_y);
	gotoxy(4* _y+2, 2 * _x);
	cout << soldierNum;
	cout.flush();
}

void soldier::setCondition(int soldierNum)
{
	switch (soldierNum)
	{
	case '1':
		seaPass = 0;
		frPass = 0;
		break;
	case '2':
		seaPass = 1;
		frPass = 1;
		break;
	case '3':
		seaPass = 1;
		frPass = 0;
		break;
	case '7':
		seaPass = 1;
		frPass = 1;
		break;
	case '8':
		seaPass = 0;
		frPass = 1;
		break;
	case '9':
		seaPass = 0;
		frPass = 0;
		break;
	}
}

void soldier::move()
{
	
	void drow();
}