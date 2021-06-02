#pragma once
class rover
{
private:
	int checkup_duration;
	int speed;
	bool available;
	int missions_before_checkup;
	int missions_done=0;
	char Type;
public:
	rover(int speed, int missions_before_checkup, int checkup_duration);
	rover();

	
	char get_type();
	
	int get_speed();
	void set_speed(int speed);
	
	bool get_availability();
	void set_availability(bool available);
	
	int get_missions_before_checkup();

	bool check_checkup();
	void execute();


	
};

