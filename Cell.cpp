#include "Cell.h"

bool Cell::isCellEmpty()
{
	if (this->cellType == (int)Type::emptyType && this->GamerA == (int)GamerA::noGamerA && this->GamerB == (int)GamerB::noGamerB)
		return true;
	else
		return false;
}

void Cell::update(int soldierNum)
{
	if (soldierNum >= (int)GamerA::soldier1 && soldierNum <= (int)GamerA::soldier3)
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
		numOfGamer = 2;
		return this->GamerB;
	}
	else if (this->GamerB == 0)
	{
		numOfGamer = 1;
		return this->GamerA;
	}
	return 0;
}
bool Cell::isAnyGamerExist() {
	if (this->GamerA == 0 && this->GamerB == 0)
		return false;
	else
		return true;
}


void Cell::clear()
{
	GamerA = 0;
	GamerB = 0;
}