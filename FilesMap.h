#pragma once
#include <iostream>
#include <map>
#include <string>

using namespace std;

class FilesMap {
	std::map<string, int> files;
	int size;
public:
	void add(const string& str);
	friend class GameManeger;
};
