
#include "GameManeger.h"

using namespace std;

void GameManeger::paramMenager()
{
	char buffer[4096];
	char* tempPath;
	if (path == nullptr)
	{
		tempPath = "cd";
		FILE* fp = _popen(tempPath, "r");
		while (fgets(buffer, 4095, fp))
		{
			path = buffer;
		}
		_pclose(fp);
	}

	char str[4095] = "2>NUL dir /a-d /b ";
	tempPath = strcat(str, path);
	
	FILE* fp = _popen(tempPath, "r");
	//FILE* fp = _popen("2>NUL dir /a-d /b C:\\Users\hadar\\Documents\\Visual Studio 2017\\Projects\\Test\\Test\\lib", "r");
	while (fgets(buffer, 4095, fp))
	{
		divideToFile(buffer);
	}
	_pclose(fp);

	if (ifMovesFile == true)
		menu();
	else
	{
		//
	}
	
}

void GameManeger::divideToFile(char *buffer)
{
	int i = 0;
	while (strncmp(buffer +i, ".",1) != 0) //פונקציה שבודקת את הסיומת
		i++;

	char* str = &buffer[i+1];
	if (strncmp(str, "moves-a_full",12)==0)
		movesAFiles.add(buffer);
	else if (strncmp(str, "moves-b_full",12) == 0)
		movesBFiles.add(buffer);
	else if (strncmp(str, "gboard",6) == 0)
		boardFile.add(buffer);

}

void GameManeger::justForTest() { //tests the board from file 
	ifstream textfile("C:\\Users\\Nofar Kedem Zada\\Downloads\\testsfiles\\board_bad_4.gboard");
	bool test = textfile.is_open();
	setBoardFromFile(textfile);
	textfile.close();
	printBoard();
	gamers[0].drowSoldiers();
	gamers[1].drowSoldiers();
	Sleep(80);
	clearScreen();
	printBoardFromFileErrors("board_bad_4.gboard");
	Sleep(80);
}

void GameManeger::commandLine(int argc, char* argv[])
{
	for (int i = 1; i<argc; i = i + 2)
		if (strcmp(argv[i], "-board") == 0)
		{
			if (strcmp(argv[i + 1], "f") == 0)
				ifBoardFile = true;
		}
		else if (strcmp(argv[i], "-moves") == 0)
		{
			if (strcmp(argv[i + 1], "f") == 0) {
				ifMovesFile = true;
			}
		}
		else if (strcmp(argv[i], "-path") == 0)
		{
			path = argv[i + 1];
		}

	paramMenager();

}
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
		case '5':
			recordGame = !recordGame;
			//initialization() - need to check if needed
			run();
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
void GameManeger::initialization() //אתחולים
{
	int gamerNum = 1;
	clearScreen();
	clearTheGame();
	win = false;
	gamers[0].setSoldiersRandom(board, gamerNum++);
	gamers[1].setSoldiersRandom(board, gamerNum);
	recordRandomBoard(board);
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
	char buff[3];
	
	while (!EXIT)
	{
		if (!win) {
			if (ifMovesFile == true)
			{
				/*
				ifstream movesFile("movesA");
				movesFile.getline(buff, sizeof(buff));
				gamers[0].readFromMovesFile(buff);

				ifstream movesFile("movesB");
				movesFile.getline(buff, sizeof(buff));
				gamers[1].readFromMovesFile(buff);
				*/
			}
			
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
				else if (!win && ifMovesFile == false) {
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
//get one file end set the board from it - need to implement separate func to get the files 
void GameManeger::setBoardFromFile(ifstream& inFile) { 
	string line;
	char currentChar;
	std::map<char, int> wrongCharMap;

	for (int i = 1; i < (int)Sizes::size; i++) {
		getline(inFile, line);
		for (int j = 1; j < (int)Sizes::size; j++) {
			currentChar = line.at(j - 1);
			if (currentChar == 'T') {
				board[j][i].setCellType((int)Type::fr);
			}
			else if (currentChar == 'S') {
				board[j][i].setCellType((int)Type::sea);
			}
			else if (currentChar == 'A') {
				if (SetACounter == 0) {
					board[j][i].setCellType((int)Type::flagA);
				}
				SetACounter++;
			}
			else if (currentChar == 'B') {
				if (SetBCounter == 0) {
					board[j][i].setCellType((int)Type::flagB);
				}
				SetBCounter++;
			}
			else if (currentChar >= '1' && currentChar <= '3') {
				gamers[0].setSoldiersFromFile(board,currentChar-'0',j,i);
				updateSetSoliderCounter(currentChar - '0');
			}
			else if (currentChar >= '7' && currentChar <= '9') {
				gamers[1].setSoldiersFromFile(board,currentChar-'0',j,i);
				updateSetSoliderCounter(currentChar - '0');
			}
			else {//need to change here
				if (currentChar != ' ') {
					if (wrongCharMap.count(currentChar) != 0) {//if the char exists
						wrongCharMap[currentChar]++;
					}
					else {
						wrongCharsSet.push_back(currentChar);
						wrongCharMap[currentChar]++;
					}
				}
			}
		}
	}

}

void GameManeger::updateSetSoliderCounter(int solider) {
	if (solider == (int)GamerA::soldier1) {
		setSol1++;
	}
	if (solider == (int)GamerA::soldier2) {
		setSol2++;
	}
	if (solider == (int)GamerA::soldier3) {
		setSol3++;
	}
	if (solider == (int)GamerB::soldier7) {
		setSol7++;
	}
	if (solider == (int)GamerB::soldier8) {
		setSol8++;
	}
	if (solider == (int)GamerB::soldier9) {
		setSol9++;
	}
}

bool GameManeger::isBoardFromFileOK() {
	if (SetACounter != 1 || SetBCounter != 1 || wrongCharsSet.size() > 0) {
		return false;
	}

	else if (setSol1 != 1 || setSol2 != 1 || setSol3 != 1 || setSol7 != 1 || setSol8 != 1 || setSol9 != 1){
		return false;
	}
	else
		return true;
}

void GameManeger::printBoardFromFileErrors(string fileName) {
	if (SetACounter != 1 || setSol1 != 1 || setSol2 != 1 || setSol3 != 1) {
		cout << "Wrong settings for player A tools in file " << fileName << endl;
	}
	if (SetBCounter != 1 || setSol7 != 1 || setSol8 != 1 || setSol9 != 1) {
		cout << "Wrong settings for player B tools in file " << fileName << endl;
	}
	if (wrongCharsSet.size() > 0) {
		cout << "Wrong character on board : "<< wrongCharsSet <<" in file " << fileName << endl;
	}
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
char GameManeger::findCellType(Cell board[(int)Sizes::size][(int)Sizes::size],int j,int i)const {
	int cellType = board[j][i].returnedCellType();
	if (cellType != (int)Type::emptyType) {
		if (cellType == (int)Type::fr)
			return 'T';
		if (cellType == (int)Type::sea)
			return 'S';
		if (cellType == (int)Type::flagA)
			return 'A';
		if (cellType == (int)Type::flagB)
			return 'B';
	}
	else if (board[j][i].isAnyGamerExist()) {
		return ('0' + board[j][i].returnSoliderNumInCell());
	}
	else
		return ' ';
}

string GameManeger::findFileName() {
	string directoryPath = findDirPath();
	//need to insert all files from the path to a map - dedicated object need to complete
	//than find a free name and send it 

}

void GameManeger::recordRandomBoard(Cell board[(int)Sizes::size][(int)Sizes::size]) {
	string fileName;
	string line;
	char type;
	fileName = findFileName();
	ofstream recordedBorad("test.txt");
	for (int i = 1; i < (int)Sizes::size; i++) {
		line.clear();
		for (int j = 1; j < (int)Sizes::size; j++) {
			type = findCellType(board,j,i);
			line.push_back(type);
		}
		recordedBorad << line << '#' << i <<endl;
	}
	recordedBorad.close();
}

