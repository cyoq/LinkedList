
#include "pch.h"
#include "LinkedList.h"

template<typename T>
node<T>::node() {
	this->next = NULL;
}

template<typename T>
node<T>::node(T data) {
	this->data = data;
	this->next = NULL;
}

template<typename T>
node<T>::node(T data, node<T> *next) {
	this->data = data;
	this->next = next;
}


template<typename T>
void node<T>::pushSorted(node<T>*& head, const T & data, int &size) {
	if (head == NULL) { this->pushFront(head, data); size++; }
	if (head->data == data) { return; }
	else if (data > head->data) {
		this->pushSorted(head->next, data, size);
	}
	else {
		this->pushFront(head, data);
		size++;
	}
}

template<typename T>
void node<T>::pushFront(node<T>*& head, const T &data) {
	node<T> *newHead = new node<T>(data, head);
	head = newHead;
}

template<typename T>
void node<T>::pushBack(node<T>*& head, const T &data) {
	if (head == NULL) {
		head = new node<T>(data);
	}
	else {
		this->pushBack(head->next, data);
	}
}

template<typename T>
bool node<T>::pushAt(node<T>*& head, const T &data, int pos) {
	if (head == NULL) { return false; }
	if (pos == 0) {
		this->pushFront(head, data);
		return true;
	}
	else {
		this->pushAt(head->next, data, pos - 1);
	}
}

template<typename T>
bool node<T>::removeAt(node<T>*& head, int pos) {
	if (head == NULL) { return false; }
	if (pos == 0) {
		this->removeFront(head);
		return true;
	}
	else {
		this->removeAt(head->next, pos - 1);
	}

}

template<typename T>
void node<T>::removeFront(node<T>*& head) {
	if (head == NULL) { return; } 
	node<T> *newHead = head;
	head = head->next;
	delete newHead;
}

template<typename T>
void node<T>::removeBack(node<T>*& head) {
	if (head == NULL) { return; }
	if (head->next == NULL) {
		delete head;
		head = NULL;
	}
	else {
		this->removeBack(head->next);
	}
}



template struct node<int>;
template struct node<std::string>;
