#pragma once
#include"../missions/mission.h"
#include"../rovers/rover.h"
#include"../station/station.h"
#include <iostream>;
using namespace std;
#include <fstream>
class UI
{
private:

	int Num_missions_total;
	int Num_missions_emergency;
	int Num_missions_polar;
	int Num_rovers_total;
	int Num_rovers_emergency;
	int Num_rovers_polar;
	float sum_wait = 0;
	float sum_ED = 0;
	ofstream outputFile;
	mission* M;
	int waiting_missions;
	int Ewaiting_missions;
	int Pwaiting_missions;
public:
	UI();
	int Input();
	void Output(station S);
	void interactive_mode(station S);
	void stepByStep_mode(station S);
	void silent_mode();
	void wrong_input();
};