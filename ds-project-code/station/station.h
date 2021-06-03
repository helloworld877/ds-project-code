#pragma once
#include"../missions/mission.h"
#include"../data structures/LinkedList.h"
#include"../data structures/Priority_Queue.h"
#include"../data structures/Queue.h"
#include"../missions/mission.h"
#include"../rovers/rover.h"
class station
{
private:
	int current_day=0;

	int emergency_rover_count;
	int polar_rover_count;

	Queue<rover*> emergency_rovers;
	Queue<rover*> polar_rovers;

	Queue<mission*> emergency_missions;
	Queue<mission*> polar_missions;

	//missions waiting list
	Queue<mission*> EMwaiting_list;
	Queue<mission*> PMwaiting_list;
	
	//missions in execution list
	LinkedList<mission*> EMInExecution_list;
	LinkedList<mission*> PMInExecution_list;

	//rovers in execution list
	LinkedList<rover*> ERInExecution_list;
	LinkedList<rover*> PRInExecution_list;

	//done misssions list
	Queue<mission*> E_DoneMissions_list;
	Queue<mission*> P_DoneMissions_list;

	//rover checkup list
	Queue<rover*> ERIncheckup_list;
	Queue<rover*> PRIncheckup_list;

	bool resume=true;

	int printing_mode;


public:
	station(int p_mode);
	void get_input();
	void print();
	void execute();
	bool get_resume();
};

