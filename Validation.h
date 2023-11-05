#ifndef _Validation_
#define _Validation_

using namespace std;

class Validation{
	
	public:
		bool int_Inrange(int, int, int) const; // check Int range
		bool input_Success() const; // check Input overfloww error
		bool onlyDigits(string) const; // check string contain digits only
		bool date_Valid(int, int, int); // check date correct or not
		bool only_Letters(string); // check string contains only letters
		char y_or_n_valid(string); // check yes or no options
};


#endif
