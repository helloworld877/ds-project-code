#include<iostream>
using namespace std;
#include"data structures/Priority_Queue.h"
#include"data structures/LinkedList.h"
#include"data structures/Queue.h"
#include"../ds-project-code/station/station.h"
int main()
{
	int printing_mode;
	cout << "enter prefferd output mode" << endl;
	cin >> printing_mode;
	station S(printing_mode);
	

	while (S.get_resume())
	{
		S.execute();
	}
	


}