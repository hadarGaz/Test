#include "GameManeger.h"
#include <fstream>  //To be deleted


int main(int argc,char* argv)
{
	//GameManeger().commandLine(argc,argv);
	//GameManeger().menu();
	ifstream textfile("C:\\Users\\Nofar Kedem Zada\\Downloads\\testsfiles\\test.txt");
	//textfile.open("board_ok_1.txt");
	bool test = textfile.is_open();
	GameManeger().setBoardFromFile(textfile);
	textfile.close();
	GameManeger().printBoard();
	
}
