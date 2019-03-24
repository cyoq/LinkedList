#include "pch.h"
#include "LinkedList.h"


template<typename T>
LinkedList<T>::LinkedList() {
	this->head = NULL;
	this->tail = NULL;
	_size = 0;
	_isSorted = false;
}


template<typename T>
LinkedList<T>::LinkedList(std::ifstream &file) {
	this->head = NULL;
	_size = 0;
	_isSorted = false;
	this->loadFromFile(file);
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
	/*obj._size = this->getSize();
	obj._isSorted = this->isSorted();
	obj.head = this->head;*/
}

template<typename T>
LinkedList<T>::~LinkedList() {
	node<T> *cursor = this->head;
	while (cursor != NULL) {
		node<T> *temp = cursor->next;
		delete cursor;
		cursor = temp;
	}
}


template<typename T>
void LinkedList<T>::show() {
	node<T> *temp = this->head;
	while (temp != NULL) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
}

template<typename T>
void LinkedList<T>::clear() {
	if (this->head == NULL || this->head->next == NULL) { return; }
	node<T> *cursor = this->head->next;
	while (cursor != NULL) {
		node<T> *temp = cursor->next;
		delete cursor;
		cursor = temp;
	}
	this->head = NULL;
	_size = 0;
}

template<typename T>
void LinkedList<T>::swap(node<T> * &a, node<T> * &b) {

	node<T> *p1 = a, *p2 = b, *p3 = b->next;

	a = p2;
	a->next = p1;
	a->next->next = p3;

	/*T temp = a->data;
	a->data = b->data;
	b->data = temp;*/

	//node<T> *prev = this->head;

	//if (a == this->head) { 
	//	node<T> *tempB = b;
	//	a->next = NULL; //a->next = null - destroy the chain between paired links
	//	a->next = tempB->next; //a->next = c
	//	tempB->next = a; //b->next = a
	//	this->head = tempB;
	//}
	//else {
	//	while (prev) {
	//		if (prev->next == a) { break; }
	//		prev = prev->next;
	//	}
	//	
	//	node<T> *temp = b->next;
	//	prev->next = b;
	//	b->next = a;
	//	a->next = temp;

	//	/*node<T> *tempB = b;
	//	a->next = NULL;
	//	a->next = tempB->next;
	//	tempB->next = a;
	//	curr = tempB;*/
	//
	//}

	
}

template<>
bool LinkedList<std::string>::containsNumber(const std::string &data) {
	return (data.find_first_of("0123456789") != std::string::npos);
}

template<>
bool LinkedList<std::string>::containsSymbols(const std::string & data) {
	return (data.find_first_of("!@#$;.,^&*()-_=+/:<>~`{}[]") != std::string::npos);
}

template<typename T>
void LinkedList<T>::sort() {

	for (node<T> *it = this->head; it->next; it = it->next) {
		for (node<T> *itj = this->head; itj->next; itj = itj->next) {
			if (itj->data > itj->next->data) {
				this->swap(itj, itj->next);
			}
		}
	}

	_isSorted = true;
}


template<>
void LinkedList<std::string>::sort() {

	/*for (node<std::string> *it = this->head; it->next; it = it->next) {
		for (node<std::string> *itj = this->head; itj->next; itj = itj->next) {
			if (strcmp(itj->data.c_str(), itj->next->data.c_str()) > 0) {
				this->swap(itj, itj->next);
			}
		}
	}*/
	

	bool swapped = true;
	while (swapped) {

		swapped = false;
		node <std::string> *inner = this->head;

		while (inner != NULL) {

			if (inner->next == NULL) { break; }
			if (strcmp(inner->data.c_str(), inner->next->data.c_str()) > 0) {
				this->swap(inner, inner->next);
				swapped = true;
			}

			inner = inner->next;
		}
	}
	

	_isSorted = true;
}


template<typename T>
bool LinkedList<T>::search(const T & data) {
	node<T> *temp = this->head;
	while (temp != NULL) {
		if (temp->data > data) {
			return false;
		}
		else if (temp->data == data) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}

template<typename T>
int LinkedList<T>::levDistance(const std::string & s1, const std::string & s2) {
	
	const int len1 = strlen(s1.c_str());
	const int len2 = strlen(s2.c_str());

	if (len1 == 0) { return 0; }
	if (len2 == 0) { return 0; }

	int **matrix = new int*[(len1 + 1)];
	for (int i = 0; i <= len1; i++) {
		matrix[i] = new int[(len2 + 1)];
	}
	
	matrix[0][0] = 0;

	for (int i = 1; i <= len1; i++) { matrix[i][0] = i; }
	for (int j = 1; j <= len2; j++) { matrix[0][j] = j; }

	
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			matrix[i][j] = std::min({
				matrix[i - 1][j] + 1,
				matrix[i][j - 1] + 1,
				matrix[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1),
			});
		}
	}

	int result = matrix[len1][len2];

	for (int i = 0; i <= len1; i++) { delete[] matrix[i]; }
	delete[] matrix;

	return result;
}


template<>
std::string LinkedList<std::string>::findNearestWord(const std::string & data) {
	
	std::string result;
	int minDistance = -1;
	node<std::string> *temp = this->head;
	while (temp != NULL) {
		int distance = levDistance(data, temp->data);
		if (distance < minDistance || minDistance == -1) {
			minDistance = distance;
			result = temp->data;
		}
		temp = temp->next;
	}

	return result;
}

template<typename T>
const int LinkedList<T>::getSize() {
	return _size;
}

template<typename T>
const bool LinkedList<T>::isSorted() {
	return _isSorted;
}

template<typename T>
bool LinkedList<T>::saveToFile(std::ofstream & file) {
	if (!file.good()) { std::cout << "cannot open file!" << std::endl; return false; }
	node<T> *temp = this->head;
	while (temp != NULL) {
		file << temp->data << std::endl;
		temp = temp->next;
	}
	file.close();
	return true;
}

template<>
void LinkedList<std::string>::toLower(std::string &data) {
	std::for_each(data.begin(), data.end(), [](char & c) {
		c = ::tolower(c);
	});
}

template<>
bool LinkedList<std::string>::loadFromFile(std::ifstream & file) {
	if (!file.good()) { return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			this->pushBackUnique(data);
		}
	}
	file.close();
	_isSorted = false;
	return true;
}


template<typename T>
bool LinkedList<T>::loadFromFile(std::ifstream & file) {
	if (!file.good()) { return false; }
	if (file.is_open()) {
		T data;
		while (file >> data) {
			this->pushBackUnique(data);
		}
	}
	file.close();
	_isSorted = false;
	return true;
}

template<>
bool LinkedList<std::string>::loadFromFileRaw(std::ifstream & file) {
	if (!file.good()) { return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			this->pushBack(data);
		}
	}
	file.close();
	_isSorted = false;
	return true;
}

template<typename T>
bool LinkedList<T>::loadFromFileRaw(std::ifstream & file) {
	if (!file.good()) { return false; }
	if (file.is_open()) {
		T data;
		while (file >> data) {
			this->pushBack(data);
		}
	}
	file.close();
	_isSorted = false;
	return true;
}

template<>
bool LinkedList<std::string>::loadFromFileSorted(std::ifstream & file) {
	if (!file.good()) { std::cout << "cannot open file!" << std::endl; return false; }
	if (file.is_open()) {
		std::string data;
		while (file >> data) {
			this->toLower(data);
			this->pushSorted(data);
		}
	}
	file.close();
	_isSorted = true;
	return true;
}

template<typename T>
bool LinkedList<T>::loadFromFileSorted(std::ifstream & file) {
	if (!file.good()) { std::cout << "cannot open file!" << std::endl; return false; }
	if (file.is_open()) {
		T data;
		while (file >> data) {
			this->pushSorted(data);
		}
	}
	file.close();
	_isSorted = true;
	return true;
}

template<>
void LinkedList<std::string>::fixWordsInFile(std::ifstream &file) {

	if (!file.good()) { std::cout << "cannot open file!" << std::endl; }

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

						//if(this->search(data)) { out << data; }
						out << this->findNearestWord(data);
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

template<typename T>
void LinkedList<T>::pushBackUnique(const T &data) {
	node<T> *newNode = new node<T>(data);
	bool unique = true;
	if (this->head == NULL) {
		this->head = newNode;
		this->tail = this->head;
		_size++;
	}
	else {
		node<T> *cursor = this->head;
		while (cursor->next != NULL) {
			if (data == cursor->data) { unique = false; break; }
			cursor = cursor->next;
		}

		if (unique) {
			cursor->next = newNode;
			this->tail = newNode;
			_size++;
		}
	}
}

template<typename T>
void LinkedList<T>::pushSorted(const T & data) {
	if (_isSorted) {
		this->head->pushSorted(this->head, data, _size);
	}
	else {
		this->sort();
		this->head->pushSorted(this->head, data, _size);
	}
}

template<typename T>
void LinkedList<T>::pushFront(const T &data) {
	this->head->pushFront(this->head, data);
	_size++;
	_isSorted = false;
}

template<typename T>
void LinkedList<T>::pushBack(const T &data) {
	//this->head->pushBack(this->head, data);
	node<T> *last = new node<T>(data);
	if (this->head == NULL) {
		head = last;
		tail = head;
	}
	else {
		tail->next = last;
		tail = last;
	}
	_size++;
	_isSorted = false;
}


template<typename T>
bool LinkedList<T>::pushAt(const T &data, int pos) {
	return this->head->pushAt(this->head, data, pos);
	_size++;
	_isSorted = false;
}


template<typename T>
void LinkedList<T>::removeFront() {
	this->head->removeFront(this->head);
	_size--;
}

template<typename T>
void LinkedList<T>::removeBack() {
	this->head->removeBack(this->head);
	_size--;
}

template<typename T>
bool LinkedList<T>::removeAt(int pos) {
	return this->head->removeAt(this->head, pos);
	_size--;
}




template class LinkedList<int>;
template class LinkedList<std::string>;
