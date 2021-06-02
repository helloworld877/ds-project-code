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
	bool dequeue(T& head)
	
	{
		if (front == nullptr)
		{
			
			return false;
		}
			
		QNode<T>* temp = front;
		head = temp->GetItem();
		front = front->GetNext();
		if (front == nullptr)
			rear = nullptr;
		return true;
	}
	
	T peek()
	{
		if (this->front == nullptr)
		{
			return nullptr;
		}

		
		return this->front->GetItem();
	}
	
};