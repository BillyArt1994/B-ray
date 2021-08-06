#ifndef CHARARRY_H
#define CHARARRY_H
#include <iostream>

class CharArray
{
public:
	unsigned size = 0;

	CharArray() {}

	inline CharArray(char& c) { this->addElement(c); }

	inline CharArray(const char* c) {
		while (*c)
		{
			this->addElement(*c);
			*c++;
		}
	}

	inline void addElement(char input) {
		m_data[size] = input;
		size += 1;
	}

	inline void addElement(char input,unsigned index) {
		m_data[index] = input;
		size += 1;
	}

	inline char at(const int index) const {
		return m_data[index];
	}

	inline const char* readArrary() const {
		return m_data;
	}

	CharArray subchar(unsigned e) {
		CharArray a;
		strncpy(a.m_data, m_data, e);
		a.size = e;
		return a;
	}

	void operator = (const CharArray& a) {
		size = a.size;
		strcpy(this->m_data, a.m_data);
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

			if (strncmp(m_data, a.readArrary(), size) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	size_t operator()()const {
		size_t hash = 5381;
		const char* key = this->m_data;
		while (*key)
		{
			hash += (hash << 5) + (*key++);
		}
		return hash;
	}

private:
	char m_data[128] = { '\0' };
};

namespace std
{
	template<>
	class hash<CharArray>
	{
	public:
		size_t operator()(const CharArray& a) const
		{
			return a();
		}
	};
}

#endif // !CHARARRY_H

