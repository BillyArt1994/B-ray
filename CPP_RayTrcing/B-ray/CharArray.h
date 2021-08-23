#ifndef CHARARRY_H
#define CHARARRY_H
#include <iostream>

class CharArray
{
public:
	unsigned size = 0;

	CharArray() {}

	CharArray(const char* c)
	{
		strncpy(m_data, c, 33);
	}

	CharArray(const CharArray& c){
		this->size = c.size;
		memcpy(this->m_data, c.m_data, 33);
	}

	inline void addElement(const char& input) {
		m_data[size] = input;
		size += 1;
	}

	inline char at(const int& index) const {
		return m_data[index];
	}

	inline const char* readArrary() const {
		return m_data;
	}

	CharArray subchar(unsigned e) {
		CharArray a;
		memcpy(a.m_data,m_data, e);
		a.size = e;
		return a;
	}

	void operator = (const CharArray& a) {
		size = a.size;
		strcpy(this->m_data, a.m_data);
	}

	CharArray operator + (char value) {
		this->m_data[size] = value;
		size += 1;
		return *this;
	}

	CharArray operator + (int value) {
		CharArray c(*this);
		c.addElement(value+'0');
		return c;
	}

	void operator +=(const char& value) {
		m_data[size] = value;
		++size;
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

	char m_data[33]{ '\0'};
};

#endif // !CHARARRY_H

