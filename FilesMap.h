#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;

class FilesMap {
	std::map<string, int> files;
	int size;
public:
	void setFile(char* argv, int argc, char* str);
	void add(char* str);
};
