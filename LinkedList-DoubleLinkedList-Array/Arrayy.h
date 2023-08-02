#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Arrayy
{
	int filledSize;
	int realSize;
	int grow;
	T* arr;
public:
	Arrayy();

	Arrayy(int s, int g, T* a);


	Arrayy(const Arrayy& a);

	Arrayy(Arrayy&& a);

	~Arrayy();

	void info()const;

	int getSize();

	void setSize(int s, int g);

	int getUpperBound();

	bool isEmpty();

	void freeExtra();

	void removeAll();

	T getAt(int i);

	void setAt(int i, T value);

	T& operator[](int i);

	void add(T value);

	void append(T* smth, int s);

	T* getData();

	void insertAt(int index, T value);

	void removeAt(int index);
};


