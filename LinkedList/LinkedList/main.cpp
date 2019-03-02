// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <istream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "timer.h"
#include "LinkedList.h"


#define CHECK_LOAD() \
	if (!loaded) { std::cout << "Please load the file with the data before acting!" << std::endl; continue; } 

int countWords(std::ifstream &file) {
	int count = 0;
	for (std::string word; file >> word; ++count) { std::cout << count << std::endl; }
	return count;
}

size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}



int main() { 

	
	std::unique_ptr<LinkedList<std::string>> arr = std::make_unique<LinkedList<std::string>>();

	std::string str;
	std::vector<std::string> values;
	bool flag = true;
	bool loaded = false;

	while (flag) {

		std::cout << ">> ";

		
		std::getline(std::cin, str);
		split(str, values, ' ');
		if (values[0] == "quit" || values[0] == "q") {
			flag = false;
		}
		else if (values[0] == "help") {
			std::cout << "help menu" << std::endl;
		}
		else if (values[0] == "size") {
			CHECK_LOAD();
			std::cout << "Size of dictionary is: " << arr->getSize() << std::endl;
		}
		else if (values[0] == "show") {
			CHECK_LOAD();
			arr->show();
		} 
		else if (values[0] == "load") {
			std::ifstream file(values[1]);
			if (!file.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Opening..." << std::endl;
				arr->loadFromFileSorted(file);
				std::cout << "File has been read succesfully!" << std::endl;
				loaded = true;
			}
		}
		else if (values[0] == "save") {
			CHECK_LOAD();
			std::ofstream out(values[1]);
			if (!out.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Saving..." << std::endl;
				arr->saveToFile(out);
				std::cout << "File has been saved succesfully!" << std::endl;
			}
		}
		else if (values[0] == "push") {
			CHECK_LOAD();
			arr->pushSorted(values[1]);
			std::cout << "Value has been pushed succesfully!" << std::endl;
		}
		else if (values[0] == "find" || values[0] == "search") {
			CHECK_LOAD();
			if (arr->search(values[1])) {
				std::cout << "Value " << "\"" << values[1] << "\" " <<
					"is found in the dictionary!" << std::endl;
			}
			else {
				std::cout << "Value " << "\"" << values[1] << "\" " <<
					"cannot be found in the dictionary!" << std::endl;
			}
		}
		else {
			std::cout << "wrong!" << std::endl;
		}

	}

	std::cout << "Goodbye!" << std::endl;
	
	
	
	system("PAUSE");
}
