#ifndef NBHASHMAP_H
#define NBHASHMAP_H

#include "Math.h"
#include "CharArray.h"
#include <string>
#include <windows.h>
#include <iterator>
using std::pair;

template <class _Key, class _Value>
struct hash_node
{
	hash_node() {}
	hash_node(pair<_Key, _Value> p) :_data(p) {}
	pair<_Key, _Value> _data;
	size_t _hashA = -1;
	size_t _hashB = -1;
	bool bExists = false;

	bool operator ==(const hash_node& a) {
		if (this->_data == a._data)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator !=(const hash_node& a) {
		if (this->_data == a._data)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

};

//Hash表
template <class _Key, class _Value>
class NBhash_map {
private:
	unsigned _capacity = 1<<4;
	unsigned _count = 0;
	float _loadFactor = 0.75f;
	hash_node<_Key, _Value>* hashtable = nullptr;

	//hash函数
	size_t hash(const char* input, unsigned ID) {
		int hash = 0;
		const char* key = input;
		switch (ID)
		{
		case 0:
			while (*key)
			{
				hash = 131 * hash + *key++;
			}
			break;
		case 1:
			while (*key)
			{
				hash = ((hash << 5) + hash) + *key++;
			}
			break;
		case 2:
			int i= 0;
			for (i = 0; *key; i++)
			{
				if ((i & 1) == 0)
				{
					hash ^= ((hash << 7) ^ (*key++) ^ (hash >> 3));
				}
				else
				{
					hash ^= (~((hash << 11) ^ (*key++) ^ (hash >> 5)));
				}
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

		hash_node<CharArray, _Value>* old_hash_table = hashtable;
		int old_capacity = _capacity;
		unsigned new_capacity = Nearest2Power(_capacity + 1);
		hashtable = new hash_node<CharArray, _Value>[new_capacity];
		_capacity = new_capacity;
		_count = 0;
		for (size_t i = 0; i < old_capacity; i++)
		{
			hash_node<CharArray, _Value>* node = &old_hash_table[i];
			if (node->bExists)
			{
				this->insert(node->_data);
			}
		}
		delete[] old_hash_table;
	}

	void prepareCryptTable() {

		unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;
		for (index1 = 0; index1 < 0x100; index1++)
		{
			for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
			{
				unsigned long temp1, temp2;
				seed = (seed * 125 + 3) % 0x2AAAAB;
				temp1 = (seed & 0xFFFF) << 0x10;
				seed = (seed * 125 + 3) % 0x2AAAAB;
				temp2 = (seed & 0xFFFF);
				cryptTable[index2] = (temp1 | temp2);
			}
		}

	}

public:

	NBhash_map() :hashtable(new hash_node<_Key, _Value>[_capacity]) {
	}

	~NBhash_map() {
		delete[] hashtable;
	}

	void insert(const pair< _Key, _Value > input) {

		if (_count >= _loadFactor * _capacity)
		{
			reSize();
		}

		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		CharArray c = input.first;
		const char* key = c.readArrary();
		size_t hashCode = hash(key, HASH_OFFSET);
		unsigned index, startPos;
		index = startPos = GetIndex(hashCode);
		size_t hashA = hash(key, HASH_A);
		size_t hashB = hash(key, HASH_B);

		do
		{
			hash_node<_Key, _Value>* nodePtr = &hashtable[index];
			if (nodePtr->bExists == false)
			{
				nodePtr->_data = input;
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

	class iterator
	{
	private:
		hash_node<_Key, _Value>* m_ptr;
	public:
		iterator() {}
		iterator(hash_node<_Key, _Value>* p) : m_ptr(p) {}

		pair<_Key, _Value>* operator ->() const {
			return &(this->m_ptr->_data);
		}

		void operator = (iterator a) {
			this->m_ptr = a.m_ptr;
		}

		bool operator == (iterator a) {

			if (this->m_ptr->_data == a.m_ptr->_data)
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		bool operator != (iterator a) {
			if (this->m_ptr->_data == a.m_ptr->_data)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	};

	template<class _K>
	iterator find(const _K& key) {
		return NULL;
	}

	template<>
	iterator find(const CharArray& key) {

		const char* str = key.readArrary();
		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		size_t hashPos = hash(str, HASH_OFFSET);
		size_t hashA = hash(str, HASH_A);
		size_t hashB = hash(str, HASH_B);
		unsigned index, startPos;
		index = startPos = GetIndex(hashPos);

		do
		{
			hash_node<CharArray, _Value>* node = &(hashtable[index]);

			if (node->bExists == false)
			{
				return this->end();
			}

			if (node->_hashA == hashA && node->_hashB == hashB)
			{

				return iterator(node);

			}

			index += 1;

			if (index >= _capacity)
			{
				index = 0;
			}

		} while (index != startPos);

		return this->end();
	}

	iterator end() const {
		return iterator(&(hashtable[_capacity + 1]));
	}

	iterator begin() const {
		return iterator(&(hashtable[0]));
	}

	unsigned count() const {
		return _count;
	}

	unsigned capacity() const {
		return _capacity;
	}

};

#endif
