function Digit(form, value, name) {
  this.value = value;
  this.form = form;
  this.name = name;
}

var digitNames = [
  'zero','one','two','three','four','five','six','seven','eight','nine',
  'ten','eleven','twelve','thirteen','fourteen','fifteen','sixteen','seventeen','eighteen','nineteen',
  'twenty', 'twenty-one', 'twenty-two', 'twenty-three', 'twenty-four', 'twenty-five', 'twenty-six', 'twenty-seven', 'twenty-eight', 'twenty-nine',
  'thirty', 'thirty-one', 'thirty-two', 'thirty-three', 'thirty-four', 'thirty-five'
];

var digits = (Array.prototype.map).call('0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ', function(digitForm, digitValue) {
  return new Digit(digitForm, digitValue, digitNames[digitValue]);
});

//console.dir(digits);

function PositionalNumberSystem(base, ordersOfMagnitude, sanitizers) {
  if (base < 2 || base > 36) {
    throw new RangeError('Only bases from 2 to 36 are supported');
  }

  this.base = base;
  this.digits = digits.slice(0, this.base);
  this.ordersOfMagnitude = ordersOfMagnitude || [];
  this.sanitizers = sanitizers || [];
}

PositionalNumberSystem.prototype = {
  int: function (value) {
    var n = value;
    var i = 0;
    var digit = [];

    while (n > 0) {
      digit.unshift(this.digits[Math.floor(n % this.base)]);
      n = Math.floor(n / this.base);
    }

    return digit;
  },

  // TODO: Account for fractional part
  getDigitArray: function (value) {
    return this.int(value);
  },

  encode: function (value) {
    return this.getDigitArray(value).reduce(function(previous, digit) {
      if (digit.value != 0 || previous != '') {
        return previous + digit.form;
      } else {
        return '';
      }
    }, '') || this.digits[0].form;
  },

  sanitize: function (string) {
    return this.sanitizers.reduce(function(previous, sanitizer) {
      return previous.replace(sanitizer[0], sanitizer[1]);
    }, string);
  },

  spell: function (value) {
    var orders = this.ordersOfMagnitude;
    var base = this.base;
    return this.sanitize(this.getDigitArray(value).reduce(function(previous, digit, revOrder, arr) {
      var order = arr.length - revOrder - 1;
      var spell = previous;
      if (digit.value != 0) {
        spell += ' ';
        spell += digit.name;
      }
      if (order > 0) {
        spell += ' ' + (orders[order]||base+'^'+order);
      }
      return spell;
    }, '') || this.digits[0].name);

  }
};

var binary = new PositionalNumberSystem(2, ['', 'pair', 'quartet', 'octet']);
var ternary = new PositionalNumberSystem(3, ['', 'trio', 'nonet']);
var quartal = new PositionalNumberSystem(4, ['', 'quartet']);
var quintal = new PositionalNumberSystem(5, ['', 'hand']);
var sextal = new PositionalNumberSystem(6, ['', 'sextet']);
var septal = new PositionalNumberSystem(7, ['', 'septet']);
var octal = new PositionalNumberSystem(8, ['', 'octet']);
var decimal = new PositionalNumberSystem(
    10,
    [
      '', 'ten', 'hundred',
      'thousand', 'ten', 'hundred',
      'million', 'ten', 'hundred',
      'billion', 'ten', 'hundred',
      'trillion', 'ten', 'hundred'
    ],
    [
      ["one ten", "ten"],
      ["two ten", "twenty"],
      ["three ten", "thirty"],
      ["four ten", "forty"],
      ["five ten", "fifty"],
      ["six ten", "sixty"],
      ["seven ten", "seventy"],
      ["eight ten", "eighty"],
      ["nine ten", "ninety"],
      ["ten one", "eleven"],
      ["ten two", "twelve"],
      ["ten three", "thirteen"],
      ["ten four", "fourteen"],
      ["ten five", "fifteen"],
      ["ten six", "sixteen"],
      ["ten seven", "seventeen"],
      ["ten eight", "eighteen"],
      ["ten nine", "nineteen"],
    ]
  );
var dozenal = new PositionalNumberSystem(12, ['', 'dozen', 'gross', 'grand', 'dozen grand', 'gross grand']);
var hexadecimal = new PositionalNumberSystem(16, ['', 'hex', 'byte', 'grand', 'hex grand', 'byte grand']);
var base36 = new PositionalNumberSystem(36, ['', 'trix', 'hectox', 'kilox', 'trix kilox', 'hectox kilox', 'megax', 'trix megax', 'hectox megax', 'gigax', 'trix gigax', 'hectox gigax']);

for (var i = 0; i <= 100000; i++) {
  console.log(binary.encode(i), binary.spell(i));
  console.log(decimal.encode(i), decimal.spell(i));
  console.log(dozenal.encode(i), dozenal.spell(i));
  console.log(hexadecimal.encode(i), hexadecimal.spell(i));
  console.log(base36.encode(i), base36.spell(i));
}
