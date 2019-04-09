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

	std::ifstream file("20.txt");

	Dictionary dict(file);

	/*std::string chars("baught me fram da shap fisk");
	
	std::cout << dict.fixWordsInString(chars) << "\n";

	dict.show();

	std::cout << "\n";

	dict.pushValue("lol");
	dict.pushValue("everything");
	dict.pushValue("zzz");

	dict.show();

	bool res = dict.removeValue("everything");

	std::cout << "\n";

	dict.show();

	std::cout << "\n";
	std::cout << res << std::endl;*/
	

	mainMenu(dict);

	std::cout << "Goodbye!" << std::endl;
	
	
	
	system("PAUSE");
}
