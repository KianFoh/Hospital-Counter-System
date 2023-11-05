#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cctype>
#include <limits>
#include "Appointment.h"
#include "Patient.h"
#include "Validation.h"
#include "Queue.h"

using namespace std;

// Validation Object contain general validation methods
Validation v;

// Queue Declaration for priority and normal
Queue prio_Q;
Queue norm_Q;

// Constructor
Appointment::Appointment(){
	// Initiate with counter 0
	counter = 0;
}

void Appointment::display_Main(){
	// Main Menu
	cout << "Patient Queue Management System\n\n";	
	cout << left << setw(2) << "1" << left <<setw(22) << "[Patient Registration" << "]" << endl;
	cout << left << setw(2) << "2" << left <<setw(22) << "[Queue Processing" << "]" << endl;
	cout << left << setw(2) << "3" << left <<setw(22) << "[Exit" << "]" << endl << endl;
	cout << "Enter Option: ";
	cin >> option;

	// Validate option for overflow error and out of range error
	if(v.input_Success() && v.int_Inrange(1,3,option)){
		// clear input buffer
		cin.ignore();
		if(option==1)
			display_Register();
		else if(option==2)
			display_Queue_Menu();
		else{
			cout << "Programing shutting down...\n";
			exit(0);
		}
	}
	// Recall this function to continue the program
	display_Main();
};

void Appointment::display_Register(){
	// Time data
	stringstream ss;
	time_t now= time(0);
    tm *ltm = localtime(&now);
    // Current Date and time
    string am_pm = "";
	int c_d = ltm->tm_mday, c_m = ltm->tm_mon+1, c_y = ltm->tm_year+1900, hours = ltm->tm_hour;
	
	//Update counter
	counter+=1;
	
	// Patient data
	string c_time = "", ic = "", name = "";
	int age = 0;
	char gender = ' ', temp_char = ' ';
	bool priority = false;

	// Info from IC
    int d = 0, m = 0, y = 0, gen_id = 0;
	
	// Get Time info
    am_pm = (hours < 12) ? "am" : "pm"; //Get am or pm
    if (hours == 0){
        hours = 12; 
    } 
	else if (hours > 12){
        hours -= 12; 
    }
    // Formatting time data 
    ss << hours;
    string s_hours = ss.str();
    ss << ":";
    if(ltm->tm_min < 10)
    	ss << (0);
    ss << (ltm->tm_min);
    ss << am_pm;
	c_time = ss.str();
	cout << "Time: " << c_time << endl;
	
	// Get counter info
	cout << "Counter Number: " << counter << endl;
	
	// Get IC info
	cout << "Enter Patient IC: ";
	while (true){
		getline(cin, ic);
		if(ic.size()!=12)
			cout << "WARNING:Invalid IC length.\n";
		else if (!v.onlyDigits(ic))
			cout << "WARNING:IC contain non numerical value.\n";
		
		// Get date of birth from IC
		else{
			y = stoi(ic.substr(0,2));
			m = stoi(ic.substr(2,2));
			d = stoi(ic.substr(4,2));
			if(y <= 23)
				y+=2000;
			else
				y+=1900;
			if(!v.date_Valid(d,m,y))
				cout << "WARNING:IC contain Invalid date of birth.\n";
			else
				break;			
		}
			cout << "Please reenter your IC: ";
	}
	
	// Get Name info
	cout << "Enter Name: ";
	while (true){
		getline(cin, name);
		if(name == "")
			cout << "WARNING:Invalid name cannot be empty\n";
		else if(v.only_Letters(name))
			break;
		else
			cout << "WARNING:Invalid name containing non alphabets\n";
		cout << "Please reenter your name: ";
	}
	
	// Get age info
	age = c_y - y;
	if(m < c_m)
		age--;
	else if(m == c_m){
		if(d <= c_d)
			age--;
	}
	cout << "Age: " << age << endl;
	
	// Get gender info
	gen_id = stoi(ic.substr(11,1));
	if(gen_id%2 == 1){
		gender = 'M';
	}
	else{
		gender = 'F';
	}
	
	// Checking for priority
	if(age >= 55)
		priority = true;
	else{
		if(gender == 'F'){
			cout << "Pregnant [Y/N]: ";
			temp_char = v.y_or_n_valid("PLease reenter again Pregnant [Y/N]: ");
			if(temp_char == 'Y')
				priority = true;
		}
		if(!priority){
			cout << "OKU [Y/N]: ";
			temp_char = v.y_or_n_valid("PLease reenter again OKU [Y/N]: ");
			if(temp_char == 'Y')
				priority = true;
		}
	}
	
	// Checking info confirmation
	cout << "Confirm [Y/N]: ";
	temp_char = v.y_or_n_valid("PLease reenter again Confirm [Y/N]: ");
	
	// Display sucesssful registration message
	if(temp_char == 'Y'){
		Patient new_data(c_time,counter,ic,age,gender,name);
		if(priority){
			prio_Q.enQueue(new_data);
			cout << "Successfully registered as a Priority Patient.\n\n";
		}
		else{
			norm_Q.enQueue(new_data);
			cout << "Successfully registered as a Normal Patient.\n\n";
		}
	}
	// No in confirmation option, return to Main Menu
	else{
		counter--;
		cout << "Return to Main Menu\n";
	}
}

void Appointment::display_Queue_Menu(){
	// Variable for confirmation of processing queue
	char process = ' ';
	
	while(true){
		// Display Queue Menu
		cout << endl << right << setw(4) << "" << "[Active Queue Menu]\n\n";
		cout << left << setw(3) << "1." << "Normal Queue " << "(" << norm_Q.get_NumItems() << " Patients)" << endl;
		cout << left << setw(3) << "2." << "Priority Queue " << "(" << prio_Q.get_NumItems() << " patients)" << endl;
		cout << left << setw(3) << "3." << "Merge Queue" << endl;
		cout << left << setw(3) << "4." << "Return" << endl << endl;
		cout << "Enter option: ";
		cin >> option;
		// Validate option for overflow error and out of range error
		if(v.input_Success() && v.int_Inrange(1,4,option)){
			cin.ignore();
			
			// Display Patients in Normal Queue
			if(option==1){
				cout << "\n[Normal Patient Queue]\n";
				norm_Q.print();
				// Prompty User to process queue
				if(!norm_Q.isEmpty()){
					cout  << endl << "Proceed to process Normal Patient Queue [Y/N]: ";
					process = v.y_or_n_valid("PLease reenter your option [Y/N]: ");
					if(process == 'Y')
						process_Queue(norm_Q, "Normal");
				}
				else
					cout << "Normal Patient Queue is empty, returning to Queue Menu...\n\n";
			}
			
			// Display Patients in Priority Queue
			else if(option==2){
				cout << "\n[Priority Patient Queue]\n";
				prio_Q.print();
				// Prompty User to process queue
				if(!prio_Q.isEmpty()){
					cout  << endl << "Proceed to process Priority Patient Queue [Y/N]: ";
					process = v.y_or_n_valid("PLease reenter your option [Y/N]: ");
					if(process == 'Y')
						process_Queue(prio_Q, "Priority");
				}
				else
					cout << "Priority Patient Queue is empty, returning to Queue Menu...\n\n";	
			}
			else if(option==3){
				Patient temp;
				
				if(prio_Q.isEmpty())
					cout << "Priority Patient Queue is empty unable to perform merge.\n";
				// Perform merge
				else{
					while(!prio_Q.isEmpty()){
						prio_Q.deQueue(temp);
						norm_Q.enQueue_Sequence(temp);
					}
					cout << "Successfully merge priority queue to normal queue.\n";
				}		
			}

			else{
				cout << endl;
				break;
			}
		}
	}	
}

void Appointment::process_Queue(Queue &q,string q_type){
	// Variable declaration
	Patient temp;
	int counter;
	
	while(true){
		// Reset temp Name value for checking purposes
		temp.setName("Unknown");
		// Display process Queue Menu
		cout << "\n[Processing " << q_type << " Queue]\n";
		cout << left << setw(4) << "[1]" << "Call Next Patient" << endl;
		cout << left << setw(4) << "[2]" << "Call Patient No#" << endl;
		cout << left << setw(4) << "[3]" << "Delete Patient" << endl;
		cout << left << setw(4) << "[4]" << "Reset Queue" << endl;
		cout << left << setw(4) << "[5]" << "Return" << endl << endl;
		cout << "Enter Option: ";
		cin >> option;
		
		// Validate
		if(v.input_Success() && v.int_Inrange(1,5,option)){
			// Clear Buffer
			cin.ignore();
			// Dequeue get next patient then call Patient function to display info
			if(option==1){
				q.deQueue(temp);
				if(temp.getName()!="Unknown"){
					temp.call_Patient(temp);
				}
			}		
			else if(option==2||option==3){
				// Get patient num
				cout << "Please enter the patient counter number: ";
				cin >> counter;
				// Validate
				if(v.input_Success()){
					// Dequeue by counter to find patient with the num and remove 
					q.deQueue_by_counter(counter,temp);		
					if(temp.getName()!="Unknown"){
						if (option == 2){
							// Display removed patient info 
    						temp.call_Patient(temp);
    					}
 						else{
 							// Display messsge the patient hs been removed
    						cout << "Patient counter " << temp.getCounter() << " has been deleted.\n";
    					}
					}
				}
			}
			else if(option==4){
				// Use cler method to remove all patient in queue
				if(!q.isEmpty()){
					q.clear();
					cout << "Queue is Successfully deleted.\n";					
				}
				else
					cout << "The queue is empty!" << endl;
			}
			// Option 5 return to Queue Menu
			else
				break;
		}
	}
}





