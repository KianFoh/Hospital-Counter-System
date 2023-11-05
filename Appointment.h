#ifndef _APPOINTMENT_
#define _APPOINTMENT_
#include "Queue.h"

using namespace std;

class Appointment{
	private:
		int option;
		int counter;
	public:
		Appointment();
		void display_Main(); // Display Main Menu
		void display_Register(); // Display Register
		void display_Queue_Menu(); // Display Queue Menu
		void process_Queue(Queue &, string); //Display Queue Process Menu
};


#endif
