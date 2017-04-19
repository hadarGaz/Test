
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
			initialization();
			run();
			getout = true;
			break;
		case '3':
			opositeGame = !opositeGame;
			initialization();
			run();
			getout = true;
			break;
		case '4':
			resetScore();
			cout << "Score was reset";
			break;
		case '9':
			getout = true;
			EXIT = 1;
			break;
		default:
			cout << "Unsupported option.." << endl;
		}

	}


}
void GameManeger::initialization() //אתחולים
{
	int gamerNum = 1;
	clearScreen();
	clearTheGame();
	win = false;
	gamers[0].setSoldiers(board, gamerNum++);
	gamers[1].setSoldiers(board, gamerNum);
	printing();
}

void GameManeger::printing()
{
	clearScreen();
	printBoard();
	gamers[0].drowSoldiers();
	gamers[1].drowSoldiers();
}
void GameManeger::run()
{
	char ch =0;
	bool gamerTurn = 0;
	int soliderOut = 0;
	
	while (!EXIT)
	{
		if (!win) {
			if (gamerTurn == 0)
			{
				soliderOut = gamers[0].move(board);
				updateSoldierOut(gamerTurn, soliderOut);
				gamerTurn = 1;
			}
			else
			{
				soliderOut = gamers[1].move(board);
				updateSoldierOut(gamerTurn, soliderOut);
				gamerTurn = 0;
			}
		}
		Sleep(80);
		
			if (_kbhit())
			{
				ch = getch();
				if (ch == ESC)
				{
					clearScreen();
					stopTheGame();
					seconderyMenu();
				}
				else if (!win) {
					gamers[0].notifyKeyHit(ch);
					gamers[1].notifyKeyHit(ch);
				
				}
			}
		
	}
	
}

void GameManeger::printBoard()
{
	char flag = 167;
	int typeofcell;
	int num = 1;
	printLetters();
	printEndLine();
	for (int i = 1; i < (int)Sizes::size; i++) {
		for (int j = 0; j < (int)Sizes::size; j++) {
			cout << "|";
			if (j == 0)
				printNumber(num++);
			else {
				typeofcell = board[j][i].returnedCellType();
				if (typeofcell == (int)Type::emptyType) {
					cout << "   ";
				}
				else if (typeofcell == (int)Type::fr) {
					setTextColor(BLACK, PURPLE);
					cout << "FR ";
					setTextColor(WHITE);
				}
				else if (typeofcell == (int)Type::sea) {
					setTextColor(BLACK, YELLOW);
					cout << "SEA";
					setTextColor(WHITE);
				}
				else if (typeofcell == (int)Type::flagA) {
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
	for (int i = 0; i < (int)Sizes::sizeOfGamers; i++) {
		cout << "Gamer: ";
		gamers[i].printGamerName();
		cout << " = ";
		gamers[i].printGamerScore();
		cout << endl;
	}

}



void GameManeger::setBoard()
{
	board[1][7].setCellType((int)Type::fr);
	board[1][8].setCellType((int)Type::fr);
	board[2][7].setCellType((int)Type::fr);
	board[3][4].setCellType((int)Type::fr);
	board[3][5].setCellType((int)Type::fr);
	board[3][6].setCellType((int)Type::fr);
	board[3][7].setCellType((int)Type::fr);
	board[4][6].setCellType((int)Type::fr);
	board[4][7].setCellType((int)Type::fr);
	board[4][8].setCellType((int)Type::fr);
	board[4][9].setCellType((int)Type::fr);

	board[8][6].setCellType((int)Type::sea);
	board[9][5].setCellType((int)Type::sea);
	board[9][6].setCellType((int)Type::sea);
	board[10][4].setCellType((int)Type::sea);
	board[10][5].setCellType((int)Type::sea);
	board[10][6].setCellType((int)Type::sea);
	board[10][7].setCellType((int)Type::sea);
	board[10][8].setCellType((int)Type::sea);
	board[10][9].setCellType((int)Type::sea);
	board[10][10].setCellType((int)Type::sea);
	board[11][7].setCellType((int)Type::sea);
	board[11][8].setCellType((int)Type::sea);
	board[11][9].setCellType((int)Type::sea);
	board[12][8].setCellType((int)Type::sea);

	board[11][1].setCellType((int)Type::flagA);
	board[2][13].setCellType((int)Type::flagB);

}

void GameManeger::printLetters()
{
	char ch = 'A';
	cout << "|" << "   ";
	for (int p = 1; p<(int)Sizes::size; p++)
		cout << "| " << ch++ << " ";
	cout << "|" << endl;
}

void GameManeger::printEndLine()
{
	for (int l = 0; l < (int)Sizes::size; l++)
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

void GameManeger::swapScore(int gamerTurn)
{
	
	if (gamerTurn == 0)
		gamers[1].win();
	else
		gamers[0].win();
	

}

void GameManeger::seconderyMenu()
{
	bool getout = false;
	char userchoise;
	while (!getout)
	{
		cout << "1. Return to game " << endl;
		cout << "2. Start new game" << endl;
		cout << "8. Go to the main menu" << endl;
		cout << "9. Exit" << endl;
		cin >> userchoise;
		switch (userchoise)
		{
		case '1':
			if (win) {
				cout << endl;
				cout << "Game was over, you can start new game" << endl;
				cout << endl;
			}
			else {
				printing();
				getout = true;
			}
			break;
		case '2':
			initialization(); 
			getout = true;
			break;
		case '8': 
			clearScreen();
			menu();
			getout = true;
			break;
		case '9':
			getout = true;
			EXIT = 1;
			break;
		default:
			cout << "Unsupported option.." << endl;
		}

	}
}

void GameManeger::resetScore()
{
	gamers[0].score = 0;
	gamers[1].score = 0;
}

void GameManeger::stopTheGame()
{
	for (int i = 0; i < (int)Sizes::sizeOfGamers; i++)
	{
		for (int j = 0; j < (int)Sizes::sizeOfSoldier; j++)
		{
			gamers[i].soldiers[j].stop();
		}
	}
	
}

void GameManeger::clearTheGame()
{
	for (int i = 0; i < (int)Sizes::size; i++)
	{
		for (int j = 0; j < (int)Sizes::size; j++)
		{
			board[i][j].clear();
		}
	}

}


void GameManeger::updateSoldierOut(int gamerTurn,int soliderOut)
{
		if (soliderOut == (int)Win::win) {
			stopTheGame();
			win = true;
			if (opositeGame) {
				swapScore(gamerTurn);
			}
			else
				gamers[gamerTurn].win();
			
		}

		if (soliderOut <= (int)GamerA::soldier3 && soliderOut >= (int)GamerA::soldier1) {
			gamers[0].updateOutSolider(soliderOut);
		}
		else if (soliderOut >= (int)GamerB::soldier7) {
			gamers[1].updateOutSolider(soliderOut);
		}

		if (gamerTurn == 0)
		{
			if (gamers[0].soldierDead == (int)Sizes::sizeOfSoldier) //all the soldier was dead
			{
				stopTheGame();
				win = true;
				if (opositeGame) {
					gamers[0].win();
				}
				else
					gamers[1].win();
			}
		}
		else
		{
			if (gamers[1].soldierDead == (int)Sizes::sizeOfSoldier) //all the soldier was dead
			{
				stopTheGame();
				win = true;
				if (opositeGame) {
					gamers[1].win();
				}
				else
					gamers[0].win();
			}
		}
}

