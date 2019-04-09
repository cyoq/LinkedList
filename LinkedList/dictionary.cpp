
#include "pch.h"
#include "dictionary.h"
#include "levenshtein_distance.h"
#include <string>
#include <sstream>

Dictionary::Dictionary(std::ifstream &file) {
	this->loadFromFileSorted(file);
}

Dictionary::~Dictionary() {}

Dictionary::Dictionary(const Dictionary & d) {
	throw "Dictionary object cannot be copied!";
}

void Dictionary::show() {
	list.forEach([](const std::string &data) {
		std::cout << data << std::endl;
		return false;
	});
}

bool Dictionary::search(const std::string & data) {
	bool result = false;
	list.forEach([&data, &result](const std::string &listData) {
		if (strcmp(listData.c_str(), data.c_str()) > 0) { result = false; return true; }
		else if (strcmp(listData.c_str(), data.c_str()) == 0) { result = true; return true; }
		return false;
	});

	setIsSorted(list, true);
	return result;
}

void Dictionary::pushValue(const std::string & data) {
	list.pushSorted(data);
}

bool Dictionary::removeValue(const std::string & data) {
	bool result = false;
	int pos = 0;
	list.forEach([&data, &result, &pos](const std::string &listData) {
		if (strcmp(listData.c_str(), data.c_str()) > 0) { result = false; return true; }
		else if (strcmp(listData.c_str(), data.c_str()) == 0) { result = true; return true; }
		pos++;
		return false;
	});
	if (result) list.removeAt(pos);
	return result;
}

bool Dictionary::saveToFile(std::ofstream & file) {
	if (!file.good()) { std::cout << "cannot open the file!" << std::endl; return false; }

	list.forEach([&file](const std::string &data) {
		file << data << std::endl;
		return false;
	});

	file.close();
	return true;
}

bool Dictionary::loadFromFile(std::ifstream & file) {
	if (!file.good()) { std::cout << "Cannot open the file!" << std::endl; return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			list.pushBackUnique(data);
		}
	}
	list.assignTail();
	setIsSorted(list, false);
	file.close();
	return true;
}

bool Dictionary::loadFromFileRaw(std::ifstream & file) {
	if (!file.good()) { return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			list.pushBack(data);
		}
	}
	file.close();
	setIsSorted(list, false);
	return true;
}

bool Dictionary::loadFromFileSorted(std::ifstream & file) {
	if (!file.good()) { std::cout << "Cannot open the file!" << std::endl; return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			list.pushSorted(data);
		}
	}
	list.assignTail();
	setIsSorted(list, true);
	file.close();
	return true;
}

void Dictionary::fixWordsInFile(std::ifstream &input, std::ofstream &output) {

	if (!input.good()) { std::cout << "Cannot open the file!" << std::endl; }

	if (input.is_open()) {
		std::string data;
		char c;
		while (!input.eof())
		{
			input.get(c);
			if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
				data.push_back(c);
			}
			else {
				if (data != "") {
					if (this->containsNumber(data) || this->containsSymbols(data)) { output << data; }
					else {
						this->toLower(data);

						if (this->search(data)) { output << data; }
						else { output << this->findNearestWord(data); }
					}
					data.clear();
				}
				if (!input.eof()) output << c;
			}
		}
	}
	input.close();
	output.close();
}


std::string Dictionary::fixWordsInString(const std::string & data) {
	
	std::string tmp;
	
	std::string result;
	size_t size = data.size();

	for (int i = 0; i <= size; i++) {
		if (((data[i] >= 65 && data[i] <= 90) || (data[i] >= 97 && data[i] <= 122)) && data[i] != '\0') {
			tmp.push_back(data[i]);
		}
		else {
			if (data != "") {
				if (this->containsNumber(tmp) || this->containsSymbols(tmp)) { result.append(tmp); }
				else {
					this->toLower(tmp);

					if (this->search(tmp)) { result.append(tmp); }
					else { result.append(this->findNearestWord(tmp)); }
				}
				tmp.clear();
			}
			result.push_back(data[i]);
		}
	}
	return result;
}

std::string Dictionary::findNearestWord(const std::string & data) {
	std::string result;
	int minDistance = -1;
	list.forEach([&data, &result, &minDistance](const std::string &listData) {
		int distance = levenshteinDistance(data, listData);
		if (distance < minDistance || minDistance == -1) {
			minDistance = distance;
			result = listData;
		}
		return false;
	});

	return result;
}


bool Dictionary::containsNumber(const std::string & data) {
	return (data.find_first_of("0123456789") != std::string::npos);
}

bool Dictionary::containsSymbols(const std::string & data) {
	return (data.find_first_of("!@#$;.,^&*()-_=+/:<>~`{}[]") != std::string::npos);
}

void Dictionary::toLower(std::string & data) {
	std::for_each(data.begin(), data.end(), [](char & c) {
		c = ::tolower(c);
	});
}
