#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {

	struct Node {
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};

	Node* head;
	Node* tail;
	unsigned int count;

public:
	// Behaviors
	void PrintForward() const{
		Node* cur = head;
		while(cur != nullptr){
			std::cout << cur->data << " ";
			cur = cur->next;
		}
		std::cout << std::endl;
	}
	void PrintReverse() const{
		Node* cur = tail;
		while(cur != nullptr){
			std::cout << cur->data << " ";
			cur = cur->prev;
		}
		std::cout << std::endl;
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{return count;}
	Node* getHead(){return head;}
	T getData()const {return head->data;}
	const Node* getHead() const{return head;}
	Node* getTail(){return tail;}
	T getDataT()const {return tail->data;}
	const Node* getTail() const{return tail;}

	// Insertion
	void AddHead(const T& data){
		Node* newNode = new Node;
		newNode->data = data;
		if(head != nullptr){
			newNode->next = head;
			head->prev = newNode;
		}else{
			tail = newNode;
		}
		head = newNode;
		count++;
	}

	void AddTail(const T& data){
		Node* newNode = new Node;
		newNode->data = data;
		if(tail != nullptr){
			newNode->prev = tail;
			tail->next = newNode;
		} else{
			head = newNode;
		}
		tail = newNode;
		count++;
	}

	// Removal
	bool RemoveHead(){
		if(count == 0) return false;
		if(count == 1){
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		} else{
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
			count--;
			return true;
		}
	}

	bool RemoveTail(){
		if(count == 0) return false;
		if (count == 1){
			delete tail;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		} else {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
			count--;
			return true;
		}
	}
	void Clear(){while(RemoveTail()){}}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other) return *this;
		Clear();
		count = other.count;
		head = other.head;
		tail = other.tail;
		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
		return *this;
	}

	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if(this == &rhs) return *this;
		Node* current = rhs.head;
		Clear();
		while(current != nullptr) {
			AddTail(current->data);
			current = current->next;
		}
		return *this;
	}

	// Construction/Destruction
	LinkedList() : head(nullptr), tail(nullptr), count(0){}

	LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0){
		Node* current = list.head;
		while(current != nullptr) {
			AddTail(current->data);
			current = current->next;
		}
	}

	
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList(){
		Clear();
	}


};


