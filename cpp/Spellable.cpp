#include <string>
#include <cmath>

#include "Spellable.h"

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
	int i = (int) *value; // Only use this for small values
	
	switch (i) {
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
		
	T l = floor(log10(*value));    	
	T head = floor(*value / pow(10, l));
	T tail = *value - (head * pow(10, l));
    Spellable<T> h;
    Spellable<T> t;
    
  switch (l) {
  case 1:
  	head *= 10;
  	h(&head);
  	t(&tail);
  	return h.spell() + "-" + t.spell();
  case 2: 
  	h(&head);
  	t(&tail);
  	return h.spell() + " hundred" + (tail > 0 ? " " + t.spell() : "");
  default:
	int p = floor(l/3 - 1);	// the index of the prefix						
	head = floor(*value / pow(10, l - l % 3));
	tail = *value - (head * pow(10, l - l % 3));
	h(&head);
  	t(&tail);
	return h.spell() + " " + powerName[p] + (tail > 0 ? " " + t.spell : "");
    }

  return "unspellable value";
}
