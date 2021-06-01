#pragma once
#include"../rovers/rover.h"
class mission
{
private:
	char type;
	int formulation_day;
	int waiting_days=0;
	int execution_days;
	int id;
	int target_location;
	int mission_duration;
	int signifigance;
	int ending_day;
	bool in_execution;
	rover* mission_rover;

public:

	mission(char type, int formulation_day, int id, int target_location, int mission_duration, int signifigance);
	mission();

	//setters

	void set_waiting_days(int wait);
	void set_execution_days (int exec);
	void set_ending_day(int end);
	void set_mission_rover(rover* mission_rover);
	void set_in_execution(bool exec);

	//getters

	int get_waiting_days();
	int get_execution_days();
	int get_ending_day();
	bool get_in_execution();
	rover* get_mission_rover();

	//executing the mission

	void execute();
};

