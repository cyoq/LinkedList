
#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>


template <typename T>
struct node {
	T data;
	node *next;

	node<T>();
	node<T>(T data);
	node<T>(T data, node<T> *next);
	void pushSorted(node<T> * &head, const T &data, int &size);
	void pushFront(node<T> * &head, const T &data);
	void pushBack(node<T> * &head, const T &data);
	bool pushAt(node<T> * &head, const T &data, int pos);
	void removeFront(node<T> * &head);
	void removeBack(node<T> * &head);
	bool removeAt(node<T> * &head, int pos);
};

template <typename T>
class LinkedList {

public:
	LinkedList<T>();
	LinkedList<T>(T *data, int n);
	LinkedList<T>(std::ifstream &file);
	LinkedList<T>(const LinkedList<T> &obj);
	~LinkedList<T>();
	void show();
	void swap(node<T> * &a, node<T> * &b);
	void sort();
	bool search(const T &data);
	const int getSize();
	const bool isSorted();
	bool saveToFile(std::ofstream &file);
	bool loadFromFile(std::ifstream &file);
	bool loadFromFileRaw(std::ifstream &file);
	bool loadFromFileSorted(std::ifstream &file);
	void pushBackUnique(const T &data);
	void pushFront(const T &data);
	void pushBack(const T &data);
	bool pushAt(const T &data, int pos);
	void pushSorted(const T &data);
	void removeFront();
	void removeBack();
	bool removeAt(int pos);
	node<T> *head;

private:
	node<T> *tail;
	int _size;
	bool _isSorted;
	void toLower(std::string &data);
};

