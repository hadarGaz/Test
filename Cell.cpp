#include "Cell.h"

bool Cell::isCellEmpty()
{
	if (this->cellType == emptyType && this->GamerA == noGamerA && this->GamerB == noGamerB)
		return true;
	else
		return false;
}

void Cell::update(int soldierNum)
{
	if (soldierNum >= 1 && soldierNum <= 3)
		GamerA = soldierNum;
	else
		GamerB = soldierNum;
}

void Cell::setCellType(int num)
{
	this->cellType = num;
}

int Cell::returnedCellType()
{
	return this->cellType;

}

int Cell::returndGamer(int& numOfGamer)
{
	if (this->GamerA == 0) {
		return this->GamerB;
		numOfGamer = 2;
	}
	else
	{
		return this->GamerA;
		numOfGamer = 1;
	}
}
