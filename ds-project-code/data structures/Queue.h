#pragma once
#include <iostream>
template <typename T>
class QNode
{
private:
	T item=NULL;
	QNode<T>* next;
public:
	QNode<T>(T item)
	{
		this->item = item;
		next = nullptr;
	}
	QNode<T>()
	{
		next = nullptr;
		item = NULL;
	
	}
	void SetNext(QNode<T>* next)
	{
		this->next = next;
	}
	QNode<T>* GetNext()
	{
		return next;
	}
	void SetItem(T item)
	{
		this->item = item;
	}
	T GetItem()
	{
		return item;
	}
};

template<typename T>
class Queue
{
private:
	QNode<T>* front;
	QNode<T>* rear;
public:
	Queue();
	
	void enqueue(T data);
	void dequeue();
	
};