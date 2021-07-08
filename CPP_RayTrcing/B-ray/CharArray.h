#ifndef CHARARRY_H
#define CHARARRY_H
#include <iostream>

class CharArray
{
public:
	unsigned size = 0;

	CharArray() {}

	void addElement(char input) {
		_array[size] = input;
		size += 1;
	}

	const char* readArrary()const {
		return _array;
	}

	CharArray subchar(unsigned e) {
		CharArray a;
		strncpy(a._array, _array, e);
		return a;
	}

	void operator = (const CharArray& a) {
		size = a.size;
		strcpy(_array, a._array);
	}

	CharArray operator + (char value) {
		CharArray a;
		a = *this;
		a.addElement(value);
		return a;
	}
private:
	char _array[128] = {'\0'};
};

bool operator ==(const CharArray& a, const CharArray& b) {
	if (a.size != b.size)
	{
		return false;
	}
	else
	{

		if (strcmp(a.readArrary(), b.readArrary()) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

#endif // !CHARARRY_H

