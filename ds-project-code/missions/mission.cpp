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

void mission::set_ending_day(int& end)
{
	if(mission_rover->get_type()=='E')
	  end = Calculate_E_ending_day();
	if (mission_rover->get_type() == 'P')
		end = Calculate_P_ending_day();
	ending_day = end;
}

void mission::set_mission_rover(rover* mission_rover)
{
	this->mission_rover = mission_rover;
}

void mission::set_in_execution(bool exec)
{
	this->in_execution = exec;
}

void mission::set_formulation_day(int formulation)
{
	formulation_day = formulation;
}

void mission::set_eventDay(int eDay)
{
	eventDay = eDay;
}

void mission::set_velocity(int v)
{
	if (this->type == 'E')
	{
		this->V_Erovers = v;
	}
	else
	{
		this->V_Provers = v;
	}
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
	return formulation_day;
}

int mission::get_eventDay()
{
	return eventDay;
}

int mission::Calculate_E_ending_day()
{
	int end_Day=eventDay+(2*target_location/(V_Erovers*25))+mission_duration;

	
	return end_Day;
}

int mission::Calculate_P_ending_day()
{
	int end_Day = eventDay + (2 * target_location / (V_Provers * 25 ))+mission_duration;


	return end_Day;
}

void mission::execute()
{
	//this function is used to put the respective missions in the in execution list 

}
