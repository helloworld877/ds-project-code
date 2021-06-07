#pragma once
class rover
{
private:
	int checkup_duration;
	int speed;
	bool available;
	int missions_before_checkup;
	int missions_done=0;
	int days_in_checkup = 0;
	int id;
	char type;
public:
	rover(int speed, int missions_before_checkup, int checkup_duration,int id);
	rover();
	
	
	int get_speed();
	void set_speed(int speed);
	
	bool get_availability();
	void set_availability(bool available);
	
	int get_missions_before_checkup();
	void set_missions_done(int x);

	bool check_checkup();
	void increment_missions();
	int get_missions_done();


	void set_days_incheckup(int& checkup);
	int get_days_incheckup();

	int get_id();

	char get_type();
	void set_type(char t);


	
};

