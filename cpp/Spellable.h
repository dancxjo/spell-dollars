// Spellable.h
#ifndef SPELLABLE_H
#define SPELLABLE_H

#include <string>

template <class T>
class Spellable {
	T* value;
public:
	Spellable() {};
	Spellable(T* value): value(value) {};
	void SetValue(T* v) { value = v; }
	std::string spell();
};

// http://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// The linker gets confused if we don't include the implementation here.
#include "Spellable.cpp"


#endif // Spellable.h
