#include "rover.h"
	

rover::rover(int speed, int missions_before_checkup, int checkup_duration)
{
	this->speed = speed;
	this->missions_before_checkup = missions_before_checkup;
	this->available = true;
	this->checkup_duration = checkup_duration;
}
rover::rover()
{

}

int rover::get_speed()
{
	return this->speed;
}

void rover::set_speed(int speed)
{
	this->speed = speed;
}
bool rover::get_availability()
{
	return this->available;
}

void rover::set_availability(bool available)
{
	this->available = available;
}

int rover::get_missions_before_checkup()
{
	return this->missions_before_checkup;
}

bool rover::check_checkup()
{
	if (this->missions_done == missions_before_checkup)
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}

void rover::execute()
{
	this->missions_done++;
}

