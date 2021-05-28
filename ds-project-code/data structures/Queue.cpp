#include <iostream>
#include "Queue.h"
using namespace std;

template<typename T>
Queue<T>::Queue()
{
	
	front = rear = nullptr;
	
}

template<typename T>
void Queue<T>::enqueue(T data)
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

template<typename T>
void Queue<T>::dequeue()
{
	if (front == nullptr)
		return;
	QNode<T>* temp = front;
	front = front->GetNext();
	if (front == nullptr)
		rear = nullptr;
	delete temp;
}
