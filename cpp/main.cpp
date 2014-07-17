#include <iostream>

#include "Spellable.h"

using namespace std;

int main(int argc, char** argv) {	
	int i = 195;
	Spellable<int> si(&i);
	Spellable<int> sj(i);	
	
	cout << i << endl << si.spell() << endl << endl;
	
	// si is bound to i
	i = 190;
	cout << i << endl  << si.spell() << endl;
	
	cout << sj.GetValue() << endl  << sj.spell() << endl;
	
	// We can also, obviously, use a constant
	Spellable<int> sk(190);
	cout << sk.GetValue() << endl  << sk.spell() << endl << endl;		

	Spellable<double> sg(20.12315);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	sg = 20.5;
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	sg = 20.1;
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	sg = 1.0 / 3.0;
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	cout.precision(7);			
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	
	cout.setf(ios::fixed, ios::floatfield);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	
	// The following crashes the program
	cout.precision(14);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;
	cout.unsetf(ios::floatfield);
	
	// We can handle assignment and negative numbers
	sg = -4234.62;
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	return 0;
	
	// TODO: This is the largest long long and it is off by one
	// Slightly smaller numbers are off by an order of magnitude
	//Spellable<long long> sm(9223372036854775807);
  	  	
  	//cout << sm.GetValue() << endl  << sm.spell() << endl << endl;
		
}
