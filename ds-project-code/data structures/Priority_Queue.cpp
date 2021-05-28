#include "Priority_Queue.h"

template <typename T>
PQ_Node<T>::PQ_Node(T data, int p)
{
	this->data = data;
	this->p = p;
	next = nullptr;
}

template<typename T>
void PQ_Node<T>::set_data(T data)
{
	this->data = data;
	
}

template<typename T>
void PQ_Node<T>::set_priority(int p)
{
	this->p = p;
}

template<typename T>
void PQ_Node<T>::set_next(PQ_Node<T>* next)
{
	this->next = next;
}

template<typename T>
T PQ_Node<T>::get_data()
{
	return this->data;
}

template<typename T>
int PQ_Node<T>::get_priority()
{
	return this->p;
}

template<typename T>
PQ_Node<T>* PQ_Node<T>::get_next()
{
	return this->next;
}


template<typename T>
Priority_Queue<T>::Priority_Queue(PQ_Node<T>* head)
{
	
	this->head = head;
	

}

template<typename T>
void Priority_Queue<T>::peek(T item)
{
	return this->head->data;
}

template<typename T>
void Priority_Queue<T>::pop(T item)
{




}
