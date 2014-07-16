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
	
	// TODO: This is the largest long long and it is off by one
	// Slightly smaller numbers are off by an order of magnitude
	Spellable<long long> sm(9223372036854775807);
  	  	
  	cout << sm.GetValue() << endl  << sm.spell() << endl << endl;
	
	
	// Some quirks of floating point			
	Spellable<double> sg(20.12312);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	
	cout.precision(3);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	
	cout.precision(4);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	
	cout.precision(5);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
		
	// TODO: Fixing the decimal causes the fraction's precision to be short
	/*
	cout.setf(ios::fixed, ios::floatfield);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	
	cout.precision(14);	
	cout << sg.GetValue() << endl  << sg.spell() << endl;	
	*/
	return 0;
}
