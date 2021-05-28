#pragma once
#include<iostream>
template <typename T>
class PQ_Node
{
public:
	int p;
	T data;
	PQ_Node<T>* next;
public:
	PQ_Node(T& data, int p)
	{
		this->data = data;
		this->p = p;
		this->next = nullptr;
	}

	void set_data(T& data)
	{
		this->data = data;

	}
	
	void set_priority(int p)
	{
		this->p = p;
	}
	
	void set_next(PQ_Node<T>* next)
	{
		this->next = next;
	}

	





	T* get_data()
	{
		return this->data;
	}
	
	int get_priority()
	{
		return this->p;
	}

	
	
	PQ_Node<T>* get_next()
	{
		return this->next;
	}




};

template<typename T>
class Priority_Queue
{
private:
	PQ_Node<T>* head;
public:
	Priority_Queue(PQ_Node<T>* start)
	{

		this->head = start;


	}
	
	bool peek(T &item)
	{
		if (head == nullptr)
		{
			item = NULL;
			return false;
		}
		item = this->head->data;
		return true;
	}
	
	bool pop(T& item)
	{
		if (head == nullptr)
		{
			return false;
		}
		PQ_Node<T>* temp = this->head;
		head = head->next;
		item=temp->data ;
		
		return true;



	}

	
	void push(T& item, int p)
	{
		PQ_Node<T>* start = this->head;

		PQ_Node<T>* temp = new PQ_Node<T>(item, p);


		if (this->head == nullptr)
		{
			this->head = temp;
			return;
		}


		if (this->head->p < p)
		{
			temp->next = this->head;
			this->head = temp;
			return;
		}
		else
		{
			while (start->next != nullptr && start->next->p > p)
			{
				start = start->next;
			}

			temp->next = start->next;
			start->next = temp;
		}





	}


	bool is_empty()
	{
		if (this->head == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}

	}
	 
	
};

