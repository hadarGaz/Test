#pragma once

class Cell {
	enum Type{emptyType,sea,fr,flagA,flagB};
	enum GamerA{noGamerA,soldier1,soldier2,soldier3};
	enum GamerB{ noGamerB,soldier7=7,soldier8=8,soldier9=9};
	int cellType =0;
	int GamerA=0;
	int GamerB=0;
public:

	bool isCellEmpty();
	void update(int soldierNum);
	void setCellType(int num);
	int returnedCellType();
	bool isAnyGamerExist();
	int returndGamer(int& numOfGamer);
	void clear();


};