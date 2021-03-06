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

function PositionalNumberSystem(base, ordersOfMagnitude, higherOrders, sanitizers, groupLength, separator) {
  if (base < 2 || base > 36) {
    throw new RangeError('Only bases from 2 to 36 are supported');
  }

  this.base = base;
  this.digits = digits.slice(0, this.base);
  this.ordersOfMagnitude = ordersOfMagnitude || [];
  this.higherOrders = higherOrders || [];
  this.sanitizers = sanitizers || [];
  this.groupLength = groupLength || 3;
  this.separator = separator || ' ';
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
    return this.grouped(this.getDigitArray(value)).map(this.flatten).join(this.separator) || this.digits[0].form;
  },

  sanitize: function (string) {
    return this.sanitizers.reduce(function(previous, sanitizer) {
      return previous.replace(sanitizer[0], sanitizer[1]);
    }, string);
  },

  flatten: function (digits) {
    return digits.reduce(function (previous, digit) {
      return previous + digit.form;
    }, '');
  },

  grouped: function (digits) {
    var groupLength = this.groupLength;

    // Break into groups
    var grouped = digits.reduce(function (groups, digit, index, arr) {
      var order = arr.length - 1 - index;
      groups[groups.length - 1].push(digit);

      if (order > 0 && order % groupLength === 0) {
        groups.push([]);
      }
      return groups;
    }, [[]]);

    return grouped;
  },

  _spellGroup: function (digits) {
    var orders = this.ordersOfMagnitude;
    var base = this.base;

    return this.sanitize(digits.reduce(function(previous, digit, revOrder, arr) {
      var order = arr.length - revOrder - 1;
      var spell = previous;
      if (digit.value != 0) {
        spell += ' ';
        spell += digit.name;
        if (order > 0) {
          spell += ' ' + (orders[order]||base+'^'+order);
        }

      }

      return spell;
    }, ''));
  },

  _spell: function (digits) {
    var higherOrders = this.higherOrders;
    return this.grouped(digits).map(this._spellGroup, this).reduce(function (previous, current, index, arr) {
      var order = arr.length - 1 - index;
      var orderName = higherOrders[order];
      return (previous + (current ? current + (orderName?' ' + orderName : ''):'')).trim();
    }, '') || this.digits[0].name;
  },

  spell: function (value) {
    return this._spell(this.getDigitArray(value));
  }
};

var binary = new PositionalNumberSystem(2, ['', 'pair', 'quartet', 'octet'], ['', 'kilob', 'megab', 'gigab'], [], 4);
var decimal = new PositionalNumberSystem(
    10,
    ['', 'ten', 'hundred'],
    ['', 'thousand', 'million', 'billion', 'trillion', 'quadrillion', 'quintillion'],
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
    ], 3, ','
  );
var dozenal = new PositionalNumberSystem(12, ['', 'dozen', 'gross'], ['', 'grand', 'great-grand', 'great-great-grand'], [], 3, ' ');
var hexadecimal = new PositionalNumberSystem(16, ['', 'hex', 'hectohex'], ['', 'kilohex', 'megahex', 'gigahex'], [], 2, ' ');
var base36 = new PositionalNumberSystem(36, ['', 'square-six', 'cubic-six'], ['kilox', 'megax', 'gigax'], [], 3, ',');
/*
for (var i = 0; i <= 100000; i++) {
  console.log(binary.encode(i), binary.spell(i));
  console.log(decimal.encode(i), decimal.spell(i));
  console.log(dozenal.encode(i), dozenal.spell(i));
  console.log(hexadecimal.encode(i), hexadecimal.spell(i));
  console.log(base36.encode(i), base36.spell(i));
}
*/

var bases = [binary, decimal, dozenal, hexadecimal, base36];
for (var i in bases) {
  var base = bases[i];
  var m = Math.pow(base.base, 6);
  console.log(base.encode(m), base.spell(m));
  console.log(base.encode(m-1), base.spell(m-1));
}

for (var n = 144; n > 0; n--) {
  var s = dozenal.spell(n).replace(/^([a-z])/, function (m, m1) { return m1.toUpperCase();});
  var p = dozenal.spell(n-1).replace(/^([a-z])/, function (m, m1) { return m1.toUpperCase();});
  if (s.match(/(gross|grand)$/)) {
    s += ' of';
  }
  if (p.match(/(gross|grand)$/)) {
    p += ' of';
  }

  var n1 = 'egg';
  if (n != 1) {
    n1 += 's';
  }
  var n2 = 'egg';
  if (n != 2) {
    n2 += 's';
  }
  console.log(s + ' ' + n1 + ' on the wall. ' + s + ' ' + n1 + '. Take one down, pass it around. ' + p + ' ' + n2 + ' on the wall.');
}
