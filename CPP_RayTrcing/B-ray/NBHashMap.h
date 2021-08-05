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
	unsigned _capacity = 1 << 4;
	unsigned _count = 0;
	float _loadFactor = 0.75f;
	hash_node<_Key, _Value>* hashtable = nullptr;

	//hash函数
	size_t hash(const char* input, unsigned length, unsigned ID) {
		int hash = 0;
		const char* key = input;
		switch (ID)
		{
		case 0:
			for (size_t i = 0; i < length; i++)
			{
				hash = 131 * hash + *key++;
			}
			break;
		case 1:
			for (size_t i = 0; i < length; i++)
			{
				hash = ((hash << 5) + hash) + *key++;
			}
			break;
		case 2:
			for (size_t i = 0; i < length; i += 2)
			{
				hash ^= ((hash << 7) ^ (*key++) ^ (hash >> 3));
				hash ^= (~((hash << 11) ^ (*key++) ^ (hash >> 5)));
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
		unsigned length = c.size;
		size_t hashCode = hash(key, length, HASH_OFFSET);
		unsigned index, startPos;
		index = startPos = GetIndex(hashCode);
		size_t hashA = hash(key, length, HASH_A);
		size_t hashB = hash(key, length, HASH_B);

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
