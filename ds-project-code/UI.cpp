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
	while (!temp.IsEmpty())
	{
		temp.dequeue(M);
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
	Queue<mission*> temp;
	temp = S.get_Ewaiting_list();
	while(!(S.get_Ewaiting_list().IsEmpty()))
	{
		S.get_Ewaiting_list().dequeue(M);
		cout << M->get_ID() << ",";
	}
	cout << "]" << " ";
	cout << "(";
	temp = S.get_Pwaiting_list();
	while (!(S.get_Pwaiting_list().IsEmpty()))
	{
		S.get_Pwaiting_list().dequeue(M);
		cout << M->get_ID() << ",";
	}
	cout << ")" << " ";
	cout << endl;
	cout << " In-Execution Missions/Rovers: " << "[" << "," << "] " << "(" << "," << ")" << endl;
	
	cout<<"Available Rovers: "<< "[" << "," << "] " << "(" << "," << ")" << endl;
	
	cout << "In-Checkup Rovers: " << "[" << "," << "] " << "(" << "," << ")" << endl;
	
	cout << "Completed Missions: " << "[" << "," << "] " << "(" << "," << ")" << endl;
}
void UI::stepByStep_mode(station S)
{

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