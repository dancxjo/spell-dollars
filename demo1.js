/**
 * Returns a spelled-out version of the dollar value entered.
 *
 * @param	numeric	a dollar amount in numbers with a dollar 
 *                sign and an optional 2-digit cents portion
 *                and optional comma separators
 * @return				the spelled-out version
 */
function demo1(numeric) {
  var text = "";
  
  var pattern = /^\$(([\d]{1,3}(,([\d]{3}))+)|([\d]+))(\.([\d]{2}))?$/;
  
  if (!pattern.test(numeric)) {
  	throw "You should enter a value in the form \"$987.52\" with a dollar sign and, optionally, two decimal places.";
  }
	
	var parts = pattern.exec(numeric);
	
	numeric = parts[1].replace(/,/g, "");
	var cents = parts[7];
    
  text = spellOut(numeric) + " dollars and " + spellOut(cents) + " cents";  
  return text;
}

var prefix = ["", "m", "b", "tr", "quadr", "quint", "sext", "sept", "oct", "non", "dec", "undec", "duodec", "tredec", "quattuordec", "quindec", "sexdec", "septendec", "octodec", "novemdec", "vigint"];

function powerName(p) {
	if (p == 0) return "thousand";	
	
	if (p == 100) return "centillion";
	
	if (prefix[p] === undefined) {
		throw "The number is too large to be represented in text. Might I suggest scientific notation instead?";
	}
	
	return prefix[p] + "illion"; 
}

/**
 * Returns a spelled-out version of an integer 
 *
 * @param	 i					 a whole number
 * @return						 the spelled-out version
 */
function spellOut(i) {
	i = Number(i);
	// Take care of non-systematic names automatically
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
	
	var l = Math.floor(Math.log(i) / Math.LN10);		
	var head = Math.floor(i / Math.pow(10, l));
	var tail = i - (head * Math.pow(10, l));
	
	switch (l) {
		case 1: return spellOut(head * 10) + "-" + spellOut(tail);
		case 2: return spellOut(head) + " hundred" + (tail > 0 ? " " + spellOut(tail) : "");		
		default:
			var p = Math.floor(l/3 - 1);	// the index of the prefix						
			head = Math.floor(i / Math.pow(10, l - l % 3));
			tail = i - (head * Math.pow(10, l - l % 3));			
			return spellOut(head) + " " + powerName(p) + (tail > 0 ? " " + spellOut(tail) : "");
	}		
}
