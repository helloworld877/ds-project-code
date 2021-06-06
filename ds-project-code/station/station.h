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

	int emergency_mission_count;
	int polar_mission_count;

	int waiting_missions;
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
	Queue<mission*> DoneMissions_list;


	//rover checkup list
	Queue<rover*> ERIncheckup_list;
	Queue<rover*> PRIncheckup_list;


	bool resume=true;

	int printing_mode;

	int checkup_duration;

public:
	station(int p_mode);
	void get_input();
	void print();
	void execute();
	bool get_resume();
	Queue<mission*> get_done_missions();
	int get_total_rovers();
	int get_total_Erovers();
	int get_total_Provers();
	int get_total_missions();
	int get_total_Emissions();
	int get_total_Pmissions();
	int get_current_day();
	int get_waiting_missions(int& Ecount, int& Pcount);
	Queue<mission*> get_Ewaiting_list();
	Queue<mission*> get_Pwaiting_list();

	Node<mission*>* get_EMInExecution_list();
	Node<mission*>* get_PMInExecution_list();

	
	Queue<rover*> get_emergency_rovers();
	Queue<rover*> get_polar_rovers();

	Queue<rover*> get_ERIncheckup_list();
	Queue<rover*> get_PRIncheckup_list();

	Queue<mission*> get_E_DoneMissions_list();
	Queue<mission*> get_P_DoneMissions_list();



};

