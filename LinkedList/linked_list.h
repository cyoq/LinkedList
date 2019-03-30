
#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>



template <typename T>
class LinkedList {

public:

	LinkedList<T>() { 
		this->head = nullptr; 
		this->tail = nullptr; 
		_size = 0; 
		_isSorted = false;
	}

	~LinkedList<T>() {
		node<T> *cursor = this->head;
		while (cursor != nullptr) {
			node<T> *temp = cursor->next;
			delete cursor;
			cursor = temp;
		}
	}

	const int getSize() { return _size; }
	const bool isSorted() { return _isSorted; }

	template<typename F>
	void forEach(const F &fun) {
		if (this->head == nullptr) return;
		node<T> *cursor = this->head;
		while (cursor != nullptr) {
			if (fun(cursor->data)) break;
			cursor = cursor->next;
		}
		_isSorted = false;
	}

	void show() {
		node<T> *cursor = this->head;
		while (cursor != nullptr) {
			std::cout << cursor->data << std::endl;
			cursor = cursor->next;
		}
	}

	void clear() {
		if (this->head == nullptr || this->head->next == nullptr) { return; }
		node<T> *cursor = this->head->next;
		while (cursor != nullptr) {
			node<T> *temp = cursor->next;
			delete cursor;
			cursor = temp;
		}
		this->head = nullptr;
		_size = 0;
	}

	void sort() {
		bool swapped = true;
		while (swapped) {
	
			swapped = false;
			node<T> **inner = &this->head;
	
			while (*inner != nullptr) {
	
				if ((*inner)->next == nullptr) { break; }
				if ((*inner)->data > (*inner)->next->data) {
					this->swap(*inner);
					swapped = true;
				}
	
				inner = &(*inner)->next;
			}
		}
		_isSorted = true;
	}

	void assignTail() {
		node<T> *cursor = this->head;
		while (cursor->next != nullptr) {
			cursor = cursor->next;
		}
		tail = cursor;
	}

	void showTail() {
		std::cout << tail->data << std::endl;
	}

	void pushBack(const T &data) {
		node<T> *last = new node<T>(data);
		if (this->head == nullptr) {
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
	
	void pushBackUnique(const T &data) {
		node<T> *newNode = new node<T>(data);
		bool unique = true;
		if (this->head == nullptr) {
			this->head = newNode;
			this->tail = this->head;
			_size++;
		}
		else {
			node<T> *cursor = this->head;
			while (cursor->next != nullptr) {
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

	void pushFront(const T &data) { this->head = new node<T>(data, this->head); _size++; _isSorted = false; }

	bool pushAt(const T &data, int pos) {
		
		bool result = _pushAt(this->head, data, pos);
		if (result) {
			_size++;
			_isSorted = false;
		}
		return result;
	}
	
	void pushSorted(const T &data) {
		if (_isSorted) {
			_pushSorted(this->head, data, _size);
		}
		else {
			this->sort();
			_pushSorted(this->head, data, _size);
		}
	}

	void removeFront() {
		if (this->head == nullptr) { return; }
		node<T> *newHead = this->head;
		this->head = this->head->next;
		delete newHead;
		_size--;
	}
	
	void removeBack() {
		_removeBack(this->head, this->tail);
		_size--;
	}

	bool removeAt(int pos) {
		bool result = _removeAt(this->head, this->tail, pos);
		if (result) _size--;
		return result;
	}
	
private:

	template <typename T>
	struct node {
		T data;
		node<T> *next;

		node<T>(T data) { this->data = data; this->next = nullptr; }
		node<T>(T data, node<T> *next) { this->data = data; this->next = next; }
	};

	// ****** PRIVATE VARIABLES ****** //

	node<T> *head;
	node<T> *tail;
	int _size;
	bool _isSorted;

	// ****** METHODS ****** //

	template<typename T>
	friend void _pushSorted(node<T> * &head, const T &data, int &size) {
		if (head == nullptr) { head = new node<T>(data, head); size++; }
		if (data == head->data) { return; }
		else if (data > head->data) {
			_pushSorted(head->next, data, size);
		}
		else {
			head = new node<T>(data, head);
			size++;
		}
	}

	friend void _pushSorted(node<std::string> * &head, const std::string &data, int &size) {
		if (head == nullptr) { head = new node<T>(data, head); size++; }
		if (strcmp(data.c_str(), head->data.c_str()) == 0) { return; }
		else if (strcmp(data.c_str(), head->data.c_str()) > 0) {
			_pushSorted(head->next, data, size);
		}
		else {
			head = new node<T>(data, head);
			size++;
		}
	}

	friend void _removeBack(node<T> * &head, node<T> * &tail) {
		if (head == nullptr) { return; }
		if (head->next == nullptr) {
			delete head;
			head = nullptr;
		}
		else if (head->next->next == nullptr) {
			tail = head;
			_removeBack(head->next, tail);
		}
		else {
			_removeBack(head->next, tail);
		}
	}

	friend bool _pushAt(node<T> * &head, const T &data, int pos) {
		if (head == nullptr) { return false; }
		if (pos == 0) {
			head = new node<T>(data, head);
			return true;
		}
		else {
			_pushAt(head->next, data, pos - 1);
		}
	}

	friend bool _removeAt(node<T> * &head, node<T> * &tail, int pos) {
		if (head == nullptr) { return false; }
		if (pos == 0) {
			node<T> *newHead = head;
			head = head->next;
			delete newHead;
			return true;
		}
		else if (pos == 1 && head->next->next == nullptr) { 
			tail = head; 
			_removeAt(head->next, tail, pos - 1);
		}
		else {
			_removeAt(head->next, tail, pos - 1);
		}
	}

	//For dictionary class
	friend void setIsSorted(LinkedList<T> &list, bool res);

	void swap(node<T> * &a) {
		node<T> *p1 = a, *p2 = a->next, *p3 = a->next->next;
		a = p2;
		a->next = p1;
		a->next->next = p3;
	}

};

//Function specialization for optimization reasons

template<>
void LinkedList<std::string>::sort() {
	bool swapped = true;
	while (swapped) {

		swapped = false;
		node<std::string> **inner = &this->head;

		while (*inner != nullptr) {

			if ((*inner)->next == nullptr) { break; }
			if (strcmp((*inner)->data.c_str(), (*inner)->next->data.c_str()) > 0) {
				this->swap(*inner);
				swapped = true;
			}

			inner = &(*inner)->next;
		}
	}
	_isSorted = true;
}




