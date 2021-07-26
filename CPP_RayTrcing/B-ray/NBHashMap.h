#ifndef NBHASHMAP_H
#define NBHASHMAP_H
#include<string>

template<class Key, class Value>
//Hash½Úµã
struct hash_node
{
	Key _key = NULL;
	Value _value = NULL;

	hash_node(const Key& key, const Value& value) {
		_key = key;
		_value = value;
	}

	Value& readValue()const {
		return _value;
	}

	Key& readKey()const {
		return _key;
	}

};


//Hash±í
template <class Key, class Value>
class NBhash_map
{
public:
	NBhash_map() {};

	void insert(const hash_node& node) {
		int hash = node.readKey()();
		unsigned index = GetIndex(hash);

		if (hash_table[index] == NULL)
		{
			hash_table[index] = node;
			_count += 1;
		}
	};

	Value& find(const Key& key) {
		int hash = key();
		unsigned index = GetIndex(hash);
		hash_node node = hash_table[index];
		if (node !=NULL)
		{
			return node
		}
		
	};

private:
	unsigned _capacity = 1<<4;
	hash_node hash_table[16] = {NULL};
	unsigned _count = 0;
	float _loadFactor = 0.75f;

	unsigned GetIndex(const int& hash) {
		return hash&(_capacity - 1);
	}
};





#endif // !NBHASHMAP_H
