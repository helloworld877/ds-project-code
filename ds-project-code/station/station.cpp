#include "station.h"
#include <iostream>
#include<istream>
#include<fstream>
#include<string>
using namespace std;

station::station(int p_mode)
{
	this->printing_mode = p_mode;
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
			this->polar_rovers.enqueue(temp);
		}
		for (int i = 0; i < emergency_rover_count; i++)
		{
			rover* temp = new rover(V_Erovers, no_precheckMisions2, checkupDuration1);
			this->emergency_rovers.enqueue(temp);
		}



		cout << "eshta" << endl;
	}
	else
	{
		cout << "ERROR";
	}

	/*cout << no_Provers << " ";
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
	*/
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
			emergency_missions.enqueue(temp);
		}
		if (roverType == 'P')
		{
			mission* temp = new mission(roverType, eventDay, ID, targetLoc, missionDur, significance);
			polar_missions.enqueue(temp);
		}





	}

	
	
}


void station::execute()
{
	current_day++;
	//check if there is a rover returning from maintanance





	//check if there is a rover coming back from a mission today


	Node<mission*>*  EM_checker= EMInExecution_list.get_head();

	while (EM_checker)
	{
		if (EM_checker->getItem()->get_ending_day() == current_day)
		{
			Node<mission*>* temp_checker=EM_checker;
			EM_checker = EM_checker->getNext();
			mission* temp;
			EMInExecution_list.remove(temp_checker, temp);
			E_DoneMissions_list.enqueue(temp);


			//implement transition of rover////////////////////////////////////////////////////////

			rover* temp_rover;
			temp_rover = temp->get_mission_rover();


			
			continue;
		}
		else 
		{
			EM_checker = EM_checker->getNext();
		}
		

	}

	///////////////////////////////////////////////////////////////////////////////



	Node<mission*>* PM_checker = PMInExecution_list.get_head();

	while (PM_checker)
	{
		if (PM_checker->getItem()->get_ending_day() == current_day)
		{
			Node<mission*>* temp_checker = PM_checker;
			PM_checker = PM_checker->getNext();
			mission* temp;
			PMInExecution_list.remove(temp_checker, temp);
			P_DoneMissions_list.enqueue(temp);
			//implement transition of rover////////////////////////////////////////////////////////



			rover* temp_rover;
			temp_rover = temp->get_mission_rover();




			continue;
		}
		else
		{
			PM_checker = PM_checker->getNext();
		}


	}






	//check if there is a mission to be added today
	while (emergency_missions.peek() && emergency_missions.peek()->get_formulation_day() == current_day)
	{
		mission* temp=nullptr; 
		emergency_missions.dequeue(temp);
		EMwaiting_list.enqueue(temp);
		
	}
	while (polar_missions.peek() && polar_missions.peek()->get_formulation_day() == current_day)
	{
		mission* temp = nullptr;
		polar_missions.dequeue(temp);
		PMwaiting_list.enqueue(temp);
	}

	
	// check if there is a rover available for the currently waiting missions

	while (EMwaiting_list.peek() && emergency_rovers.peek())
	{
		mission* temp_mission = nullptr;
		EMwaiting_list.dequeue(temp_mission);

		rover* temp_rover = nullptr;
		emergency_rovers.dequeue(temp_rover);

		temp_mission->set_mission_rover(temp_rover);
		temp_mission->set_ending_day();

		temp_rover->increment_missions();

		EMInExecution_list.insert(temp_mission);
		ERInExecution_list.insert(temp_rover);




	}




	while (PMwaiting_list.peek() && polar_rovers.peek())
	{
		mission* temp_mission = nullptr;
		PMwaiting_list.dequeue(temp_mission);

		rover* temp_rover = nullptr;
		polar_rovers.dequeue(temp_rover);

		temp_mission->set_mission_rover(temp_rover);
		temp_mission->set_ending_day();

		temp_rover->increment_missions();

		PMInExecution_list.insert(temp_mission);
		PRInExecution_list.insert(temp_rover);
	}


	//incrementing waiting days for emergency missions

	if (EMwaiting_list.peek())
	{
		Queue<mission*> temp;
		mission* temp_mission;
		
		while (EMwaiting_list.dequeue(temp_mission))
		{
			temp_mission->increment_waiting();
			temp.enqueue(temp_mission);
			
		}
		
		while (temp.dequeue(temp_mission))
		{
			EMwaiting_list.enqueue(temp_mission);
		}


	}


	//incrementing waiting days for polar missions
	
	if (PMwaiting_list.peek())
	{
		Queue<mission*> temp;
		mission* temp_mission;

		while (PMwaiting_list.dequeue(temp_mission))
		{
			temp_mission->increment_waiting();
			temp.enqueue(temp_mission);

		}

		while (temp.dequeue(temp_mission))
		{
			PMwaiting_list.enqueue(temp_mission);
		}


	}



	this->resume = true;

	if (this->current_day == 100)
	{
		this->resume = false;
	}
}

bool station::get_resume()
{
	return this->resume;
}


