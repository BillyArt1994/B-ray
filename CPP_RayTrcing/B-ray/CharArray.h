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

	bool operator == (const CharArray& a) {
		if (size != a.size)
		{
			return false;
		}
		else
		{

			if (strcmp(_array, a.readArrary()) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

private:
	char _array[128] = {'\0'};
};

namespace std
{
	template<>
	class hash<CharArray>
	{
	public:
		size_t operator()( CharArray& a,CharArray& b) const
		{
			return (a == b);
		}
	};
}

#endif // !CHARARRY_H

