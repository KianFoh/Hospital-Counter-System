#ifndef _PATIENT_
#define _PATIENT_

using namespace std;

class Patient{
	private:
		string time;
		int counter;
		string ic;
		int age;
		char gender;
		string name;
		
	public:
		//Constructor
		Patient(string, int, string, int, char, string);
		Patient();
		
		//Getter
		string getTime();
		int getCounter();
		string getIc();
		int getAge();
		char getGender();
		string getName();
		
		//Setter
		void setTime(string);
		void setCounter(int);
		void setIc(string);
		void setAge(int);
		void setGender(char);
		void setName(string);
		void call_Patient(Patient); //Method for displaying patient info
};

#endif
