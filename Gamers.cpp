#include "Gamers.h"
#define _CRT_SECURE_NO_WARNINGS
char Gamers::defualtName = 'A';
int Gamers::gamerNum = 1;

void Gamers::setSoldiersRandom(Cell board[(int)Sizes::size][(int)Sizes::size])
{
	int soldierNum;
	soldierDead = 0;
	if (_gamerNum == 1) {
		soldierNum = (int)GamerA::soldier1;
	}
	else {
		soldierNum = (int)GamerB::soldier7;
	}
	int x=0, y=0, found = 0;
	for (soldier& sol : soldiers)
	{
		sol.isAlive = true;
		while (!found)
		{
			x = (rand() % 13) + 1;
			if (_gamerNum == 2)
				y = rand() % 5 + 9;
			else
				y = (rand() % 5) + 1;
			if ((board[x][y]).isCellEmpty())
				found = 1;
		}
		sol.setCondition(soldierNum);
		sol.set(x, y, soldierNum);
		(board[x][y]).update(soldierNum++);
		found = 0;
	}
}

void Gamers::setSoldiersFromFile(Cell board[(int)Sizes::size][(int)Sizes::size], int solider, int x, int y) {
	if (solider >= (int)GamerA::soldier1 && solider <= (int)GamerA::soldier3) {
		soldiers[solider - 1].isAlive = true;
		soldiers[solider - 1].setCondition(solider);
		soldiers[solider - 1].set(x, y, solider);
		(board[x][y]).update(solider);
	}
	if (solider >= (int)GamerB::soldier7 && solider <= (int)GamerB::soldier9) {
		soldiers[solider - 7].isAlive = true;
		soldiers[solider - 7].setCondition(solider);
		soldiers[solider - 7].set(x, y, solider);
		(board[x][y]).update(solider);
	}
}

void Gamers::drowSoldiers() const
{
	for (soldier sol : soldiers)
	{
		if(sol.isAlive)
			sol.draw();
	}
		
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
	if (currSoldier <= (int)GamerA::soldier3)
		soldiers[currSoldier-1].setDirection(d);
	else
		soldiers[currSoldier - 7].setDirection(d);
}


void Gamers::putScore(int _score)
{
	score = _score;
}

//returns 0 if there is no attack OR solider num of the solider who fall if attack occured
int Gamers::move(Cell board[(int)Sizes::size][(int)Sizes::size],string& recordBufferA,string& recordBufferB)
{
	int movementResult;
	if (currSoldier != -1) {
		if (currSoldier <= (int)GamerA::soldier3) {
			if (soldiers[currSoldier - 1].isAlive) {
				movementResult = soldiers[currSoldier - 1].move(board);
				if (isRecordOn && (soldiers[currSoldier - 1]._x_dir != 0 || soldiers[currSoldier - 1]._y_dir != 0))
					recordMoveToBuffer(currSoldier, soldiers[currSoldier - 1]._x, soldiers[currSoldier - 1]._y, recordBufferA);
				return movementResult;
			}
		}
		else {
			if (soldiers[currSoldier - 7].isAlive)
				movementResult = soldiers[currSoldier - 7].move(board);
			if (isRecordOn && (soldiers[currSoldier - 7]._x_dir != 0 || soldiers[currSoldier - 7]._y_dir != 0))
				recordMoveToBuffer(currSoldier, soldiers[currSoldier - 7]._x, soldiers[currSoldier - 7]._y,recordBufferB);
			return movementResult;
		}
	}
	//else
		return 0;
}



void Gamers::updateOutSolider(int outSolider) {
	if(outSolider >= (int)GamerA::soldier1 && outSolider <= (int)GamerA::soldier3)
		soldiers[outSolider - 1].isAlive = false;
	else
		soldiers[outSolider - 7].isAlive = false;
	soldierDead++;
}

int Gamers::win() 
{
	clearScreen();
	if(quietMode == false)
		cout << "The gamer: " << name << " won this game" << endl;
	score++;
	return _gamerNum;
}

bool Gamers::readFromMovesFile(char* buff)
{
	char *col, *row;
	bool valid;
	currSoldier = *strtok(buff, " ,") - '0';
	col = strtok(NULL, " ,");
	row = strtok(NULL, " ,");
	if (currSoldier >= (int)GamerA::soldier1 && currSoldier <= (int)GamerA::soldier3)
		valid = soldiers[currSoldier - 1].setDirectionFromFile(col, row);
	else if (currSoldier >= (int)GamerB::soldier7 && currSoldier <= (int)GamerB::soldier9)
		valid = soldiers[currSoldier - 7].setDirectionFromFile(col, row);
	else
		valid = false;
	return valid;
}

void Gamers::recordMoveToBuffer(int tool, int col, int row,string& recordBuffer)
{
	char c_tool;
	c_tool = tool + '0';
	char c_col =  char(col + (int)convertToChar::capitalCol);
	string c_row = to_string(row);
	recordBuffer.append(1, c_tool);
	recordBuffer.append(1, c_col);
	recordBuffer.append(c_row);
	recordBuffer.append(",");	

}

