#include "FilesMap.h"

void FilesMap::setFile(char* argv, int argc, char* str)
{
	for (int i = 1; i < argc; i++)
	{
		//���� �� strcmpp
		if (strcmp(&argv[i], str) == 0) //�� ���� �� ����� �� ������ ��"�
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