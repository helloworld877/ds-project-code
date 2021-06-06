#include "mission.h"

mission::mission(char type, int formulation_day, int id, int target_location, int mission_duration, int signifigance)
{
	this->type = type;
	this->formulation_day = formulation_day;
	this->id = id;
	this->target_location = target_location;
	this->mission_duration = mission_duration;
	this->signifigance = signifigance;
}
mission::mission()
{

}
void mission::set_waiting_days(int wait)
{
	this->waiting_days = wait;
}

void mission::set_execution_days(int exec)
{
	this->execution_days = exec;
}

void mission::set_ending_day(int end)
{
	this->ending_day = end;
}

void mission::set_mission_rover(rover* mission_rover)
{
	this->mission_rover = mission_rover;
}

void mission::set_in_execution(bool exec)
{
	this->in_execution = exec;
}

void mission::set_ending_day()
{
	if (this->mission_rover == nullptr)
	{
		return;
	}
	this->ending_day= this->formulation_day + (2 * target_location / (this->mission_rover->get_speed() * 25)) + mission_duration;
}

int mission::get_waiting_days()
{
	return this->waiting_days;
}

int mission::get_execution_days()
{
	return this->execution_days;
}

int mission::get_ending_day()
{
	return this->ending_day;
}

bool mission::get_in_execution()
{
	return this->in_execution;
}

rover* mission::get_mission_rover()
{
	return this->mission_rover;
}

int mission::get_formulation_day()
{

	return this->formulation_day;
}
//extra getters for output file
int mission::get_ID()
{
	return this->id;
}

int mission::get_ED()
{
	return this->get_ending_day() - this->get_formulation_day();
}

void mission::execute()
{
	//this function is used to put the respective missions in the in execution list 

}

void mission::increment_waiting()
{
	this->waiting_days++;
}

void mission::set_priority(int p)
{
	this->priority = p;
}

int mission::get_priority()
{
	return this->priority;
}
