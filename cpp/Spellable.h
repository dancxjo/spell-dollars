// Spellable.h
#ifndef SPELLABLE_H
#define SPELLABLE_H

#include <string>

template <class T>
class Spellable {
	T* value;
public:	
	// TODO: new values are never deleted!
	Spellable() { value = NULL; };
	Spellable(T* value): value(value) {}
	Spellable(T v) { value = new T(v); }
			
	void SetValue(T* v) { value = v; }
	void SetValue(T v) { value = new T(v); }

	T GetValue() const { return *value; }

	std::string spell();
	
	// Let's do arithmetic!
	Spellable & operator=(const T &rhs) {
		SetValue(rhs);
	}
	
	Spellable & operator+=(const T &rhs) {
    	*value += rhs;
		return *this;
	}
	
	bool operator==(const T &other) const {
		return *value == other;
	}
	
	bool operator==(const std::string &other) const {
		return spell() == other;
	}
protected:
	std::string spellFraction();
};

// http://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
// The linker gets confused if we don't include the implementation here.
#include "Spellable.cpp"


#endif // Spellable.h
