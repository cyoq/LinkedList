// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <memory>
#include <time.h>
#include "timer.h"
#include "main_menu.h"
#include "linked_list.h"
#include "dictionary.h"

 


int main() { 

	Dictionary dict;

	mainMenu(dict);

	std::cout << "Goodbye!" << std::endl;
	
	
	
	system("PAUSE");
}
