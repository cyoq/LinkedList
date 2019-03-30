#pragma once


#include "linked_list.h"


class Dictionary {

public:
	Dictionary();
	~Dictionary();
	friend void mainMenu(Dictionary &dict);
	void show();
	bool search(const std::string &data);
	bool saveToFile(std::ofstream &file);
	bool loadFromFile(std::ifstream &file);
	bool loadFromFileRaw(std::ifstream &file);
	bool loadFromFileSorted(std::ifstream &file);
	void fixWordsInFile(std::ifstream &file);
	std::string findNearestWord(const std::string &data);
	

private:
	LinkedList<std::string> list;

	friend void setIsSorted(LinkedList<std::string> &list, bool res) { list._isSorted = res; }
	bool containsNumber(const std::string &data);
	bool containsSymbols(const std::string &data);
	void toLower(std::string &data);
};

