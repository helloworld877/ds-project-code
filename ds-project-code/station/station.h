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

	Queue<rover> emergency_rovers;
	Queue<rover> polar_rovers;

	Queue<mission> emergency_missions;
	Queue<mission> polar_missions;

	Queue<mission> EMwaiting_list;
	Queue<mission> PMwaiting_list;

	Queue<rover> ERwaiting_list;
	Queue<rover> PRwaiting_list;

	LinkedList<mission> EMInExecution_list;
	LinkedList<mission> PMInExecution_list;

	LinkedList<rover> ERInExecution_list;
	LinkedList<rover> PRInExecution_list;

	Queue<mission> DoneMissions_list;
	bool resume;

	int no_Provers, no_Erovers, V_Provers, V_Erovers;
	int no_precheckMisions1, no_precheckMisions2, checkupDuration1, checkupDuration2;
	int no_events;
	char formulation, roverType;
	int formulation_day, ID, targetLoc, missionDur, significance,eventDay;


public:
	station();
	void get_input(int& no_events,  int& eventDay);
	void print();
	void execute();
	bool get_resume();
	Queue<mission> ended_E_missions(LinkedList<mission>& EMInExecution_list, LinkedList<rover>& ERInExecution);
	Queue<mission> ended_P_missions(LinkedList<mission>& PMInExecution_list, LinkedList<rover>& PRInExecution);
	/*Queue<rover> ended_E_rover(Queue<mission>& ERInExecution_list, Queue<rover>& ERInExecution);
	Queue<rover> ended_P_rover(Queue<mission>& PRInExecution_list,Queue<rover>& PRInExecution);
	*/
	//void set_resume(bool r);
};

