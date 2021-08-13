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
		strncpy(this->m_data, m_data, e);
		this->size = e;
		return *this;
	}

	void operator = (const CharArray& a) {
		size = a.size;
		strcpy(this->m_data, a.m_data);
	}

	CharArray operator + (char value) {
		this->m_data[size] = value;
		return *this;
	}

	CharArray operator + (int value) {
		this->m_data[size]=value+'0';
		return *this;
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

private:
	char m_data[128] = { '\0' };
};

#endif // !CHARARRY_H

