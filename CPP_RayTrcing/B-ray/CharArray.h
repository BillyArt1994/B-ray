#ifndef CHARARRY_H
#define CHARARRY_H
#include <iostream>

class CharArray
{
public:
	unsigned size = 0;

	CharArray() {}

	CharArray(char c) { this->addElement(c); }

	void addElement(char input) {
		_array[size] = input;
		size += 1;
	}

	void addElement(char input,unsigned index) {
		_array[index] = input;
		size += 1;
	}

	char at(const int index) {
		return _array[index];
	}

	const char* readArrary()const {
		return _array;
	}

	CharArray subchar(unsigned e) {
		CharArray a;
		strncpy(a._array, _array, e);
		a.size = e;
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

	CharArray operator + (int value) {
		CharArray a;
		a = *this;
		a.addElement(value+'0');
		return a;
	}

	bool operator == (const CharArray& a) const {
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
	char _array[128] = { '\0' };
};

namespace std
{
	template<>
	class hash<CharArray>
	{
	public:
		size_t operator()(const CharArray& a) const
		{
			return hash<std::string>()(a.readArrary()) ^ hash<int>()(a.size);
		}

	};
}

#endif // !CHARARRY_H

