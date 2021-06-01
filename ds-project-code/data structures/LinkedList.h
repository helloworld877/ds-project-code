#pragma once
#include <iostream>
using namespace std;

 //------------------------CLASS NODE---------------------------

template<typename T>
class Node
{
	T item;
	Node<T>* next;

public:
	Node(T paraItem)
	{
		next = NULL;
		item = paraItem;
	}
	T setItem(T paraItem)
	{
		item = paraItem;
	}
	T getItem()
	{
		return this->item;
	}
	T setNext(Node<T>* nextptr)
	{
		next = nextptr;
	}
	Node<T>* getNext()
	{
		return this->next;
	}
	~Node() {}
};

//------------------------LINKED LIST---------------------------

template<typename T>
class LinkedList
{
	Node<T>* Head;

public:

	LinkedList()
	{
		Head = NULL;
	}

	bool isEmpty()
	{
		if(Head == NULL)
		{
			return true;
		}
		return false;
	}

	int getLength()
	{
		int count = 0;
		Node<T>* ptr = Head;
		while (ptr)
		{
			count++;
			ptr = ptr->getNext();
		}
	}

	void clear()
	{
		Node<T>* ptr = Head;
		while (Head)
		{
			ptr = Head->getNext();
			delete Head;
			Head = ptr;
		}
	}

	void insert(T data)
	{
		Node<T>* Nptr = new Node(data);
		Nptr->setNext(Head);
		Head = Nptr;
	}

	void remove()
	{
		Node<T>* ptr;
		Head = Head->getNext();
		delete ptr;
	}


	~LinkedList() 
	{
		clear();
	}

};


