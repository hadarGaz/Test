#include "Gamers.h"

char Gamers::defualtName = 'A';

void Gamers::setSoldiers(Cell board[Size][Size], int gamerNum)
{
	_gamerNum = gamerNum;
	int soldierNum;
	if (gamerNum == 1) {
		soldierNum = 1;
	}
	else {
		soldierNum = 7;
	}
	int x=0, y=0, found = 0;
	for (soldier& sol : soldiers)
	{
		while (!found)
		{
			x = (rand() % 13) + 1;
			if (gamerNum == 2)
				y = rand() % 5 + 9;
			else
				y = (rand() % 5) + 1;
			if ((board[x][y]).isCellEmpty())
				found = 1;
		}
		//to ask how to do here cont
		sol.setCondition(soldierNum);
		sol.set(x, y, soldierNum++);
		(board[x][y]).update(soldierNum);
		found = 0;
	}
}

void Gamers::drowSoldiers()
{
	for (soldier& sol : soldiers)
		sol.draw();
}
void Gamers::setkeys(const char* keys)
{
	int i = 0;
	for (char& key : _keys)
		key = keys[i++];
}

void Gamers::notifyKeyHit(char ch)
{
	int i = 0, found = 0;
	if ((ch >= '1' && ch <= '3') && _gamerNum == 1)
		currSoldier = atoi(&ch);
	else if((ch >= '7' && ch <= '9') && _gamerNum == 2)
		currSoldier = atoi(&ch);
	else if (tolower(ch) == _keys[UP])
		setDirection(Direction::UP);
	else if (tolower(ch) == _keys[DOWN])
		setDirection(Direction::DOWN);
	else if (tolower(ch) == _keys[LEFT])
		setDirection(Direction::LEFT);
	else if (tolower(ch) == _keys[RIGHT])
		setDirection(Direction::RIGHT);


}

void Gamers::setName()
{
	cin >> name;
}

void Gamers::setDirection(Direction d)
{
	if (currSoldier <= 3)
		soldiers[currSoldier-1].setDirection(d);
	else
		soldiers[currSoldier - 7].setDirection(d);
}

void Gamers::printGamerName()
{
		cout << name;
}

void Gamers::printGamerScore()
{
	cout << score;
}


int Gamers::getScore()
{
	return score;
}

void Gamers::putScore(int _score)
{
	score = _score;
}

void Gamers::move(Cell board[Size][Size])
{
	if (currSoldier != -1) {
		if(currSoldier <= 3)
			soldiers[currSoldier - 1].move(board);
		else
			soldiers[currSoldier - 7].move(board);
	}
}