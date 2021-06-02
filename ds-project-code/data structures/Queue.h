#pragma once
#include <iostream>
template <typename T>
class QNode
{
private:
	T item;
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
	Queue()
	{
		front = rear = nullptr;
	}
	
	void enqueue(T& data)
	{
		{
			QNode<T>* temp = new QNode<T>(data);
			if (!rear)
			{
				front = rear = temp;
				return;
			}
			rear->SetNext(temp);
			rear = temp;
		}

	}
	void dequeue(T &item)
	{
		if (front == nullptr)
			return ;
		QNode<T>* temp = front;
		front = front->GetNext();
		if (front == nullptr)
			rear = nullptr;
		item=temp->GetItem();
	}
	
	T peek()
	{
		return this->front->GetItem();
	}
	
	bool isEmpty()
	{
		if (front == nullptr)
			return true;
		else
			return false;

	}
};
