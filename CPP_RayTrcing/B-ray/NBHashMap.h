#ifndef NBHASHMAP_H
#define NBHASHMAP_H

#include "Math.h"
#include <string>
#include <windows.h>
#include "CharArray.h"
using std::pair;

template<class Key, class Value>
//Hash节点
class hash_node
{
private:
	pair<Key, Value> _data;
	size_t _hashA = 0;
	size_t _hashB = 0;
public:

	hash_node(const pair<Key, Value>& input) :_data(input) {
	}

	~hash_node() {}

	hash_node() {}

	pair<Key, Value> readData() const {
		return _data;
	}

	size_t getHashA() const {
		return _hashA;
	}

	size_t getHashB() const {
		return _hashB;
	}

	void setHashA(size_t hash) {
		_hashA = hash;
	}

	void setHashB(size_t hash) {
		_hashB = hash;
	}

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

	void operator =(const hash_node&a) {
		this->_data = a.readData();
		this->_hashA = a.getHashA();
		this->_hashB = a.getHashB();
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
template <class Key, class Value>
class NBhash_map {

};


template <class Value>
class NBhash_map<CharArray, Value>
{
public:
	NBhash_map() :hash_table(new hash_node<CharArray, Value>[_capacity]) {};

	~NBhash_map()
	{
		delete[] hash_table;
	}

	void insert(const pair<CharArray, Value>& input) {

		if (_count >= _loadFactor * _capacity)
		{
			reSize();
		}

		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		hash_node<CharArray, Value> node(input);
		CharArray t = input.first;
		const char* keyCode = t.readArrary();
		size_t hashPos = hash(keyCode, HASH_OFFSET);
		unsigned index, startPos;
		index = startPos = GetIndex(hashPos);
		node.setHashA(hash(keyCode, HASH_A));
		node.setHashB(hash(keyCode, HASH_B));

		do
		{
			hash_node<CharArray, Value>* nodePtr = &hash_table[index];
			if (*nodePtr == hash_node<CharArray, Value>())
			{
				*nodePtr = node;
				_count += 1;
				break;
			}

			if (nodePtr->getHashA() == node.getHashA() && nodePtr->getHashB() == node.getHashB())
			{
				int x;
				x = MessageBox(NULL, "hash表中已经存在相同Key值 ！！", "提示", MB_OK);
			}

			index = GetIndex(index + 1);
		} while (index != startPos);

	};

	template<class K>
	Value find(const K& key) {
		return NULL;
	};

	template<>
	Value find(const CharArray& Key) {
		const char* str = Key.readArrary();
		const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		size_t hashPos = hash(str, HASH_OFFSET);
		size_t hashA = hash(str, HASH_A);
		size_t hashB = hash(str, HASH_B);
		unsigned index, startPos;
		index = startPos = GetIndex(hashPos);

		do
		{
			hash_node<CharArray, Value> node = hash_table[index];

			if (node == hash_node<CharArray, Value>())
			{
				return NULL;
			}

			if (node.getHashA() == hashA && node.getHashB() == hashB)
			{
				return node.readData().second;
			}

			index += 1;

			if (index >= _capacity)
			{
				index = 0;
			}

		} while (index != startPos);

		return NULL;
	}

	unsigned& getCapacity() const {
		return _capacity;
	}

	unsigned& getCount() const {
		return _count;
	}

	hash_node<CharArray, Value>* getHash_tablePtr()const {
		return hash_table;
	}

private:
	unsigned _capacity = 1 << 4;
	hash_node<CharArray, Value>* hash_table = nullptr;
	unsigned _count = 0;
	float _loadFactor = 0.75f;
	unsigned GetIndex(const size_t& hash) {
		return hash & (_capacity - 1);
	}

	void reSize() {
		hash_node<CharArray, Value>* old_hash_table = hash_table;
		int old_capacity = _capacity;
		unsigned new_capacity = Nearest2Power(_capacity + 1);
		hash_table = new hash_node<CharArray, Value>[new_capacity];
		_capacity = new_capacity;
		_count = 0;
		for (size_t i = 0; i < old_capacity; i++)
		{
			hash_node<CharArray, Value>* node = &old_hash_table[i];
			if (*node != hash_node<CharArray, Value>())
			{
				this->insert(node->readData());
			}
		}
		delete[] old_hash_table;
	}

	size_t hash(const char* input, unsigned ID) {

		int hash = 0;
		const char* key = input;
		switch (ID)
		{
		case 0:
			hash = 0;
			while (*key)
			{
				hash = 33 * hash + *key++;
			}
			break;
		case 1:
			hash = 0;
			while (*key)
			{
				hash = ((hash << 5) + hash) + *key++;
			}
			break;
		case 2:
			hash = 53581;
			while (*key)
			{
				hash = ((hash << 5) + hash) + *key++;
			}

			break;
		}
		return hash;
	}
};

#endif // !NBHASHMAP_H
