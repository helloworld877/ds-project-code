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
	void setItem(T paraItem)
	{
		item = paraItem;
	}
	T getItem()
	{
		return this->item;
	}
	void setNext(Node<T>* nextptr)
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
		Node<T>* Nptr = new Node<T>(data);
		Nptr->setNext(Head);
		Head = Nptr;
	}

	void remove(Node<T>* del_ptr ,T& item)
	{
		Node<T>* ptr=this->Head;

		item = del_ptr->getItem();

		if (this->Head == del_ptr)
		{
			this->Head = this->Head->getNext();
			return;
		}

		if (del_ptr->getNext() == nullptr)
		{
			Node<T>* temp = this->Head;
			while (temp->getNext()->getNext() != NULL)
			{
				temp = temp->getNext();
			}
			temp->setNext(nullptr);
			return;
		}

		this->Head = this->Head->getNext();
		

		del_ptr->setItem(ptr->getItem());
				
	}

	Node<T>* get_head()
	{
		return this->Head;
	}



	~LinkedList() 
	{
		clear();
	}

};



