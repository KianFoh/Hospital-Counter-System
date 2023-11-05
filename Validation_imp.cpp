#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <cctype>
#include "Validation.h"

using namespace std;

// Check int in range 
bool Validation::int_Inrange(int min, int max, int input) const{
	if (min <= input && max >= input){
		return true;
	}
	cout << "WARNING:Input out of range.\n" << endl;
	return false;
}

// Check for invalid input
bool Validation::input_Success() const{
	if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "WARNING:Input Failure.\n" << endl;
        return false;
	}	
	return true;
}

// Check string contain only Digi
bool Validation::onlyDigits(string str) const{
    for (size_t i = 0; i < str.length(); ++i) {
        if (!isdigit(str[i])) {
            return false; 
        }
    }
    return true; 
}

// Check date 
bool Validation::date_Valid(int d, int m, int y){ 
	// Check month
    if (m < 1 || m > 12) 
    	return false; 
    // Check day
   	if (d < 1 || d > 31) 
    	return false; 
	
	// Check Feb
    if (m == 2){ 
    	// Check leap year
        if (y%4 == 0)
        	return (d <= 29);
        else
        	return (d <= 28); 
    } 
  
  	// Check 30 days months
    if (m == 4 || m == 6 || 
    	m == 9 || m == 11) 
        return (d <= 30); 
        
    return true; 
} 

// Check string contain only letters
bool Validation::only_Letters(string str){
  for(char &c : str) {
    if(!isalpha(c))
      return false;
  }
  return true;
}

// Check yes or no input
char Validation::y_or_n_valid(string reenter_message){
	char option = ' ';
	while(true){
		cin >> option; 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if(option!= 'Y' && option!='N'){
			cout << "WARNING:Invalid input.\n";
			cout << reenter_message;
			continue;
		}
		break;
	}
	return option;
}
