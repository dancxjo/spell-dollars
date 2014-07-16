// Spellable.h
#ifndef SPELLABLE_H
#define SPELLABLE_H

#include <string>

template <class T>

class Spellable {
	T* value;
public:
	Spellable(T* value): value(value) {};
	std::string spell();
};

#endif // Spellable.h
