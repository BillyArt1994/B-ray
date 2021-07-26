#ifndef NBHASHMAP_H
#define NBHASHMAP_H

//Hash±í
template <class Key, class Value>
class NBhash_map
{
public:

private:
	pair<Key, Value>[17] = {NULL};
	unsigned _size = 0;
};

#endif // !NBHASHMAP_H
