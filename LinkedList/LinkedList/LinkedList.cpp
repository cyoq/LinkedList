#include "pch.h"
#include "LinkedList.h"


template<typename T>
LinkedList<T>::LinkedList() {
	this->head = NULL;
	_size = 0;
	_isSorted = false;
}

template<typename T>
LinkedList<T>::LinkedList(T *data, int n) {
	_size = 0;
	_isSorted = false;
	if (this->head == NULL) {
		this->head = new node<T>();
	}
	node<T> *temp = this->head;
	for (int i = 0; i < n; i++) {
		temp->data = data[i];
		if (i < n - 1) {
			temp->next = new node<T>();
			temp = temp->next;
			_size++;
		}
	}
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
void LinkedList<T>::swap(node<T> * &a, node<T> * &b) {

	/*if (a == NULL) { return; }
	if (b == NULL) {return;}
	if (a->next == NULL) {return; }
	if (b->next == NULL) { return; }

	node<T> *firstPrev = NULL;
	node<T> *secondPrev = NULL;
	node<T> *current = this->head;

	while (current->next != a) {
		current = current->next;
	}

	firstPrev = current;
	current = this->head;

	while (current->next != b) {
		current = current->next;
	}

	secondPrev = current;
	current = a->next;

	firstPrev->next = b;
	secondPrev->next = a;

	a->next = b->next;
	b->next = current;*/


	T temp = a->data;
	a->data = b->data;
	b->data = temp;
}


template<typename T>
void LinkedList<T>::sort() {

	for (node<T> *it = this->head; it; it = it->next) {
		for (node<T> *itj = this->head; itj; itj = itj->next) {
			if (itj->next == NULL) { break; }
			if (itj->data > itj->next->data) {
				this->swap(itj, itj->next);
			}
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

template<typename T>
bool LinkedList<T>::loadFromFile(std::ifstream & file) {
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
	this->head->pushBack(this->head, data);
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

template<>
void LinkedList<std::string>::toLower(std::string data) {
	std::for_each(data.begin(), data.end(), [](char & c) {
		c = ::tolower(c);
	});
}



template class LinkedList<int>;
template class LinkedList<std::string>;
