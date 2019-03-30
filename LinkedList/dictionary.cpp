
#include "pch.h"
#include "dictionary.h"
#include "levenshtein_distance.h"

Dictionary::Dictionary() {}

Dictionary::~Dictionary() {}

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
	});

	setIsSorted(list, true);
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

void Dictionary::fixWordsInFile(std::ifstream &file) {

	if (!file.good()) { std::cout << "Cannot open the file!" << std::endl; }

	std::ofstream out("fixed.txt");

	if (file.is_open()) {
		std::string data;
		char c;
		while (!file.eof())
		{
			file.get(c);
			if (c == '\t' || c == '\n' || c == ' ' || file.eof()) {
				if (data != "") {
					if (this->containsNumber(data) || this->containsSymbols(data)) { out << data; }
					else {
						this->toLower(data);

						if (this->search(data)) { out << data; }
						else { out << this->findNearestWord(data); }
					}
					data.clear();
				}
				if (!file.eof()) out << c;
			}
			else {
				data.push_back(c);
			}
		}
	}
	file.close();
	out.close();
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
