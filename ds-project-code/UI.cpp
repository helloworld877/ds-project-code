#include "UI.h"
UI::UI()
{

}
int UI::Input()
{
	int printing_mode;
	cout << "1. Interactive mode" << endl;
	cout << "2. Step-By-Step mode" << endl;
	cout << "3. Silenet mode" << endl;
	cout << "Enter preferred output mode: ";
	cin >> printing_mode;
	cin.ignore();
	return printing_mode;
}
void UI::Output(station S)
{
	// open file
	outputFile.open("Output.txt", ios::out);

	outputFile << "CD" << "    ";
	outputFile << "ID" << "    ";
	outputFile << "FD" << "    ";
	outputFile << "WD" << "    ";
	outputFile << "ED" << "    ";
	outputFile << endl;
	Queue<mission*> temp;
	temp = S.get_done_missions();
	sum_ED = 0;
	sum_wait = 0;
	while (temp.dequeue(M))
	{
		
		outputFile << M->get_ending_day() << "    ";
		outputFile << M->get_ID() << "    ";
		outputFile << M->get_formulation_day() << "    ";
		outputFile << M->get_waiting_days() << "    ";
		outputFile << M->get_ED() << "    ";
		outputFile << endl;
		sum_wait += M->get_waiting_days();
		sum_ED += M->get_ED();
	}

	outputFile << "………………………………………………………………………………………………" << endl;
	outputFile << "………………………………………………………………………………………………" << endl;
	Num_missions_total = S.get_total_missions();
	Num_missions_emergency = S.get_total_Emissions();
	Num_missions_polar = S.get_total_Pmissions();
	Num_rovers_total = S.get_total_rovers();
	Num_rovers_emergency = S.get_total_Erovers();
	Num_rovers_polar = S.get_total_Provers();
	outputFile << "Missions:" << Num_missions_total << " [P:" << Num_missions_polar << ", E:" << Num_missions_emergency << "]" << endl;
	outputFile << "Rovers:" << Num_rovers_total << " [P:" << Num_rovers_polar << ", E:" << Num_rovers_emergency << "]" << endl;
	outputFile << "Avg Wait = " << sum_wait/ Num_missions_total << ", Avg Exec = " << sum_ED/ Num_missions_total << endl;


	//close file
	outputFile.close();
}
void UI::interactive_mode(station S)
{
	waiting_missions = S.get_waiting_missions(Ewaiting_missions, Pwaiting_missions);

	cout << "Current Day: " << S.get_current_day() << endl;
	cout << waiting_missions << " Waiting Missions: " << "[";

	waiting_missions = 0;
	
	Priority_Queue<mission*> temp;
	Queue<mission*> temp2;
	temp = S.get_Ewaiting_list();
	while(temp.dequeue(M))
	{
		
		cout << M->get_ID() << ",";
	}
	cout << "]" << " ";
	cout << "(";
	temp2 = S.get_Pwaiting_list();
	while (temp2.dequeue(M))
	{
		
		cout << M->get_ID() << ",";
	}
	cout << ")" << " ";

	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	/////////////////////////////////////////////////////
	

	Node<mission*>* EM_head = S.get_EMInExecution_list();
	Node<mission*>* PM_head = S.get_PMInExecution_list();

	int in_execution_count = 0;

	while (EM_head)
	{
		in_execution_count++;
		EM_head = EM_head->getNext();
	}

	while (PM_head)
	{
		in_execution_count++;
		PM_head = PM_head->getNext();
	}

	 EM_head = S.get_EMInExecution_list();
	 PM_head = S.get_PMInExecution_list();

	
	cout <<in_execution_count<< " In-Execution Missions/Rovers: ";
	if (EM_head == nullptr)
	{
		cout << "[]"<<" ";
	}
	else
	{
		cout << "[";
		while (EM_head)
		{


			cout << EM_head->getItem()->get_ID() << "/" << EM_head->getItem()->get_mission_rover()->get_id();

			if (EM_head->getNext() == nullptr)
			{
				cout << "]";
			}
			else
			{
				cout << ", ";
			}







			EM_head = EM_head->getNext();
		}
	}

	if (PM_head == nullptr)
	{
		cout << "()" << " ";
	}
	else
	{
		cout << "(";


		while (PM_head)
		{


			cout << PM_head->getItem()->get_ID() << "/" << PM_head->getItem()->get_mission_rover()->get_id();

			if (PM_head->getNext() == nullptr)
			{
				cout << ")";
			}
			else
			{
				cout << ", ";
			}







			PM_head = PM_head->getNext();
		}


	}
	
	cout << endl;
	
	cout << "-------------------------------------------------------" << endl;

	/////////////////////////////////////////////////////////////////////////


	Queue<rover*> available_E_rovers = S.get_emergency_rovers();
	Queue<rover*> available_P_rovers = S.get_polar_rovers();
	Queue<rover*> available_E_rovers2 ;
	Queue<rover*> available_P_rovers2 ;
	int available_rovers_count = 0;
	rover *r;

	while (available_E_rovers.dequeue(r))
	{
		available_E_rovers2.enqueue(r);
		available_rovers_count++;
	}

	while (available_P_rovers.dequeue(r))
	{
		available_P_rovers2.enqueue(r);
		available_rovers_count++;
	}

	
	while (available_E_rovers2.dequeue(r))
	{
		available_E_rovers.enqueue(r);
		
	}

	while (available_P_rovers2.dequeue(r))
	{
		available_P_rovers.enqueue(r);
		
	}


	
	cout << available_rovers_count << "Available Rovers: ";
		if(available_E_rovers.peek()==nullptr)
		{
			cout << "[]" << " ";
		}
		else
		{
			cout << "[";
			while (available_E_rovers.peek())
			{

				available_E_rovers.dequeue(r);

				cout << r->get_id();

				if (available_E_rovers.peek() == nullptr)
				{
					cout << "] ";
				}
				else
				{
					cout << ", ";
				}

				available_E_rovers2.enqueue(r);


			}
		}

		if (available_P_rovers.peek() == nullptr)
		{
			cout << "()" << " ";
		}
		else
		{
			cout << "(";
			while (available_P_rovers.peek())
			{

				available_P_rovers.dequeue(r);

				cout << r->get_id();

				if (available_P_rovers.peek() == nullptr)
				{
					cout << ") ";
				}
				else
				{
					cout << ", ";
				}

				available_P_rovers2.enqueue(r);


			}
		}

		while (available_E_rovers2.dequeue(r))
		{
			available_E_rovers.enqueue(r);

		}

		while (available_P_rovers2.dequeue(r))
		{
			available_P_rovers.enqueue(r);

		}
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
	///////////////////////////////////////////////////////////

		Queue<rover*> in_checkup_E_rovers = S.get_ERIncheckup_list();
		Queue<rover*> in_checkup_P_rovers = S.get_PRIncheckup_list();
	


		Queue<rover*> in_checkup_E_rovers2;
		Queue<rover*> in_checkup_P_rovers2;
		int in_checkup_rovers_count = 0;
		

		while (in_checkup_E_rovers.dequeue(r))
		{
			in_checkup_E_rovers2.enqueue(r);
			in_checkup_rovers_count++;
		}

		while (in_checkup_P_rovers.dequeue(r))
		{
			in_checkup_P_rovers2.enqueue(r);
			in_checkup_rovers_count++;
		}


		while (in_checkup_E_rovers2.dequeue(r))
		{
			in_checkup_E_rovers.enqueue(r);
			
		}

		while (in_checkup_P_rovers2.dequeue(r))
		{
			in_checkup_P_rovers.enqueue(r);
			
		}




		cout << in_checkup_rovers_count << "In Checkup Rovers: ";
		if (in_checkup_E_rovers.peek() == nullptr)
		{
			cout << "[]" << " ";
		}
		else
		{
			cout << "[";
			while (in_checkup_E_rovers.peek())
			{

				in_checkup_E_rovers.dequeue(r);

				cout << r->get_id();

				if (in_checkup_E_rovers.peek() == nullptr)
				{
					cout << "] ";
				}
				else
				{
					cout << ", ";
				}

				in_checkup_E_rovers2.enqueue(r);


			}
		}

		if (in_checkup_P_rovers.peek() == nullptr)
		{
			cout << "()" << " ";
		}
		else
		{
			cout << "(";
			while (in_checkup_P_rovers.peek())
			{

				in_checkup_P_rovers.dequeue(r);

				cout  << r->get_id();

				if (in_checkup_P_rovers.peek() == nullptr)
				{
					cout << ") ";
				}
				else
				{
					cout << ", ";
				}

				in_checkup_P_rovers2.enqueue(r);


			}
		}


		while (in_checkup_E_rovers2.dequeue(r))
		{
			in_checkup_E_rovers.enqueue(r);

		}

		while (in_checkup_P_rovers2.dequeue(r))
		{
			in_checkup_P_rovers.enqueue(r);

		}
		cout << endl;
		cout << "-------------------------------------------------------" << endl;
















	////////////////////////////////////////////////////////////




		
		




		/////////////////////////////////////////////////



		Queue<mission*> E_done_missions = S.get_E_DoneMissions_list();
		Queue<mission*> P_done_missions = S.get_P_DoneMissions_list();


		Queue<mission*> E_done_missions2;
		Queue<mission*> P_done_missions2;

		int done_missions_count = 0;

		mission* m;

		while (E_done_missions.dequeue(m))
		{
			E_done_missions2.enqueue(m);
			done_missions_count++;
		}

		while (P_done_missions.dequeue(m))
		{
			P_done_missions2.enqueue(m);
			done_missions_count++;
		}


		while (E_done_missions2.dequeue(m))
		{
			E_done_missions.enqueue(m);

		}
	
		while (P_done_missions2.dequeue(m))
		{
			P_done_missions.enqueue(m);

		}


		cout << done_missions_count << " Completed Missions: ";

		if (E_done_missions.peek() == nullptr)
		{

			cout << "[] ";
		}
		else
		{
			cout << "[";

			while (E_done_missions.peek())
			{
			
				E_done_missions.dequeue(m);

				
				cout << m->get_ID();
				if (E_done_missions.peek() == nullptr)
				{
					cout << "] ";
				}
				else
				{
					cout << ", ";
				}

				E_done_missions2.enqueue(m);


			}




		}


		if (P_done_missions.peek() == nullptr)
		{

			cout << "() ";
		}
		else
		{
			cout << "(";

			while (P_done_missions.peek())
			{
				P_done_missions.dequeue(m);

				
				cout << m->get_ID();
				if (P_done_missions.peek() == nullptr)
				{
					cout << ") ";
				}
				else
				{
					cout << ", ";
				}

				P_done_missions2.enqueue(m);


			}




		}



		while (E_done_missions2.dequeue(m))
		{
			E_done_missions.enqueue(m);

		}

		while (P_done_missions2.dequeue(m))
		{
			P_done_missions.enqueue(m);

		}
		cout << endl;
		cout << "-------------------------------------------------------" << endl;

		cout << endl;



	waiting_missions = 0;
	Ewaiting_missions = 0;
	Pwaiting_missions=0;

	cout << "Press Enter to Continue"<<endl;
	cin.ignore();


}
void UI::stepByStep_mode(station S)

{
	waiting_missions = S.get_waiting_missions(Ewaiting_missions, Pwaiting_missions);

	cout << "Current Day: " << S.get_current_day() << endl;
	cout << waiting_missions << " Waiting Missions: " << "[";

	waiting_missions = 0;

	Priority_Queue<mission*> temp;
	Queue<mission*> temp2;
	temp = S.get_Ewaiting_list();
	while (temp.dequeue(M))
	{

		cout << M->get_ID() << ",";
	}
	cout << "]" << " ";
	cout << "(";
	temp2 = S.get_Pwaiting_list();
	while (temp2.dequeue(M))
	{

		cout << M->get_ID() << ",";
	}
	cout << ")" << " ";

	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	/////////////////////////////////////////////////////


	Node<mission*>* EM_head = S.get_EMInExecution_list();
	Node<mission*>* PM_head = S.get_PMInExecution_list();

	int in_execution_count = 0;

	while (EM_head)
	{
		in_execution_count++;
		EM_head = EM_head->getNext();
	}

	while (PM_head)
	{
		in_execution_count++;
		PM_head = PM_head->getNext();
	}

	EM_head = S.get_EMInExecution_list();
	PM_head = S.get_PMInExecution_list();


	cout << in_execution_count << " In-Execution Missions/Rovers: ";
	if (EM_head == nullptr)
	{
		cout << "[]" << " ";
	}
	else
	{
		cout << "[";
		while (EM_head)
		{


			cout << EM_head->getItem()->get_ID() << "/" << EM_head->getItem()->get_mission_rover()->get_id();

			if (EM_head->getNext() == nullptr)
			{
				cout << "]";
			}
			else
			{
				cout << ", ";
			}







			EM_head = EM_head->getNext();
		}
	}

	if (PM_head == nullptr)
	{
		cout << "()" << " ";
	}
	else
	{
		cout << "(";


		while (PM_head)
		{


			cout << PM_head->getItem()->get_ID() << "/" << PM_head->getItem()->get_mission_rover()->get_id();

			if (PM_head->getNext() == nullptr)
			{
				cout << ")";
			}
			else
			{
				cout << ", ";
			}







			PM_head = PM_head->getNext();
		}


	}

	cout << endl;

	cout << "-------------------------------------------------------" << endl;

	/////////////////////////////////////////////////////////////////////////


	Queue<rover*> available_E_rovers = S.get_emergency_rovers();
	Queue<rover*> available_P_rovers = S.get_polar_rovers();
	Queue<rover*> available_E_rovers2;
	Queue<rover*> available_P_rovers2;
	int available_rovers_count = 0;
	rover* r;

	while (available_E_rovers.dequeue(r))
	{
		available_E_rovers2.enqueue(r);
		available_rovers_count++;
	}

	while (available_P_rovers.dequeue(r))
	{
		available_P_rovers2.enqueue(r);
		available_rovers_count++;
	}


	while (available_E_rovers2.dequeue(r))
	{
		available_E_rovers.enqueue(r);

	}

	while (available_P_rovers2.dequeue(r))
	{
		available_P_rovers.enqueue(r);

	}



	cout << available_rovers_count << "Available Rovers: ";
	if (available_E_rovers.peek() == nullptr)
	{
		cout << "[]" << " ";
	}
	else
	{
		cout << "[";
		while (available_E_rovers.peek())
		{

			available_E_rovers.dequeue(r);

			cout << r->get_id();

			if (available_E_rovers.peek() == nullptr)
			{
				cout << "] ";
			}
			else
			{
				cout << ", ";
			}

			available_E_rovers2.enqueue(r);


		}
	}

	if (available_P_rovers.peek() == nullptr)
	{
		cout << "()" << " ";
	}
	else
	{
		cout << "(";
		while (available_P_rovers.peek())
		{

			available_P_rovers.dequeue(r);

			cout << r->get_id();

			if (available_P_rovers.peek() == nullptr)
			{
				cout << ") ";
			}
			else
			{
				cout << ", ";
			}

			available_P_rovers2.enqueue(r);


		}
	}

	while (available_E_rovers2.dequeue(r))
	{
		available_E_rovers.enqueue(r);

	}

	while (available_P_rovers2.dequeue(r))
	{
		available_P_rovers.enqueue(r);

	}
	cout << endl;
	cout << "-------------------------------------------------------" << endl;
	///////////////////////////////////////////////////////////

	Queue<rover*> in_checkup_E_rovers = S.get_ERIncheckup_list();
	Queue<rover*> in_checkup_P_rovers = S.get_PRIncheckup_list();



	Queue<rover*> in_checkup_E_rovers2;
	Queue<rover*> in_checkup_P_rovers2;
	int in_checkup_rovers_count = 0;


	while (in_checkup_E_rovers.dequeue(r))
	{
		in_checkup_E_rovers2.enqueue(r);
		in_checkup_rovers_count++;
	}

	while (in_checkup_P_rovers.dequeue(r))
	{
		in_checkup_P_rovers2.enqueue(r);
		in_checkup_rovers_count++;
	}


	while (in_checkup_E_rovers2.dequeue(r))
	{
		in_checkup_E_rovers.enqueue(r);

	}

	while (in_checkup_P_rovers2.dequeue(r))
	{
		in_checkup_P_rovers.enqueue(r);

	}




	cout << in_checkup_rovers_count << "In Checkup Rovers: ";
	if (in_checkup_E_rovers.peek() == nullptr)
	{
		cout << "[]" << " ";
	}
	else
	{
		cout << "[";
		while (in_checkup_E_rovers.peek())
		{

			in_checkup_E_rovers.dequeue(r);

			cout << r->get_id();

			if (in_checkup_E_rovers.peek() == nullptr)
			{
				cout << "] ";
			}
			else
			{
				cout << ", ";
			}

			in_checkup_E_rovers2.enqueue(r);


		}
	}

	if (in_checkup_P_rovers.peek() == nullptr)
	{
		cout << "()" << " ";
	}
	else
	{
		cout << "(";
		while (in_checkup_P_rovers.peek())
		{

			in_checkup_P_rovers.dequeue(r);

			cout << r->get_id();

			if (in_checkup_P_rovers.peek() == nullptr)
			{
				cout << ") ";
			}
			else
			{
				cout << ", ";
			}

			in_checkup_P_rovers2.enqueue(r);


		}
	}


	while (in_checkup_E_rovers2.dequeue(r))
	{
		in_checkup_E_rovers.enqueue(r);

	}

	while (in_checkup_P_rovers2.dequeue(r))
	{
		in_checkup_P_rovers.enqueue(r);

	}
	cout << endl;
	cout << "-------------------------------------------------------" << endl;
















	////////////////////////////////////////////////////////////










		/////////////////////////////////////////////////



	Queue<mission*> E_done_missions = S.get_E_DoneMissions_list();
	Queue<mission*> P_done_missions = S.get_P_DoneMissions_list();


	Queue<mission*> E_done_missions2;
	Queue<mission*> P_done_missions2;

	int done_missions_count = 0;

	mission* m;

	while (E_done_missions.dequeue(m))
	{
		E_done_missions2.enqueue(m);
		done_missions_count++;
	}

	while (P_done_missions.dequeue(m))
	{
		P_done_missions2.enqueue(m);
		done_missions_count++;
	}


	while (E_done_missions2.dequeue(m))
	{
		E_done_missions.enqueue(m);

	}

	while (P_done_missions2.dequeue(m))
	{
		P_done_missions.enqueue(m);

	}


	cout << done_missions_count << " Completed Missions: ";

	if (E_done_missions.peek() == nullptr)
	{

		cout << "[] ";
	}
	else
	{
		cout << "[";

		while (E_done_missions.peek())
		{

			E_done_missions.dequeue(m);


			cout << m->get_ID();
			if (E_done_missions.peek() == nullptr)
			{
				cout << "] ";
			}
			else
			{
				cout << ", ";
			}

			E_done_missions2.enqueue(m);


		}




	}


	if (P_done_missions.peek() == nullptr)
	{

		cout << "() ";
	}
	else
	{
		cout << "(";

		while (P_done_missions.peek())
		{
			P_done_missions.dequeue(m);


			cout << m->get_ID();
			if (P_done_missions.peek() == nullptr)
			{
				cout << ") ";
			}
			else
			{
				cout << ", ";
			}

			P_done_missions2.enqueue(m);


		}




	}



	while (E_done_missions2.dequeue(m))
	{
		E_done_missions.enqueue(m);

	}

	while (P_done_missions2.dequeue(m))
	{
		P_done_missions.enqueue(m);

	}
	cout << endl;
	cout << "-------------------------------------------------------" << endl;

	cout << endl;



	waiting_missions = 0;
	Ewaiting_missions = 0;
	Pwaiting_missions = 0;


	Sleep(1000);

}
void UI::silent_mode()
{
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}
void UI::wrong_input()
{
	cout << "Invalid input!!" << endl;
	Input();
}