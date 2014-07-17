#include <cmath>
#include <iostream>
#include <string>

//#include "Spellable.h"

const std::string POWERNAME[21] = {
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

/**
 * Necesitated due to the intricacies of determining precision.
 * Handling this as part of a recursive spell() makes impossible
 * determining the number of significant digits in the integer
 * part of the number, which is necessary for floating precision.
 *
 * @return			the spelling of the fractional portion
 */
template <class T>
std::string Spellable<T>::spellFraction() {	
	double n = *value - floor(*value);
	
	// We could get deep into floating point math. http://www.jbox.dk/sanos/source/lib/fcvt.c.html
	// See also http://pastebin.com/c84Dbvd7, http://stackoverflow.com/questions/7228438/convert-double-float-to-string			
	int precision = std::cout.precision();
	
	bool fixed = (std::cout.flags() & std::ios::floatfield & std::ios::fixed) != 0;
	bool scientific = (std::cout.flags() & std::ios::floatfield & std::ios::scientific) != 0;

	if (!fixed && !scientific) {
		// Account for the digits taken by the integer part
		precision -= floor(log10(*value)) + 1;
	}		
	
	n *= pow(10, precision);
	n = round(n);
	
	// Now cancel 0's. 
	while (n/10 == floor(n/10)) {
		n /= 10;
		precision--;
	}		
	
	Spellable<long long> numerator(floor(n));
	std::cout << numerator.spell() << std::endl;
	std::string denominator;
	
	switch (precision) {
		case 0: denominator = "one"; break; // This shouldn't happen
		case 1: denominator = "tenth"; break;
		case 2: denominator = "hundredth"; break;
		default:
			denominator = POWERNAME[(int)floor(precision/3 - 1)] + "th";
			switch(precision % 3) {
				case 1: denominator = "ten " + denominator; break;
				case 2: denominator = "hundred " + denominator; break;
			}
			break;
	}
			
	return numerator.spell() + " " + denominator + (n == 1 ? "" : "s");
}

template <class T>
std::string Spellable<T>::spell() {
	// Handle negatives
	if (*value < 0) {
		Spellable<T> positive(*value * -1);
		return "negative " + positive.spell();
	}
	
	// l is the number of places in the number's integer part
	int l = floor(log10(*value));
	
	// Handle the fractional part first		
	if (*value > 0 && *value < 1) {
		return spellFraction();
	}
	
	double f = *value - floor(*value);
				
	if (f > 0) {
		Spellable<T> integer(*value - f);
		return integer.spell() + " and " + spellFraction();
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
		
		Spellable<T> head(floor(*value / pow(10,  l)));
		Spellable<T> tail(*value - (head.GetValue() * pow(10,  l)));
	
		std::string midfix;
		std::string prefix;
	
		switch (l) {
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
			head = floor(*value / pow(10,  l - l % 3));
			tail = *value - (head.GetValue() * pow(10,  l - l % 3));			
			midfix = " " + POWERNAME[p];
			prefix = " ";
			break;
		}
		
		return head.spell() + midfix + (tail.GetValue() > 0 ? prefix + tail.spell() : "");
	}	
};
