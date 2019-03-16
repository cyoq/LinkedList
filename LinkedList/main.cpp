// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <memory>
#include <time.h>
#include "timer.h"
#include "main_menu.h"
#include "LinkedList.h"


 

int countWords(std::ifstream &file) {
	int count = 0;
	for (std::string word; file >> word; ++count) { std::cout << count << std::endl; }
	return count;
}


int main() { 

	
	std::unique_ptr<LinkedList<std::string>> arr = std::make_unique<LinkedList<std::string>>();

	/*arr->pushBack("a");
	arr->pushBack("b");
	arr->pushBack("c");
	arr->pushBack("d");
	arr->pushBack("b");
	arr->pushBack("a");
	arr->pushBack("r");
	
	arr->show();

	arr->swap(arr->head, arr->head->next->next);

	std::cout << std::endl;

	arr->show();*/
	

	//std::cout << arr->levDistance("uou", "a") << std::endl;


	mainMenu(arr);

	std::cout << "Goodbye!" << std::endl;
	
	
	
	system("PAUSE");
}
