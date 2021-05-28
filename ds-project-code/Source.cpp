#include<iostream>
using namespace std;
#include"data structures/Priority_Queue.h"
#include"data structures/LinkedList.h"
#include"data structures/Queue.h"

int main()
{
	int a0 = 1;
	PQ_Node<int> x (a0, 5);
	Priority_Queue<int> y(&x);
	int a2=2;
	int a3=3;
	int a4=4;
	y.push(a2, 2);
	y.push(a3, 3);
	y.push(a4, 0);
	int temp;

	
	while (y.pop(temp))
	{
		
		cout << temp << endl;

	}
	
	

	return 0;
}