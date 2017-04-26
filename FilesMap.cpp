#include "FilesMap.h"

void FilesMap::setFile(char* argv, int argc, char* str)
{
	for (int i = 1; i < argc; i++)
	{
		//לממש את strcmpp
		if (strcmp(&argv[i], str) == 0) //זה אומר אם הקובץ עם הסיומת הנ"ל
		{
			this->add(&argv[i]);
			//
		}
	}
}

void FilesMap::add(char* str)
{
	files[str]++;
}