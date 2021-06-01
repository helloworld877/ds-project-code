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





public:
	station();
	void get_input();
	void print();
	void execute();

};

