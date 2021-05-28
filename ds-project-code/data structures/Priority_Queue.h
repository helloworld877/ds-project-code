#pragma once
#include<iostream>
template <typename T>
class PQ_Node
{
private:
	int p;
	T data;
	PQ_Node<T>* next;
public:
	PQ_Node(T data, int p);

	void set_data(T data);
	
	void set_priority(int p);
	
	void set_next(PQ_Node<T>* next);
	





	T get_data();
	
	int get_priority();
	
	
	PQ_Node<T>* get_next();




};

template<typename T>
class Priority_Queue
{
private:
	PQ_Node<T>* head;
public:
	Priority_Queue(PQ_Node<T>* head);
	
	void peek(T item);
	
	void pop(T item);
	

	
};

