#include "station.h"
#include <iostream>
#include<istream>
#include<fstream>
#include<string>
using namespace std;

station::station()
{
	this->get_input();
}

void station::get_input()
{
	int no_Provers, no_Erovers, V_Provers, V_Erovers;
	int no_precheckMisions1, no_precheckMisions2, checkupDuration1, checkupDuration2;
	int no_events = 0;
	char formulation, roverType;
	int eventDay, ID, targetLoc, missionDur, significance;

	ifstream inputFile("input.txt", ios::in);

	if (inputFile.is_open())
	{
		inputFile >> no_Provers;
		inputFile >> no_Erovers;
		inputFile >> V_Provers;
		inputFile >> V_Erovers;
		inputFile >> no_precheckMisions1;
		inputFile >> no_precheckMisions2;
		inputFile >> checkupDuration1;
		inputFile >> no_events;

		//adding the dat to the station
		this->polar_rover_count = no_Provers;
		this->emergency_rover_count = no_Erovers;

		for (int i = 0; i < polar_rover_count; i++)
		{
			rover* temp = new rover(V_Provers,no_precheckMisions1,checkupDuration1);
			this->polar_rovers.enqueue(*temp);
		}
		for (int i = 0; i < emergency_rover_count; i++)
		{
			rover* temp = new rover(V_Erovers, no_precheckMisions2, checkupDuration1);
			this->emergency_rovers.enqueue(*temp);
		}



		cout << "eshta" << endl;
	}
	else
	{
		cout << "ERROR";
	}

	cout << no_Provers << " ";
	cout << no_Erovers;
	cout << endl;
	cout << V_Provers << " ";
	cout << V_Erovers;
	cout << endl;
	cout << no_precheckMisions1 << " ";
	cout << no_precheckMisions2 << " ";
	cout << checkupDuration1 << " ";
	cout << endl;
	cout << no_events << endl;
	
	for (int i = 0; i < no_events; i++)
	{
		inputFile >> formulation;
		inputFile >> roverType;
		inputFile >> eventDay;
		inputFile >> ID;
		inputFile >> targetLoc;
		inputFile >> missionDur;
		inputFile >> significance;



		/*
		cout << "day no." << i + 1 << ":";
		cout << formulation << " ";
		cout << roverType << " ";
		cout << eventDay << " ";
		cout << ID << " ";
		cout << targetLoc << " ";
		cout << missionDur << " ";
		cout << significance << " ";
		cout << endl;

		*/


		if (roverType == 'E')
		{
			mission* temp = new mission(roverType,eventDay,ID,targetLoc,missionDur,significance);
			emergency_missions.enqueue(*temp);
		}
		if (roverType == 'P')
		{
			mission* temp = new mission(roverType, eventDay, ID, targetLoc, missionDur, significance);
			polar_missions.enqueue(*temp);
		}





	}

	


}
