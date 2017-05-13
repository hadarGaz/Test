#pragma once
#include "enum.h"
class Cell {
	
	int cellType =0;
	int GamerA=0;
	int GamerB=0;
public:
	bool isCellEmpty();
	void update(int soldierNum);
	void setCellType(int num);
	int returnedCellType() const;
	bool isAnyGamerExist();
	int returndGamer(int& numOfGamer);
	void clear();
	void clearGamer();
	int returnSoliderNumInCell()const;
};