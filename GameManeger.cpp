
#include "GameManeger.h"

using namespace std;

void GameManeger::paramMenager()
{
	char* tempPath;
	if (path == "NULL") //it mean current directory
	{
		openFolder("cd");
		size_t size = path.find_last_of("\n");
		path[size] = '\0';
	}

	char str[4095] = "2>NUL dir /a-d /b ";
	tempPath = strcat(str, path.c_str());
	openFolder(tempPath);
	
	currFileBoard = boardFile.files.begin();
	currFileMovesA = movesAFiles.files.begin();
	currFileMovesB = movesBFiles.files.begin();

	if (ifMovesFile == true)
	{
		while (GameOver == false)
		{
			uploadFiles();
			if (GameOver == false)
			{
				initialization();
				run();
				Sleep(50 * delay);
			}
			
		}
		endMessage();
	}
	else
	{
		menu();
		while (GameOver == false)
		{
			uploadFiles(); //check and set the file
			initialization();
			run();
			Sleep(50 * delay);
		}
		if (ifBoardFile == true)
			endMessage();
	}
	
}

void GameManeger::openFolder(char* tempPath)
{
	char buffer[4096];
	FILE* fp = _popen(tempPath, "r");
	while (fgets(buffer, 4095, fp))
	{
		if(path == "NULL")
			path = buffer; //new 13.5
		else
			divideToFile(buffer);
	}
	_pclose(fp);
}


void GameManeger::divideToFile(char *buffer)
{
	string fileName;
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

void GameManeger::commandLine(int argc, char* argv[])
{
	for (int i = 1; i < argc; i = i + 2)
	{
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
		else if (strcmp(argv[i], "-quiet") == 0)
		{
			if (ifBoardFile == true && ifMovesFile == true)
				quietMode = true;
			i--; // beacuse there is no parameter after quite
		}
		else if (strcmp(argv[i], "-delay") == 0)
		{
			if(quietMode == false)
				delay = *argv[i + 1];
		}
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
		cout << "5. Record/UnRecord game" << endl;
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
			uploadFiles();
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
			//cout << "Score was reset";
			break;
		case '5':
			recordGame = !recordGame;

			break;
		case '9':
			getout = true;
			EXIT = 1;
			GameOver = true;
			break;
		default:
			cout << "Unsupported option.." << endl;
		}

	}


}

void GameManeger::uploadFiles() //סידור לוח וחיילים
{
	clearTheGame();
	if (ifBoardFile == true)
		uploadBoardFromFile();
	else
	{
		setBoard();
		gamers[0].setSoldiersRandom(board);
		gamers[1].setSoldiersRandom(board);
/*
		if (recordGame) {
			gamers[0].isRecordOn = true;
			gamers[1].isRecordOn = true;

		}
		else {
			gamers[0].isRecordOn = false;
			gamers[1].isRecordOn = false;
		}
*/
	}
	if (ifMovesFile == true)
		updateFilePerGame();
}
void GameManeger::initialization() //אתחולים
{
	clearScreen();
	win = false;
	EXIT = false;
	SetACounter = 0, SetBCounter = 0;
	setSol1 = 0, setSol2 = 0, setSol3 = 0, setSol7 = 0, setSol8 = 0, setSol9 = 0;
	wrongCharsSet.clear();
	gamers[0].soldierDead = 0;
	gamers[1].soldierDead = 0;

	if(quietMode == false)
		printing();
}

void GameManeger::uploadBoardFromFile() //אתחולים
{
	bool isBoardOk = false;
	ifstream fileNameforBoard = openfile(currFileBoard, 0);
	setBoardFromFile(fileNameforBoard);
	isBoardOk = printAndCheckBoardFromFileErrors(currFileBoard->first);
	if (isBoardOk == false)
		GameOver = true;
}

void GameManeger::printing() const
{
	clearScreen();
	printBoard();
	gamers[0].drowSoldiers();
	gamers[1].drowSoldiers();
}
void GameManeger::run()
{
	if (ifMovesFile == true)
		runFromMovesFile();
	else
		runFromKeyBordMoves();

	if (ifBoardFile)
	{
		currFileBoard++;
		if (currFileBoard == boardFile.files.end())
			GameOver = true;
	}
}
void GameManeger::runFromKeyBordMoves()
{
	char ch = 0;
	bool gamerTurn = 0;
	int soliderOut = 0;
	ofstream movesArecord;
	ofstream movesBrecord;
	if (recordGame) {
		recordToFiles(movesArecord, movesBrecord);
		gamers[0].isRecordOn = true;
		gamers[1].isRecordOn = true;
	}
	else {
		gamers[0].isRecordOn = false;
		gamers[1].isRecordOn = false;
	}
	while (!EXIT)
	{
		if (!win)
		{
			if (gamerTurn == 0)
			{
				soliderOut = gamers[0].move(board, recordBufferA, recordBufferB);
				updateSoldierOut(gamerTurn, soliderOut);
				gamerTurn = 1;
			}
			else
			{
				soliderOut = gamers[1].move(board, recordBufferA, recordBufferB);
				updateSoldierOut(gamerTurn, soliderOut);
				gamerTurn = 0;
			}

			Sleep(delay);
		}
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
	writeToMoveFiles(movesArecord, movesBrecord);
	movesArecord.close();
	movesBrecord.close();
	recordBufferA.clear();
	recordBufferB.clear();
}
void GameManeger::runFromMovesFile()
{
	bool validRowFromLine = false;
	int soliderOut = 0;
	char buff[1024];
	static int GameCycle = 0;
	int numOfMoves = 0;
	char winner = '0';
	ifstream fileNameforGamerA = openfile(currFileMovesA, 1);
	ifstream fileNameforGamerB = openfile(currFileMovesB, 2);
	GameCycle++;
	while (!win)
	{
		numOfMoves++;
		if (gamer1Active == true)
		{
			if (fileNameforGamerA.good() == true)
			{
				fileNameforGamerA.getline(buff, sizeof(buff) - 1);
				validRowFromLine = gamers[0].readFromMovesFile(buff); //and set direction
				if (validRowFromLine == true)
				{
					soliderOut = gamers[0].move(board, recordBufferA, recordBufferB);
					winner = updateSoldierOut(0, soliderOut);
				}
			}
			else
				gamer1Active = false;

		}

		if (quietMode == false)
			Sleep(delay);

		if (gamer2Active == true)
		{
			if (fileNameforGamerB.good() == true)
			{
				fileNameforGamerB.getline(buff, sizeof(buff) - 1);
				validRowFromLine = gamers[1].readFromMovesFile(buff); //and set direction
				if (validRowFromLine == true)
				{
					soliderOut = gamers[1].move(board, recordBufferA, recordBufferB);
					winner = updateSoldierOut(1, soliderOut);
				}

			}
			else
				gamer2Active = false;
		}
		else if (gamer1Active == false && gamer2Active == false)
		{
			win = true;
		}
	}
	fileNameforGamerA.close();
	fileNameforGamerB.close();
	if (quietMode == true)
	{
		if(winner == 'A')
			endMessagePerGame(GameCycle, 2 * numOfMoves-1, winner);
		else
			endMessagePerGame(GameCycle, 2 * numOfMoves, winner);

	}
}

void GameManeger::endMessagePerGame(int GameCycle, int numOfMoves, char winner) const
{
	clearScreen();
	cout << "Game cycle: " << GameCycle << endl;
	cout << "Num moves: " << numOfMoves << endl;
	if(winner == '0')
		cout << "Wineer: NONE" << endl;
	else
		cout << "Wineer: " << winner << endl;
}

void GameManeger::printBoard() const
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
		cout << "Gamer: "<< gamers[i].name;
		cout << " = " << gamers[i].score << endl;
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
			else if ((currentChar- '0' >= (int)GamerA::soldier1) && (currentChar-'0' <= (int)GamerA::soldier3)) {
				updateSetSoliderCounter(currentChar - '0');
				if (setSol1 <= 1 || setSol2 <= 1 || setSol3 <= 1)
					gamers[0].setSoldiersFromFile(board,currentChar-'0',j,i);
					

			}
			else if (currentChar - '0' >= (int)GamerB::soldier7 && currentChar - '0' <= (int)GamerB::soldier9) {
				updateSetSoliderCounter(currentChar - '0');
				if (setSol7 <= 1 || setSol8 <= 1 || setSol9 <= 1)
					gamers[1].setSoldiersFromFile(board, currentChar - '0', j, i);	
			}
			else {
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


bool GameManeger::printAndCheckBoardFromFileErrors(string fileName) const {
	bool isBoardOk = true;
	if (SetACounter != 1 || setSol1 != 1 || setSol2 != 1 || setSol3 != 1) {
		cout << "Wrong settings for player A tools in file " << fileName << endl;
		isBoardOk = false;
	}
	if (SetBCounter != 1 || setSol7 != 1 || setSol8 != 1 || setSol9 != 1) {
		cout << "Wrong settings for player B tools in file " << fileName << endl;
		isBoardOk = false;
	}
	if (wrongCharsSet.size() > 0) {
		cout << "Wrong character on board : "<< wrongCharsSet <<" in file " << fileName << endl;
		isBoardOk = false;
	}
	return isBoardOk;
}

void GameManeger::printLetters() const
{
	char ch = 'A';
	cout << "|" << "   ";
	for (int p = 1; p<(int)Sizes::size; p++)
		cout << "| " << ch++ << " ";
	cout << "|" << endl;
}

void GameManeger::printEndLine()const
{
	for (int l = 0; l < (int)Sizes::size; l++)
		cout << "====";
	cout << endl;
}


void GameManeger::printNumber(int num) const
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
			uploadFiles();
			initialization(); 
			getout = true;
			EXIT = 1;
			break;
		case '8': 
			clearScreen();
			stopTheGame();
			menu();
			getout = true;
			EXIT = 1;
			break;
		case '9':
			getout = true;
			EXIT = 1;
			GameOver = true;
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


char GameManeger::updateSoldierOut(int gamerTurn,int soliderOut)
{
	int gamerNum = -1;
		if (soliderOut == (int)Win::win) {
			stopTheGame();
			win = true;
			if (opositeGame) {
				swapScore(gamerTurn);
			}
			else
				gamerNum = gamers[gamerTurn].win();
			
		}

		if (soliderOut <= (int)GamerA::soldier3 && soliderOut >= (int)GamerA::soldier1) {
			gamers[0].updateOutSolider(soliderOut);
		}
		else if (soliderOut >= (int)GamerB::soldier7) {
			gamers[1].updateOutSolider(soliderOut);
		}

			if (gamers[0].soldierDead == (int)Sizes::sizeOfSoldier) //all the soldier was dead
			{
				stopTheGame();
				win = true;
				if (opositeGame) {
					gamerNum = gamers[0].win();
				}
				else
					gamerNum = gamers[1].win();
			}
	
			if (gamers[1].soldierDead == (int)Sizes::sizeOfSoldier) //all the soldier was dead
			{
				stopTheGame();
				win = true;
				if (opositeGame) {
					gamerNum = gamers[1].win();
				}
				else
					gamerNum = gamers[0].win();
			}

		if (gamerNum == 1)
			return 'A';
		else if (gamerNum == 2)
			return 'B';
		else
			return '0';
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


void GameManeger::recordRandomBoard(string fileName) {
	string line;
	char type;
	ofstream recordedBorad(fileName);
	bool ok = recordedBorad.is_open();
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



int GameManeger::cmpBetweenString(map<string, int>::iterator str1, map<string, int>::iterator str2)
{
	int res;
	size_t indexstr1 = str1->first.find_last_of(".");
	size_t indexstr2 = str2->first.find_last_of(".");
	res = str1->first.substr(0, indexstr1).compare(str2->first.substr(0, indexstr2));
	return res;
}
void GameManeger::updateFilePerGame()
{
	int res;
	bool found = false;
	gamer1Active = false;
	gamer2Active = false;
	if (ifBoardFile == true)
	{
		if (ifMovesFile == true)
		{
			while (currFileMovesA != (movesAFiles.files.end()) && (res = cmpBetweenString(currFileBoard, currFileMovesA)) >= 0 && found == false)
			{
			
					if (res == 0)
					{
						gamer1Active = true;
						found = true;
					}
					else
						currFileMovesA++;
			}
			found = false;
			while ((currFileMovesB != movesBFiles.files.end()) && (res = cmpBetweenString(currFileBoard, currFileMovesB)) >= 0 && found == false)
			{
				if (res == 0)
				{
					gamer2Active = true;
					found = true;
				}
				else
					currFileMovesB++;
			}
			if (gamer1Active == false && gamer2Active == false)
			{
				GameOver = true;
			}
		}
	}
	

}

ifstream GameManeger::openfile(map<string, int>::iterator file, int numOfGamer)
{
	ifstream movesFile;
	bool contin = false;
	if(numOfGamer == 0)
		contin = true;
	if (numOfGamer == 1 && gamer1Active == true)
		contin = true;
	else if (numOfGamer == 2 && gamer2Active == true)
		contin = true;

	if (contin == true)
	{
		const char* tempPath = path.c_str();
		string fullPath = tempPath;
		fullPath.append("\\");
		fullPath.append(file->first);
		size_t indexstr1 = fullPath.find_last_of("\n"); //support \n and \r
		fullPath[indexstr1] = '\0';
		ifstream movesFile(fullPath);
		bool ok = movesFile.is_open();
		return movesFile;
	}
	return movesFile;
}

ofstream GameManeger::openfileForRecord(map<string, int>::iterator file, int numOfGamer) {
	string boardFileName;
	boardFileName = file->first;
	size_t sufix = boardFileName.find(".gboard");
	boardFileName.erase(sufix,8);

	string fullPath = path;
	fullPath.append("\\");
	fullPath.append(boardFileName);
	if (numOfGamer == 1) {
		fullPath.append(".moves-a_full");
	}
	if (numOfGamer == 2) {
		fullPath.append(".moves-b_full");
	}
	ofstream movesFile(fullPath);
	bool ok = movesFile.is_open();
	return movesFile;
}

ofstream GameManeger::openfileForRecord(int numOfGamer, string randomName)
{	
	if (numOfGamer == 1) {
		randomName.append(".moves-a_full");
	}
	if (numOfGamer == 2) {
		randomName.append(".moves-b_full");
	}
	ofstream movesFile(randomName);
	bool ok = movesFile.is_open();
	return movesFile;
}

string GameManeger::RandomNameGenerator()
{
	//generate name for the files
	string randomName = "random_";
	string fullPath = path;
	GameNumber++;
	char numToAdd = GameNumber + '0';
	randomName.append(1, numToAdd);
	fullPath.append("\\");
	fullPath.append(randomName);
	return fullPath;
}

void GameManeger::recordToFiles(ofstream& movesA, ofstream& movesB)
{
	
	if (ifBoardFile && recordGame) {
		//get the names from the board and open the moves files
		movesA = openfileForRecord(currFileBoard, 1);
		movesB = openfileForRecord(currFileBoard, 2);
	}
	if (!ifBoardFile && recordGame) {
		//generate name and open 3 file - board + moves
		string fileName = RandomNameGenerator();
		fileName.append(".gboard");
		recordRandomBoard(fileName);
		fileName = fileName.substr(0,fileName.find(".gboard"));
		movesA = openfileForRecord(1, fileName);
		movesB = openfileForRecord(2, fileName);
	}

}

void GameManeger::writeToMoveFiles(ofstream & movesA, ofstream & movesB)
{
	char* token = strtok(&recordBufferA[0],",");
	while(token != NULL) {
		int i = 0;
		movesA << token[i] << "," << token[i + 1] << "," << token[i + 2];
		if (token[i + 3] != '\0') {
			movesA << token[i + 3] << endl;
		}
		else
			movesA << endl;
		token = strtok(NULL,",");
	}
	char* token1 = strtok(&recordBufferB[0], ",");
	while (token1 != NULL) {
		int i = 0;
		movesB << token1[i] << "," << token1[i + 1] << "," << token1[i + 2];
		if (token1[i + 3] != '\0') {
			movesB << token1[i + 3] << endl;
		}
		else
			movesB << endl;
		token1 = strtok(NULL, ",");
	}
}

void GameManeger::endMessage() const
{
	clearScreen();
	cout << "Game Summary" << endl;
	cout << "A points - " << gamers[0].score << endl;
	cout << "B points - " << gamers[1].score << endl;
}


