#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

//#include "Spellable.h"

const std::string powerName[21] = {
	"thousand",
	"million",
	"billion",
	"trillion",
	"quadrillion",
	"quintillion",
	"sextillion",
	"septillion",
	"octillion",
	"nonillion",
	"decillion",
	"undecillion",
	"duodecillion",
	"tredecillion",
	"quattuordecillion",
	"quindecillion",
	"sexdecillion",
	"septendecillion",
	"octodecillion",
	"novemdecillion",
	"vigintillion"
};

template <class T>
std::string Spellable<T>::spell() {
	// Handle the fractional part first
	int l = floor(log10(*value));
	double f = *value - floor(*value);
				
	if (f > 0) {
		Spellable<T> integer(*value - f);
		
		std::ostringstream os;		
		
		// TODO: Only subtract l if floatfield is fixed!
		int precision = std::cout.precision() - l;		
		
		Spellable<int> d(pow(10, precision - 1));
		Spellable<int> n(floor(f * d.GetValue()));
		
		std::string denominator = d.spell();
		// Resorting to some string manipulation
		if (denominator.substr(0, 3) == "one") {
			denominator = denominator.substr(4);
		}
		
		os << " and " << n.spell() << " " << denominator << "th" << (n == 1 ? "" : "s");
		
		return integer.spell() + os.str();
	} else {
		switch ((int) *value) {
		case 0: return "zero";
		case 1: return "one";
		case 2: return "two";
		case 3: return "three";
		case 4: return "four";
		case 5: return "five";
		case 6: return "six";
		case 7: return "seven";
		case 8: return "eight";
		case 9: return "nine";
		case 10: return "ten";
		case 11: return "eleven";
		case 12: return "twelve";
		case 13: return "thirteen";
		case 14: return "fourteen";
		case 15: return "fifteen";
		case 16: return "sixteen";
		case 17: return "seventeen";
		case 18: return "eighteen";
		case 19: return "nineteen";
		case 20: return "twenty";
		case 30: return "thirty";
		case 40: return "forty";
		case 50: return "fifty";
		case 60: return "sixty";
		case 70: return "seventy";
		case 80: return "eighty";
		case 90: return "ninety";
		}	
		
		Spellable<T> head(floor(*value / pow(10, l)));
		Spellable<T> tail(*value - (head.GetValue() * pow(10, l)));
	
		std::string midfix;
		std::string prefix;
	
		switch (l) {
		case 0:
			
		case 1:
			head.SetValue(head.GetValue() * 10);
			midfix = "";
			prefix = "-";
			break;
		case 2:
			midfix = " hundred";
			prefix = " ";
			break;
		default:
			int p = floor(l/3 - 1);
			head = floor(*value / pow(10, l - l % 3));
			tail = *value - (head.GetValue() * pow(10, l - l % 3));			
			midfix = " " + powerName[p];
			prefix = " ";
			break;
		}
		
		return head.spell() + midfix + (tail.GetValue() > 0 ? prefix + tail.spell() : "");
	}	
};

/*
template <class T>
std::string Spellable<T>::spell() {
	int l = floor(log10(*value));
	double f = *value - floor(*value);
	
	std::string fraction;
			
	if (f > 0) {		
		std::ostringstream os;		
		// TODO: Only subtract l if floatfield is fixed!
		int precision = std::cout.precision() - l;		
		
		Spellable<int> d(pow(10, precision - 1));
		Spellable<int> n(floor(f * d.GetValue()));
		
		std::string denominator = d.spell();
		// Resorting to some string manipulation
		if (denominator.substr(0, 3) == "one") {
			denominator = denominator.substr(4);
		}
		
		os << " and " << n.spell() << " " << denominator << "th" << (n == 1 ? "" : "s");
		
		fraction = os.str();
	} else {
		fraction = "";
	}
	
	switch ((int) *value) {
	case 0: return "zero" + fraction;
	case 1: return "one" + fraction;
	case 2: return "two" + fraction;
	case 3: return "three" + fraction;
	case 4: return "four" + fraction;
	case 5: return "five" + fraction;
	case 6: return "six" + fraction;
	case 7: return "seven" + fraction;
	case 8: return "eight" + fraction;
	case 9: return "nine" + fraction;
	case 10: return "ten" + fraction;
	case 11: return "eleven" + fraction;
	case 12: return "twelve" + fraction;
	case 13: return "thirteen" + fraction;
	case 14: return "fourteen" + fraction;
	case 15: return "fifteen" + fraction;
	case 16: return "sixteen" + fraction;
	case 17: return "seventeen" + fraction;
	case 18: return "eighteen" + fraction;
	case 19: return "nineteen" + fraction;
	case 20: return "twenty";
	case 30: return "thirty";
	case 40: return "forty";
	case 50: return "fifty";
	case 60: return "sixty";
	case 70: return "seventy";
	case 80: return "eighty";
	case 90: return "ninety";
	}	
	
	Spellable<T> head(floor(*value / pow(10, l)));
	Spellable<T> tail(*value - (head.GetValue() * pow(10, l)) );

	std::string midfix;
	std::string prefix;

	switch (l) {
	case 0:
		
	case 1:
		head.SetValue(head.GetValue() * 10);
		midfix = "";
		prefix = "-";
		break;
	case 2:
		midfix = " hundred";
		prefix = " ";
		break;
	default:
		int p = floor(l/3 - 1);
		head = floor(*value / pow(10, l - l % 3));
		tail = *value - (head.GetValue() * pow(10, l - l % 3));			
		midfix = " " + powerName[p];
		prefix = " ";
		break;
	}
	
	return head.spell() + midfix + (tail.GetValue() > 0 ? prefix + tail.spell() : "")  + fraction;		
}
*/
