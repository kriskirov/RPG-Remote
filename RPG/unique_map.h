#ifndef UNIQUE_MAP_H
#define UNIQUE_MAP_H
//#include "Action.h"
#include <map>
#include <cassert>

//A unique map is a map that has both: unique keys and unique values. A key cannot exists more than once. A value cannot exist more than once.
template <typename KEY, typename VALUE>
class unique_map{
public:
	unique_map() = default;
	unique_map(const unique_map& rhs) = default;
	unique_map& operator=(const unique_map& rhs) = default;

	void add(KEY key, VALUE value);
	bool getKey(VALUE value, KEY& foundResult);
	std::pair<KEY, VALUE> getPair(const KEY& key);
	bool isValidValue(VALUE value);
private:
	std::map<KEY, VALUE> mMapOfUniqueValues;
};

template <typename KEY, typename VALUE>
void unique_map<KEY, VALUE>::add(KEY key, VALUE value){
	std::map<KEY, VALUE>::iterator it = mMapOfUniqueValues.find(key);
	assert(it == mMapOfUniqueValues.end());//the user of the interface must not try to add the same value a second time
	bool noDuplicateValueFound = true;
	for (it = mMapOfUniqueValues.begin(); it != mMapOfUniqueValues.end(); ++it){
		if (it->second == value)
			noDuplicateValueFound = false;
	}
	assert(noDuplicateValueFound);
	mMapOfUniqueValues.insert(std::pair<KEY, VALUE>(key, value));
}

template <typename KEY, typename VALUE>
std::pair<KEY, VALUE> unique_map<KEY, VALUE>::getPair(const KEY& key){
	std::map<KEY,VALUE>::iterator iter;
	iter = mMapOfUniqueValues.find(key);
	if (iter != mMapOfUniqueValues.end()){
		return std::pair<KEY, VALUE>(*iter);
	}
	return std::pair<KEY, VALUE>(KEY(), VALUE());
}

template <typename KEY, typename VALUE>
bool unique_map<KEY, VALUE>::getKey(VALUE value, KEY& foundResult){
	std::map<KEY, VALUE>::iterator it;
	for (it = mMapOfUniqueValues.begin(); it != mMapOfUniqueValues.end(); ++it){
		if (it->second == value){
			foundResult = it->first;
			return true;
		}
	}
	foundResult = KEY();
	return false;
}

template <typename KEY, typename VALUE>
bool unique_map<KEY, VALUE>::isValidValue(VALUE value){
	std::map<KEY, VALUE>::iterator it;
	for (it = mMapOfUniqueValues.begin(); it != mMapOfUniqueValues.end(); ++it){
		if (it->second == value){
			return true;
		}
	}
	return false;
}
#endif