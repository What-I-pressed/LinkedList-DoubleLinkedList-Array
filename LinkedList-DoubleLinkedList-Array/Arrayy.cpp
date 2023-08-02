#include "Arrayy.h"
#include <iostream>

using namespace std;

template<typename T>
Arrayy<T>::Arrayy() {
	this->filledSize = 0;
	this->realSize = 0;
	this->grow = 0;
	arr = nullptr;
}

template<typename T>
Arrayy<T>::Arrayy(int s, int g, T* a) {
	this->filledSize = s;
	this->grow = g;
	if (s % g != 0) { this->realSize = (s / g + 1) * g; }
	else { this->realSize = s; };
	arr = new T[realSize];
	for (int i = 0; i < s; i++) {
		arr[i] = a[i];
	}
}

template<typename T>
Arrayy<T>::Arrayy(const Arrayy& a) {
	this->filledSize = a.filledSize;
	this->realSize = a.realSize;
	this->grow = a.grow;
	arr = new T[realSize];
	for (int i = 0; i < realSize; i++) {
		arr[i] = a.arr[i];
	}
}

template<typename T>
Arrayy<T>::Arrayy(Arrayy&& a) {
	this->filledSize = a.filledSize;
	this->realSize = a.realSize;
	this->grow = a.grow;
	arr = a.arr;
	a.arr = nullptr;
}

template<typename T>
Arrayy<T>::~Arrayy() {
	if (arr != nullptr) {
		delete[] arr;
	}
}

template<typename T>
void Arrayy<T>::info()const {
	cout << "-----------------------------------------------------------\n";
	cout << "Filled size: " << filledSize << endl;
	cout << "Real size: " << realSize << endl;
	cout << "Grow: " << grow << endl;
	for (int i = 0; i < realSize; i++) {
		cout << i << ")\t" << arr[i] << endl;
	}
	cout << "-----------------------------------------------------------\n";
	cout << endl;
}

template<typename T>
int Arrayy<T>::getSize() {
	return realSize;
}

template<typename T>
void Arrayy<T>::setSize(int s, int g) {
	int RS = s % g != 0 ? (s / g + 1) * g : s;
	if (this->realSize == s && this->grow == g) { return; }
	else {
		T* newArr = new T[RS];
		int S = realSize > s ? s : realSize;
		for (int i = 0; i < S; i++) {
			newArr[i] = this->arr[i];
		}
		if (arr != nullptr) { delete[] arr; }
		arr = newArr;
		this->realSize = RS;
		this->grow = g;
	}
}

template<typename T>
int Arrayy<T>::getUpperBound() {
	return filledSize > 0 ? filledSize - 1 : 0;
}

template<typename T>
bool Arrayy<T>::isEmpty() {
	return filledSize == 0 ? true : false;
}

template<typename T>
void Arrayy<T>::freeExtra() {
	if (this->filledSize != this->realSize) {
		this->realSize = filledSize;
		this->grow = 1;
		T* newArr = new T[realSize];
		for (int i = 0; i < realSize; i++) {
			newArr[i] = arr[i];
		}
		if (arr != nullptr) {
			delete[] arr;
		}
		arr = newArr;
	}
}

template<typename T>
void Arrayy<T>::removeAll() {
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
	}
	this->filledSize = 0;
	this->realSize = 0;
	this->grow = 0;
}

template<typename T>
T Arrayy<T>::getAt(int i) {
	return arr[i % realSize];
}

template<typename T>
void Arrayy<T>::setAt(int i, T value) {
	if (i > -1 && i < realSize) {
		this->arr[i] = value;
		if (i >= filledSize && i < realSize) {
			filledSize++;
		}
	}
	else {
		cout << "There is no item with such index" << endl;
	}
}

template<typename T>
T& Arrayy<T>::operator[](int i) {
	return arr[i % realSize];
}

template<typename T>
void Arrayy<T>::add(T value) {
	if (filledSize < realSize) {
		arr[filledSize] = value;
		filledSize++;
		return;
	}
	else {
		if (realSize == 0) { this->grow = 1; }
		int RS = (filledSize / grow + 1) * grow;
		T* newArr = new T[RS];
		for (int i = 0; i < realSize; i++) {
			newArr[i] = arr[i];
		}
		newArr[filledSize] = value;
		if (arr != nullptr) {
			delete[] arr;
		}
		arr = newArr;
		filledSize++;
		this->realSize = RS;
	}
}

template<typename T>
void Arrayy<T>::append(T* smth, int s) {
	int size = realSize + s;
	int RS = size % grow == 0 ? size : (size / grow + 1) * grow;
	T* newArr = new T[RS];
	int i = 0;
	for (; i < realSize; i++) {
		newArr[i] = arr[i];
	}
	for (; i < size; i++) {
		newArr[i] = smth[i - realSize];
	}
	if (arr != nullptr) {
		delete[] arr;
	}
	arr = newArr;
	this->filledSize += s;
	this->realSize = RS;
}

template<typename T>
T* Arrayy<T>::getData() {
	return arr;
}

template<typename T>
void Arrayy<T>::insertAt(int index, T value) {
	index %= realSize + 1;
	if (realSize == 0) { grow = 1; }
	int RS = realSize + grow;
	T* newArr = new T[RS];
	for (int i = 0, j = 0; i < realSize + 1; i++) {
		if (i == index) {
			newArr[i] = value;
			continue;
		}
		newArr[i] = arr[j++];
	}
	delete[] arr;
	arr = newArr;
	filledSize++;
	this->realSize = RS;
}

template<typename T>
void Arrayy<T>::removeAt(int index) {
	index %= realSize;
	int RS = (filledSize - 1) % grow == 0 ? filledSize - 1 : realSize;
	T* newArr = new T[RS];
	int* ch;
	int i = 0, j = 0;
	ch = RS == realSize ? &i : &j;
	for (; *ch < RS; i++) {
		if (i == index) {
			continue;
		}
		newArr[j++] = arr[i];
	}
	if (arr != nullptr) {
		delete[] arr;
	}
	arr = newArr;
	if (index < filledSize) {
		filledSize--;
	}
	this->realSize = RS;
}