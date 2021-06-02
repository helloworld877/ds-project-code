#include "station.h"
#include <iostream>
#include<istream>
#include<fstream>
#include<string>
using namespace std;

station::station()
{
	this->get_input( no_events, formulation_day);
}

void station::get_input(int& no_events,  int &eventDay)
{
	
	no_events = 0;
	

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
			temp->set_velocity(V_Erovers);
			emergency_missions.enqueue(*temp);

		}
		if (roverType == 'P')
		{
			mission* temp = new mission(roverType, eventDay, ID, targetLoc, missionDur, significance);
			temp->set_velocity(V_Provers);
			polar_missions.enqueue(*temp);
		}





	}

	
	
}


void station::execute()
{
	current_day++;
	get_input( no_events, formulation_day);
	mission tempM;
	rover tempR;
	
	mission checkE; //checks if the formulation day of emergency mission = current day
	checkE = emergency_missions.peek();
	while (checkE.get_formulation_day() == current_day)
	{
		emergency_missions.dequeue(tempM);
		EMwaiting_list.enqueue(tempM);
		checkE = emergency_missions.peek();
	}
	mission checkP; //checks if the formulation day of polar mission = current day
	checkP = polar_missions.peek();
	while (checkP.get_formulation_day() == current_day)
	{
		polar_missions.dequeue(tempM);
		PMwaiting_list.enqueue(tempM);
		checkP = polar_missions.peek();
	}
			
	while(!emergency_rovers.isEmpty())
	{
		emergency_rovers.dequeue(tempR);
		ERwaiting_list.enqueue(tempR);
	}
	while (!polar_rovers.isEmpty())
	{
		polar_rovers.dequeue(tempR);
		PRwaiting_list.enqueue(tempR);
	}
		

	while ((!EMwaiting_list.isEmpty()) && !ERwaiting_list.isEmpty())
	{
		EMwaiting_list.dequeue(tempM);
		EMInExecution_list.insert(tempM);
		eventDay = tempM.get_formulation_day() + tempM.get_waiting_days();
		ERwaiting_list.dequeue(tempR);
		ERInExecution_list.insert(tempR);
	}
	while ((!PMwaiting_list.isEmpty()) && !PRwaiting_list.isEmpty())
	{
		PMwaiting_list.dequeue(tempM);
		PMInExecution_list.insert(tempM);
		tempM.set_eventDay( tempM.get_formulation_day() + tempM.get_waiting_days());
		PRwaiting_list.dequeue(tempR);
		PRInExecution_list.insert(tempR);
	}
	Queue<mission> EDone = ended_E_missions(EMInExecution_list, ERInExecution_list);
	while (!EDone.isEmpty())
	{
		EDone.dequeue(tempM);
		//TO DO: the pointer pointing at the rover
		DoneMissions_list.enqueue(tempM);
	}
	Queue<mission>PDone = ended_P_missions(PMInExecution_list,PRInExecution_list);
	while (!PDone.isEmpty())
	{
		PDone.dequeue(tempM);
		//TO DO: the pointer pointing at the rover
		DoneMissions_list.enqueue(tempM);
	}
	/*TO DO:if(checkup)
        {
            move to checkup
        }
        else 
        {
        move to available
        }
    */


	this->resume = true;

	if (this->current_day == 100)
	{
		this->resume = false;
	}
	
}
/*void station::set_resume(bool r)
{
	resume = r;
}

*/
bool station::get_resume()
{
	return this->resume;
}

Queue<mission> station::ended_E_missions(LinkedList<mission>& EMInExecution_list, LinkedList<rover>& ERInExecution)
{
	Queue<mission> Done;
	Queue<mission> tempM;
	mission temp;
	rover* R;
	while (!EMInExecution_list.isEmpty())
	{
		EMInExecution_list.dequeue(temp);
		if (current_day == temp.get_ending_day())
		{
			R=temp.get_mission_rover();
			Done.enqueue(temp);
			if (R->get_type() == 'E')
			{
				//TO DO: Get the rover responsible for the mission and send it to emergency rover list
			}
		}
		else
		{
			tempM.enqueue(temp);
		}
	}
	while (!tempM.isEmpty())
	{
		tempM.dequeue(temp);
		EMInExecution_list.insert(temp);
	}
	return Done;
}

Queue<mission> station::ended_P_missions(LinkedList<mission>& PMInExecution_list, LinkedList<rover>& PRInExecution)
{
	Queue<mission> Done;
	Queue<mission> tempM;
	Node<mission> *temp;
	temp = PMInExecution_list.get_head();
	while (!PMInExecution_list.isEmpty())
	{
		if (current_day == temp->getItem().get_ending_day())
		{
			Done.enqueue(temp->getItem());

		}
		else
		{
			tempM.enqueue(temp);
		}
	}
	while (!tempM.isEmpty())
	{
		tempM.dequeue(temp);
		PMInExecution_list.enqueue(temp);
	}
	return Done;
}

/*Queue<rover> station::ended_E_rover(Queue<mission>& ERInExecution_list)
{
	Queue<rover> Done;
	Queue<rover> tempR;
	rover temp;
	while (!ERInExecution_list.isEmpty())
	{
		ERInExecution_list.dequeue(temp);
		if ()
		{
			Done.enqueue(temp);
		}
		else
		{
			tempR.enqueue(temp);
		}
	}
	while (!tempR.isEmpty())
	{
		tempR.dequeue(temp);
		PRInExecution_list.enqueue(temp);
	}
	return Done;
}

Queue<rover> station::ended_P_rover(Queue<mission>& PRInExecution_list)
{
	return Queue<rover>();
}
*/


