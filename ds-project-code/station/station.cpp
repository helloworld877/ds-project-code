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
			rover* temp = new rover(V_Provers,no_precheckMisions1,checkupDuration1,i);
			this->polar_rovers.enqueue(temp);
		}
		for (int i = 0; i < emergency_rover_count; i++)
		{
			rover* temp = new rover(V_Erovers, no_precheckMisions2, checkupDuration1,i);
			this->emergency_rovers.enqueue(temp);
		}
	}
	else
	{
		cout << "ERROR";
	}

	for (int i = 0; i < no_events; i++)
	{
		inputFile >> formulation;
		inputFile >> roverType;
		inputFile >> eventDay;
		inputFile >> ID;
		inputFile >> targetLoc;
		inputFile >> missionDur;
		inputFile >> significance;


		if (roverType == 'E')
		{
			mission* temp = new mission(roverType,eventDay,ID,targetLoc,missionDur,significance);
			emergency_missions.enqueue(temp);
			emergency_mission_count++;
		}
		if (roverType == 'P')
		{
			mission* temp = new mission(roverType, eventDay, ID, targetLoc, missionDur, significance);
			polar_missions.enqueue(temp);
			polar_mission_count++;
		}





	}

	this->checkup_duration = checkupDuration1;
	
}


void station::execute()
{
	current_day++;
	//check if there is a rover returning from maintanance


	rover* ER_checker;
	Queue<rover*> tempeven;
	while (ERIncheckup_list.dequeue(ER_checker))
	{
		if (ER_checker->get_days_incheckup() == this->checkup_duration)
		{
			emergency_rovers.enqueue(ER_checker);
		}
		else
		{
			int x = ER_checker->get_days_incheckup() + 1;
			ER_checker->set_days_incheckup(x);
			tempeven.enqueue(ER_checker);
		}
	}
	while (tempeven.dequeue(ER_checker))
	{
		ERIncheckup_list.enqueue(ER_checker);
	}


	rover* PR_checker;
	Queue<rover*> tempodd;
	while (PRIncheckup_list.dequeue(PR_checker))
	{
		if (PR_checker->get_days_incheckup() == this->checkup_duration)
		{
			polar_rovers.enqueue(PR_checker);
		}
		else
		{
			int x = PR_checker->get_days_incheckup() + 1;
			PR_checker->set_days_incheckup(x);
			tempodd.enqueue(PR_checker);
		}
	}
	while (tempodd.dequeue(PR_checker))
	{
		PRIncheckup_list.enqueue(PR_checker);
	}



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
			DoneMissions_list.enqueue(temp);


			//implement transition of rover////////////////////////////////////////////////////////

			rover* temp_rover;
			temp_rover = temp->get_mission_rover();
			ERInExecution_list.remove_value(temp_rover);
			if (temp_rover->get_missions_before_checkup() == temp_rover->get_missions_done())
			{
				temp_rover->set_missions_done(0);
				ERIncheckup_list.enqueue(temp_rover);

			}
			else
			{
				emergency_rovers.enqueue(temp_rover);
			}

			temp->set_mission_rover(nullptr);

			
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
			DoneMissions_list.enqueue(temp);
			//implement transition of rover////////////////////////////////////////////////////////


			rover* temp_rover;
			temp_rover = temp->get_mission_rover();
			PRInExecution_list.remove_value(temp_rover);

			if (temp_rover->get_missions_before_checkup() == temp_rover->get_missions_done())
			{

				temp_rover->set_missions_done(0);
				PRIncheckup_list.enqueue(temp_rover);

			}
			else
			{
				polar_rovers.enqueue(temp_rover);
			}



			temp->set_mission_rover(nullptr);


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




	//interactive mode here





	this->resume = true;
	if (emergency_missions.peek() == nullptr && polar_missions.peek() == nullptr)
	{
		if (EMInExecution_list.get_head() == nullptr && PMInExecution_list.get_head() == nullptr)
		{
			if (EMwaiting_list.peek() == nullptr && PMwaiting_list.peek() == nullptr)
			{
				this->resume = false;
				//silent mode here

			}
		}
	}








}
//extra getters for output file
Queue<mission*> station::get_done_missions()
{
	return this->DoneMissions_list;
}

Queue<mission*> station::get_Ewaiting_list()
{
	return this->EMwaiting_list;
}

Queue<mission*> station::get_Pwaiting_list()
{
	return this->PMwaiting_list;
}

Node<mission*>* station::get_EMInExecution_list()
{
	return this->EMInExecution_list.get_head();
}

Node<mission*>* station::get_PMInExecution_list()
{
	return this->PMInExecution_list.get_head();
}

Queue<rover*> station::get_emergency_rovers()
{
	return this->emergency_rovers;
}

Queue<rover*> station::get_polar_rovers()
{
	return this->polar_rovers;
}

Queue<rover*> station::get_ERIncheckup_list()
{
	return this->ERIncheckup_list;
}

Queue<rover*> station::get_PRIncheckup_list()
{
	return this->PRIncheckup_list;
}

Queue<mission*> station::get_E_DoneMissions_list()
{
	return this->E_DoneMissions_list;
}

Queue<mission*> station::get_P_DoneMissions_list()
{
	return this->P_DoneMissions_list;
}

int station::get_total_Emissions()
{
	return this->emergency_mission_count;
}
int station::get_total_Pmissions()
{
	return this->polar_mission_count;
}
int station::get_total_missions()
{
	return this->get_total_Emissions() + this->get_total_Pmissions();
}
int station::get_total_Erovers()
{
	return this->emergency_rover_count;
}
int station::get_total_Provers()
{
	return this->polar_rover_count;
}
int station::get_total_rovers()
{
	return this->get_total_Erovers() + this->get_total_Provers();
}

int station::get_current_day()
{
	return this->current_day;
}
int station::get_waiting_missions(int& Ecount, int& Pcount)
{
	Queue<mission*> temp_polar;
	Queue<mission*> temp_emergency;
	int count = 0;
	mission* M;
	while (!EMwaiting_list.IsEmpty())
	{
		EMwaiting_list.dequeue(M);
		temp_emergency.enqueue(M);
		Ecount++;
	}
	while (!PMwaiting_list.IsEmpty())
	{
		PMwaiting_list.dequeue(M);
		temp_polar.enqueue(M);
		Pcount++;
	}
	count = Ecount + Pcount;

	while (temp_emergency.dequeue(M))
	{
		EMwaiting_list.enqueue(M);
	}


	while (temp_polar.dequeue(M))
	{
		PMwaiting_list.enqueue(M);
	}


	return count;
}
bool station::get_resume()
{
	return this->resume;
}


