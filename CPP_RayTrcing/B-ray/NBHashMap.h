#ifndef NBHASHMAP_H
#define NBHASHMAP_H

#include "Math.h"
#include "CharArray.h"
#include <string>
#include <windows.h>
#include <iterator>
using std::pair;

template <class T_Value>
struct hash_node
{
	hash_node() {}
	hash_node(CharArray k, T_Value v) :_key(k), _value(v) {}
	CharArray _key;
	T_Value _value;
	size_t _hashA = -1;
	size_t _hashB = -1;
	bool bExists = false;
};

//Hash表
template <class T_Value>
class NBhash_map {
private:
	unsigned _capacity = 1 << 4;
	unsigned _count = 0;
	float _loadFactor = 0.75f;

	hash_node<T_Value>* hashtable = nullptr;

	//hash函数
	size_t hash(const char* input, unsigned length, unsigned ID) {
		int hash = 0;
		switch (ID)
		{
		case 0:
			for (size_t i = 0; i < length; i++)
			{
				hash = 131 * hash + *input++;
			}
			break;
		case 1:
			for (size_t i = 0; i < length; i++)
			{
				hash = ((hash << 5) + hash) + *input++;
			}
			break;
		case 2:
			for (size_t i = 0; i < length; i += 2)
			{
				hash ^= ((hash << 7) ^ (*input++) ^ (hash >> 3));
				hash ^= (~((hash << 11) ^ (*input++) ^ (hash >> 5)));
			}
			break;
		}
		return  (hash & 0x7FFFFFFF);
	}

	//获得hash表索引
	unsigned GetIndex(const size_t& hash) {
		return hash & (_capacity - 1);
	}

	void reSize() {

		hash_node<T_Value>* old_hash_table = hashtable;
		int old_capacity = _capacity;
		unsigned new_capacity = Nearest2Power(_capacity + 1);
		hashtable = new hash_node<T_Value>[new_capacity];
		_capacity = new_capacity;
		_count = 0;
		for (size_t i = 0; i < old_capacity; i++)
		{
			hash_node<T_Value>* node = &old_hash_table[i];
			if (node->bExists)
			{
				this->insert(node->_key, node->_value);
			}
		}
		delete[] old_hash_table;
	}


public:

	NBhash_map() :hashtable(new hash_node<T_Value>[_capacity]) {
	}

	~NBhash_map() {
		delete[] hashtable;
	}

	void insert(CharArray key, T_Value vlue) {

		if (_count >= _loadFactor * _capacity)
		{
			reSize();
		}

		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		const char* code = key.readArrary();
		unsigned length = key.size;
		size_t hashCode = hash(code, length, HASH_OFFSET);
		unsigned index, startPos;
		index = startPos = GetIndex(hashCode);
		size_t hashA = hash(code, length, HASH_A);
		size_t hashB = hash(code, length, HASH_B);

		do
		{
			hash_node<T_Value>* nodePtr = &hashtable[index];
			if (nodePtr->bExists == false)
			{
				nodePtr->_key = key;
				nodePtr->_hashA = hashA;
				nodePtr->_hashB = hashB;
				nodePtr->bExists = true;
				_count += 1;
				break;
			}

			if (nodePtr->_hashA == hashA && nodePtr->_hashB == hashB)
			{
				int x;
				x = MessageBox(NULL, "hash表中已经存在相同Key值 ！！", "提示", MB_OK);
			}

			index = GetIndex(index + 1);

		} while (index != startPos);
	}

	bool find(const CharArray& key,T_Value& v) {

		unsigned length = key.size;
		const char* str = key.readArrary();
		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		size_t hashPos = hash(str, length, HASH_OFFSET);
		size_t hashA = hash(str, length, HASH_A);
		size_t hashB = hash(str, length, HASH_B);
		unsigned index, startPos;
		index = startPos = GetIndex(hashPos);

		do
		{
			hash_node<T_Value>* node = &(hashtable[index]);

			if (node->bExists == false)
			{
				return false;
			}

			if (node->_hashA == hashA && node->_hashB == hashB)
			{

				v = node->_value;
				return true;

			}

			index += 1;

			if (index >= _capacity)
			{
				index = 0;
			}

		} while (index != startPos);

		return false;
	}
};

#endif
