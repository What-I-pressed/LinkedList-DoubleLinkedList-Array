#include <iostream>
#include <string>
#include "Arrayy.h"
#include "Arrayy.cpp"

using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node() {
		this->value = 0;
		next = nullptr;
	}

	Node(int v) {
		this->value = v;
		next = nullptr;
	}

	Node(int v, Node*& n) {
		this->value = v;
		next = n;
	}

	void operator()(int v, Node*& n) {
		this->value = v;
		next = n;
	}
};

template <typename T>
class DoubleNode {
public:
	T value;
	short priority;
	DoubleNode* previous;
	DoubleNode* next;

	DoubleNode() {
		this->value = 0;
		this->priority = 99999;
		previous = nullptr;
		next = nullptr;
	}

	DoubleNode(int v, short p) {
		this->value = v;
		this->priority = p;
		previous = nullptr;
		next = nullptr;
	}

	DoubleNode(int v, short prior, DoubleNode<T>* p, DoubleNode<T>* n) {
		this->value = v;
		this->priority = prior;
		previous = p;
		next = n;
	}

	void operator()(int v, short prior, DoubleNode<T>* p, DoubleNode<T>* n) {
		this->value = v;
		this->priority = prior;
		previous = p;
		next = n;
	}

	void operator()(DoubleNode<T>* p, DoubleNode<T>* n) {
		previous = p;
		next = n;
	}
};

class LinkedList {
	Node* head;
public:
	LinkedList() {
		head = nullptr;
	}

	void addFront(int value) {
		Node* newHead = new Node(value, head);
		head = newHead;
	}

	void addBack(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
	}

	void removeFront() {
		if (head != nullptr) {
			Node* newNode = head;
			head = head->next;
			delete newNode;
		}
	}

	void removeBack() {
		if (head == nullptr) { return; }
		else if (head->next == nullptr) {
			delete head;
			head = nullptr;
			return;
		}
		else {
			Node* current = head;
			while (current->next->next != nullptr) {
				current = current->next;
			}
			delete current->next;
			current->next = nullptr;
		}
	}

	void insert(int index, int value) {
		if (index < 0) { return; }
		else if (head == nullptr || index == 0) {
			Node* newNode = new Node(value, head);
			head = newNode;
		}
		else if (index == 1) {
			Node* newNode = new Node(value, head->next);
			head->next = newNode;
		}
		else {
			Node* current = head;
			Node* newNode = new Node(value);
			int i = 1;
			while (i != index && current->next != nullptr) {
				i++;
				current = current->next;
			}
			if (i != index && i != index - 1) { return; }
			newNode->next = current->next;
			current->next = newNode;

		}
	}

	void remove(int index) {
		if (head == nullptr) { return; }
		else if (index == 0) {
			Node* current = head;
			head = head->next;
			delete current;
		}
		else {
			Node* current = head;
			for (int i = 1; i != index && current->next->next != nullptr; i++, current = current->next) {};
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
		}
	}

	int search_index(int index) {
		if (head == nullptr) { return -9999999; }
		Node* current = head;
		int i = 0;
		while (i != index && current->next != nullptr) {
			i++;
			current = current->next;
		}
		if (i != index) { return -9999999; }
		return current->value;
	}

	bool isEmpty()const {
		return head == nullptr ? true : false;
	}

	int getSize()const {
		Node* current = head;
		int i = 0;
		while (current != nullptr) {
			current = current->next;
			i++;
		}
		return i;
	}

	bool search(int v)const {
		Node* current = head;
		while (current != nullptr) {
			if (current->value == v) {
				return true;
			}
			current = current->next;
		}
		return false;
	}

	void info()const {
		cout << "\n--------------------------------------------------------------\n\n";
		Node* current = head;
		for (int i = 0; current != nullptr; i++) {
			cout << i << ")\t" << current->value << endl;
			current = current->next;
		}
		cout << "\n--------------------------------------------------------------\n\n";
	}

	~LinkedList() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

template <typename T>
class Queue {
	DoubleNode<T>* head;
public:
	Queue() {
		head = nullptr;
	}

	bool isEmpty() {
		return head == nullptr ? true : false;
	}

	void enQueue(T elem, short priority) {
		if (head == nullptr) {
			head = new DoubleNode<T>(elem, priority);
			return;
		}
		else if (head->priority > priority) {
			head = new DoubleNode<T>(elem, priority, nullptr, head);
			head->next->previous = head;
			return;
		}
		DoubleNode<T>* current = head;
		DoubleNode<T>* newNode = new DoubleNode<T>(elem, priority);
		while (current->next != nullptr ? true : current->priority > priority ? true : false) {
			if (current->priority > priority) {
				current->previous->next = newNode;
				newNode->previous = current->previous;
				newNode->next = current;
				current->previous = newNode;
				return;
			}
			current = current->next;
		}
		current->next = newNode;
		newNode->previous = current;
	}

	void deQueue() {
		if (head != nullptr) {
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
		}
	}

	void info()const {
		cout << "\n--------------------------------------------------------------\n\n";
		DoubleNode<T>* current = head;
		while (current != nullptr) {
			cout << current->value << "\t priority : " << current->priority << endl;
			current = current->next;
		}
		cout << "\n--------------------------------------------------------------\n\n";
	}

	~Queue() {
		DoubleNode<T>* temp;
		while (head != nullptr) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

void main() {
	LinkedList list;
	cout << "Is list empty : " << boolalpha << list.isEmpty() << endl;
	list.addBack(50);
	list.addFront(20);
	list.addFront(225);
	list.addFront(256);
	list.addFront(289);
	list.addBack(999);
	list.info();
	cout << "Is list empty : " << boolalpha << list.isEmpty() << endl;
	list.removeBack();
	list.removeFront();
	list.info();
	cout << "Is 256 on list : " << boolalpha << list.search(256) << endl;
	list.insert(2, 99999);
	list.insert(5, 100099);
	list.insert(0, 4040404);
	list.insert(1, -2222);
	list.info();
	list.remove(2);
	list.remove(7);
	list.remove(0);
	list.remove(1);
	list.info();
	cout << "Element with index 3 : " << list.search_index(3) << endl;
	cout << "Element with index 0 : " << list.search_index(0) << endl;
	cout << "Element with index 2 : " << list.search_index(2) << endl;
	cout << "\n###################################################################\n\n";
	Queue<int> list1;
	cout << "is queue emptty : " << boolalpha << list1.isEmpty() << endl;
	list1.enQueue(1, 4);
	list1.enQueue(2, 2);
	list1.enQueue(3, 1);
	list1.enQueue(4, 2);
	list1.enQueue(5, 6);
	list1.enQueue(6, 1);
	list1.enQueue(7, 0);
	list1.info();
	list1.deQueue();
	list1.info();
	list1.deQueue();
	list1.info();
	list1.deQueue();
	list1.info();
	cout << "\n###################################################################\n\n";
	Arrayy <int> arr1;
	Arrayy <short> arr2;
	arr1.add(5);
	arr1.add(4);
	arr1.add(3);
	arr1.add(2);
	arr1.add(1);
	cout << "Real size: " << arr1.getSize() << endl;
	arr1.setSize(6, 4);
	arr1.info();
	cout << "Upper bound: " << arr1.getUpperBound() << endl;
	cout << "Arr2 is empty: " << boolalpha << arr2.isEmpty() << endl;
	arr1.freeExtra();
	arr1.info();
	Arrayy <int> arr3(arr1);
	arr1.removeAll();
	arr3.info();
	cout << "Item with index [3] = " << arr3.getAt(3) << endl;
	arr3.setAt(3, 9);
	cout << "Now item with index [3] = " << arr3[3] << endl;
	arr1.add(0);
	arr1.add(-1);
	arr1.add(-2);
	arr1.add(-3);
	arr1.add(-4);
	arr3.append(arr1.getData(), arr1.getSize());
	arr3.info();
	arr3.insertAt(10, -5);
	arr3.insertAt(0, 6);
	arr3.info();
	arr3.removeAt(0);
	arr3.removeAt(10);
	arr3.info();
}