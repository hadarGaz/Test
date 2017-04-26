#include "GameManeger.h"
#include <fstream>  //To be deleted


int main(int argc,char* argv)
{
	GameManeger().commandLine(argc,argv);
	GameManeger().menu();
	
}
