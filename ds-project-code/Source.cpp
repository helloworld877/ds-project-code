#include<iostream>
using namespace std;
#include"data structures/Priority_Queue.h"
#include"data structures/LinkedList.h"
#include"data structures/Queue.h"
#include"../ds-project-code/station/station.h"
#include"../ds-project-code/UI.h"
int main()
{
	int printing_mode;
	UI user;
	printing_mode = user.Input();
	station S(printing_mode);
	while (S.get_resume())
	{
		S.execute();

		user.Output(S);
		if (printing_mode == 1)

			user.interactive_mode(S);
		else if (printing_mode == 2)
			user.stepByStep_mode(S);
		else if (printing_mode == 3)
		{

		}
		else
			user.wrong_input();
		
	}
	if (printing_mode == 3)
	user.silent_mode();
	
}
