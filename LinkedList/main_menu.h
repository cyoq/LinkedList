#pragma once

#include "pch.h"
#include "dictionary.h"
#include <vector>
#include <algorithm>


#define CHECK_LOAD() \
	if (!loaded) { std::cout << "Please load the file with the data before acting!" << std::endl; continue; }

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


void mainMenu(Dictionary &dict) {
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
			std::cout << "Size of dictionary is: " << dict.list.getSize() << std::endl;
		}
		else if (values[0] == "show") {
			CHECK_LOAD();
			dict.show();
		}
		else if (values[0] == "showtail") {
			CHECK_LOAD();
			dict.list.showTail();
		}
		else if (values[0] == "clear") {
			CHECK_LOAD();
			std::cout << "Clearing the list!" << std::endl;
			dict.list.clear();
			loaded = false;
		}
		else if (values[0] == "sort") {
			CHECK_LOAD();
			clock_t start = clock();
			dict.list.sort();
			clock_t end = clock();
			std::cout << "List has succesfully been sorted in " <<
				(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
		}
		else if (values[0] == "sorted" || values[0] == "s?") {
			CHECK_LOAD();
			std::cout << "List is sorted: " << (dict.list.isSorted() ? "true" : "false") << std::endl;
		}
		else if (values[0] == "sortload") {
			std::ifstream file(values[1]);
			if (!file.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Opening..." << std::endl;
				clock_t start = clock();
				dict.loadFromFileSorted(file);
				clock_t end = clock();
				std::cout << "File has succesfully been read in " << 
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
				loaded = true;
			}
		}
		else if (values[0] == "load") {
			std::ifstream file(values[1]);
			if (!file.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Opening..." << std::endl;
				clock_t start = clock();
				dict.loadFromFile(file);
				clock_t end = clock();
				std::cout << "File has succesfully been read in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
				loaded = true;
			}
		}
		else if (values[0] == "rawload") {
			std::ifstream file(values[1]);
			if (!file.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Opening..." << std::endl;
				clock_t start = clock();
				dict.loadFromFileRaw(file);
				clock_t end = clock();
				std::cout << "File has succesfully been read in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
				loaded = true;
			}
		}
		else if (values[0] == "save") {
			CHECK_LOAD();
			std::ofstream out(values[1]);
			if (!out.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Saving..." << std::endl;
				clock_t start = clock();
				dict.saveToFile(out);
				clock_t end = clock();
				std::cout << "File has succesfully been saved in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
			}
		}
		else if (values[0] == "fixfile") {
			CHECK_LOAD();
			std::ifstream in(values[1]);
			if (!in.good()) { std::cout << "File is corrupted! Please try again!" << std::endl; }
			else {
				std::cout << "Fixing..." << std::endl;
				clock_t start = clock();
				dict.fixWordsInFile(in);
				clock_t end = clock();
				std::cout << "File has succesfully been fixed in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
			}
		}
		else if (values[0] == "push") {
			CHECK_LOAD();
			dict.list.pushSorted(values[1]);
			std::cout << "Value has been pushed succesfully!" << std::endl;
		}
		else if (values[0] == "fix") {
			CHECK_LOAD();
			clock_t start = clock();
			std::string result = dict.findNearestWord(values[1]);
			clock_t end = clock();
			std::cout << "Did you mean: " << result << std::endl;
			std::cout << "Corrected word has succesfully been found in " <<
				(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
			
		}
		else if (values[0] == "find" || values[0] == "search") {
			CHECK_LOAD();
			clock_t start = clock();
			bool result = dict.search(values[1]);
			clock_t end = clock();
			if (result) {
				std::cout << "Value " << "\"" << values[1] << "\" " <<
					"is found in the dictionary!" << std::endl;
				std::cout << "Word has succesfully been found in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
			}
			else {
				std::cout << "Value " << "\"" << values[1] << "\" " <<
					"cannot be found in the dictionary!" << std::endl;
				std::cout << "Word has not been found in " <<
					(double)(end - start) / CLOCKS_PER_SEC << " seconds!" << std::endl;
			}
		}
		else {
			std::cout << "wrong!" << std::endl;
		}

	}
}