#include <iostream>

#include "Spellable.h"

int main()
{
  int i = 195;
  long long l = 9223372036854775807;
  float f = 89759.12312;
  
  Spellable<int> si(&i);
  Spellable<long long> sl(&l);
  Spellable<float> sf(&f);
  
  cout << si.spell() << endl;
  cout << sl.spell() << endl;
  cout << sf.spell() << endl;

  return 0;
}
