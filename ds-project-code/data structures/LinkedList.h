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

	Node<T>* get_head()
	{
		return this->Head;
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

	void remove(T* data)
	{
		Node<T>* ptr=Head;
		Node<T>* ptr2 = Head->getNext();
		while (ptr2)
		{
			if (ptr2->getItem()==*data)
			{
				ptr->setNext(ptr2->getNext());
				
				return;
			}
			ptr = ptr->getNext();
			ptr2 = ptr2->getNext();
		}
		
	}

	~LinkedList() 
	{
		clear();
	}

};



