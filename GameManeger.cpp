
#include "GameManeger.h"

using namespace std;


void GameManeger::menu()
{
	bool getout = false;
	char userchoise;
	while (!getout)
	{
		cout << "1. Choose names for gamers" << endl;
		cout << "2. Start game" << endl;
		cout << "3. Start opisite game" << endl;
		cout << "4. Reset score" << endl;
		cout << "9. Exit" << endl;
		cin >> userchoise;
		switch (userchoise)
		{
		case '1':
			cout << "Choose name for the fisrt gamer" << endl;
			gamers[0].setName();
			cout << "Choose name for the second gamer" << endl;
			gamers[1].setName();
			break;
		case '2':
			startGame();
			break;
		case '3':
			clearScreen();
			swapScore();
			break;
		case '4':
			resetScore();
			cout << "Score was reset";
			break;
		case '9':
			getout = true;
			break;
		default:
			cout << "Unsupported option.." << endl;
		}

	}


}
void GameManeger::startGame()
{
	int gamerNum = 1;
	gamers[0].setSoldiers(board, gamerNum++);
	gamers[1].setSoldiers(board, gamerNum);
	run();
}
void GameManeger::run()
{
	char ch =0;
	bool gamerTurn = 0;
	int soliderOut = 0;
	clearScreen();
	printBoard();
	gamers[0].drowSoldiers();
	gamers[1].drowSoldiers();
	while (ch != ESC)
	{
		if (gamerTurn == 0)
		{
			soliderOut = gamers[0].move(board);
			updateSoldierOut(gamerTurn,soliderOut);
			gamerTurn = 1;
		}
		else
		{
			soliderOut = gamers[1].move(board);
			updateSoldierOut(gamerTurn, soliderOut);
			gamerTurn = 0;
		}
		Sleep(80);
		if (_kbhit())
		{
			ch = getch();
			gamers[0].notifyKeyHit(ch);
			gamers[1].notifyKeyHit(ch);
		}
	}
	clearScreen();
	stopTheGame();
	seconderyMenu();
}

void GameManeger::printBoard()
{
	char flag = 166;
	int typeofcell;
	int num = 1;
	printLetters();
	printEndLine();
	for (int i = 1; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			cout << "|";
			if (j == 0)
				printNumber(num++);
			else {
				typeofcell = board[j][i].returnedCellType();
				if (typeofcell == empty) {
					cout << "   ";
				}
				else if (typeofcell == fr) {
					cout << "FR ";
				}
				else if (typeofcell == sea) {
					cout << "SEA";
				}
				else if (typeofcell == flagA) {
					cout << " " << flag << "A";
				}
				else {
					cout << " " << flag << "B";
				}
			}
		}
		cout << "|" << endl;
		printEndLine();
	}
	cout << "SCORE: " << endl;
	for (int i = 0; i < SizeOfSoldier; i++) {
		cout << "Gamer: ";
		gamers[i].printGamerName();
		cout << " = ";
		gamers[i].printGamerScore();
		cout << endl;
	}

}



void GameManeger::setBoard()
{
	board[1][7].setCellType(fr);
	board[1][8].setCellType(fr);
	board[2][7].setCellType(fr);
	board[3][4].setCellType(fr);
	board[3][5].setCellType(fr);
	board[3][6].setCellType(fr);
	board[3][7].setCellType(fr);
	board[4][6].setCellType(fr);
	board[4][7].setCellType(fr);
	board[4][8].setCellType(fr);
	board[4][9].setCellType(fr);

	board[8][6].setCellType(sea);
	board[9][5].setCellType(sea);
	board[9][6].setCellType(sea);
	board[10][4].setCellType(sea);
	board[10][5].setCellType(sea);
	board[10][6].setCellType(sea);
	board[10][7].setCellType(sea);
	board[10][8].setCellType(sea);
	board[10][9].setCellType(sea);
	board[10][10].setCellType(sea);
	board[11][7].setCellType(sea);
	board[11][8].setCellType(sea);
	board[11][9].setCellType(sea);
	board[12][8].setCellType(sea);

	board[11][1].setCellType(flagA);
	board[2][13].setCellType(flagB);

}

void GameManeger::printLetters()
{
	char ch = 'A';
	cout << "|" << "   ";
	for (int p = 1; p<Size; p++)
		cout << "| " << ch++ << " ";
	cout << "|" << endl;
}

void GameManeger::printEndLine()
{
	for (int l = 0; l < Size; l++)
		cout << "====";
	cout << endl;
}


void GameManeger::printNumber(int num)
{
	
	if (num >= 10)
		cout << " " << num;
	else
		cout << " " << num << " ";
}

void GameManeger::swapScore()
{
	
	int scoreA = gamers[0].getScore();
	int scoreB = gamers[1].getScore();
	gamers[0].putScore(scoreA);
	gamers[1].putScore(scoreB);
	

}

void GameManeger::seconderyMenu()
{
	bool getout = false;
	while (!getout)
	{
		cout << "1. Return to game " << endl;
		cout << "2. Start new game" << endl;
		cout << "8. Go to the main menu" << endl;
		cout << "9. Exit" << endl;
		char userchoise;
		cin >> userchoise;
		switch (userchoise)
		{
		case '1':
			run();
			break;
		case '2':
			startGame();
			break;
		case '8':
			clearScreen();
			menu();
			break;
		case '9':
			getout = true;
			break;
		default:
			cout << "Unsupported option.." << endl;
		}

	}
}

void GameManeger::resetScore()
{
	/*
	for (Gamers& gamer : gamers)
		gamer.putScore(0);
		*/
	gamers[0].score = 0;
	gamers[1].score = 0;
}

void GameManeger::stopTheGame()
{
	for (int i = 0; i < SizeOfSoldier; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			gamers[i].soldiers[j].stop();
		}
	}
	
}

void GameManeger::updateSoldierOut(int gamerTurn,int soliderOut)
{
		if (soliderOut == -1) {
			stopTheGame();
			gamers[gamerTurn].win();
		}

		if (soliderOut <= 3 && soliderOut >= 1) {
			gamers[0].updateOutSolider(soliderOut);
		}
		else if (soliderOut >= 7) {
			gamers[1].updateOutSolider(soliderOut);
		}

		if (gamerTurn == 0)
		{
			if (gamers[0].soldierDead == 3) //all the soldier was dead
			{
				stopTheGame();
				gamers[1].win();
			}

		}
		else
		{
			if (gamers[1].soldierDead == 3) //all the soldier was dead
			{
				stopTheGame();
				gamers[0].win();
			}
		}
}

