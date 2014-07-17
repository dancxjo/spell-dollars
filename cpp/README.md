This is the C++ version of the program laid out in the folder above this one. 
Rather than translating the trivial recursive function laid out earlier, this
project aims at demonstrating a grasp of OOP.

I start out first by implementing a class called Spellable, which uses templates
to create a spellable version of the numeric types. (TODO: Implement arithmetic 
operators.)

Moving forward, I will implement a subclass of Spellable that handles unitized
amounts (i.e. quantities). Then as a subclass of that, I can implement dollars.

Compiling
---------
Since Spellable uses a class template, linking is quirky. To overcome this, I've
included Spellable.cpp in Spellable.h (so including Spellable.h includes Spellable.cpp).
It is, therefore, unneccessary to compile and link Spellable.cpp.
