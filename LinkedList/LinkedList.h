
#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>


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
	LinkedList<T>(std::ifstream &file);
	LinkedList<T>(const LinkedList<T> &obj);
	~LinkedList<T>();
	void show();
	void sort();
	void clear();
	bool search(const T &data);
	int levDistance(const std::string &s1, const std::string &s2);
	T findNearestWord(const T &data);
	const int getSize();
	const bool isSorted();
	bool saveToFile(std::ofstream &file);
	bool loadFromFile(std::ifstream &file);
	bool loadFromFileRaw(std::ifstream &file);
	bool loadFromFileSorted(std::ifstream &file);
	void fixWordsInFile(std::ifstream &file);
	void pushBackUnique(const T &data);
	void pushFront(const T &data);
	void pushBack(const T &data);
	bool pushAt(const T &data, int pos);
	void pushSorted(const T &data);
	void removeFront();
	void removeBack();
	bool removeAt(int pos);

private:
	node<T> *head;
	node<T> *tail;
	int _size;
	bool _isSorted;
	void toLower(std::string &data);
	void swap(node<T> * &a, node<T> * &b);
	bool containsNumber(const std::string &data);
};

