/**
 * This demo is meant to be straight-forward and 
 * not use very complex techniques, such as regular
 * expressions.
 * 
 */

function throwFormatError() {
  throw "You should enter a value in the form \"$987.52\" with a dollar sign and optionally two decimal places.";
}

function demo1(numeric) {
  var text = "";
  
  // Validation of the input
  if (numeric.length() < 1) {
    throwFormatError();
  }
  
  if (numeric[0] != "$") {
    throwFormatError();
  }
  
  // Strip off the dollar sign
  numeric = numeric.substring(1);
  
  // Validate that cents portion is either of length 0 or 2
  var decimalPos = numeric.lastIndexOf(".");
  
  if (decimalPos != -1 && decimalPos != numeric.length() - 4) {
    throwFormatError();
  }
  
  var cents = numeric.substring(decimalPos);
  
  numeric = numeric.substring(0, decimalPos - 1);
  
  text = numeric + " / " + cents;
  return text;
}

/**
 * demo2 uses regular expressions.
 * 
 */

function demo2(numeric) {

}
