#include <iostream>
#include "Patient.h"

using namespace std;

//Constructor
Patient::Patient(string time, int counter, string ic, int age, char gender, string name){
	setTime(time);
	setCounter(counter);
	setIc(ic);
	setAge(age);
	setGender(gender);
	setName(name);
}

Patient::Patient(){
	setTime("Unknown");
	setCounter(0);
	setIc("Unknown");
	setAge(0);
	setGender('N');
	setName("Nameless");
}

//Getter
string Patient::getTime(){
	return time;
}
int Patient::getCounter(){
	return counter;
}
string Patient::getIc(){
	return ic;
}
int Patient::getAge(){
	return age;
}
char Patient::getGender(){
	return gender;
}
string Patient::getName(){
	return name;
}

//Setter
void Patient::setTime(string time){
	this->time = time;
}
void Patient::setCounter(int counter){
	this->counter = counter;
}
void Patient::setIc(string ic){
	this->ic = ic;
}
void Patient::setAge(int age){
	this->age = age;
}
void Patient::setGender(char gender){
	this->gender = gender;
}
void Patient::setName(string name){
	this->name = name;
}

void Patient::call_Patient(Patient p){
	cout << "\nCalling ";
	(p.getGender()=='M') ? cout << "Mr " : cout << "Ms ";
	cout << p.getName() << "......No " << p.getCounter() << ".\n"; 
}


