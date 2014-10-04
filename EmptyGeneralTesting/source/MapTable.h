#pragma once

#include <map>
#include <vector>
#include "Table.h"

using namespace std;

template <typename T>
class MapTable : public Table {

private:
	map <T, vector<T>> primaryMap;
	map <T, vector <T>> reversedMap;
	map <T, bool> isProcessed;
	bool isInMiddleOfSearch = false;
public:
	MapTable(void);
	~MapTable(void);

	int insert (T key, T value);
	bool isMapped (T key, T value);
	bool isMappedStar (T key, T value);
	vector<T> getValues (T key);
	vector<T> getValuesStar (T key);
	vector <T> getKeys (T value);
	vector <T> getKeysStar (T value);
};

template <typename T>
void MapTable <T>::insert(T key, T value) {
	if (isMapped(key, value))
		return;
	if (primaryMap[key] == null)
		primaryMap[key] = vector <T>();
	if (reversedMap[value] == null)
		reversedMap[value] = vector <T>();

	primaryMap[key].push_back(value);
	reversedMap[value].push_back(key);
}

template <typename T>
bool MapTable <T>::isMapped (T key, T value) {
	vector <T> values = primaryMap[key];
	return find(values.begin(), values.end(), stmt2) != values.end();
}

template <typename T>
bool MapTable <T>::isMappedStar (T key, T value) {
	if (!isInMiddleOfSearch) {
		isProcessed.clear();
		isInMiddleOfSearch = true;
	}

	if (isProcessed.count(key) != 0 || isProcessed[key] == true)
		return false;
	else
		isProcessed[key] = true;

	vector <int> values = primaryMap[key];
	if (isNext(stmt1, stmt2)) {
		isInMiddleOfSearch = false;
		return true;
	}
	//apply depth first search here
	for (size_t i = 0; i < this->mapNext[stmt1].size(); i++) {
		if (isNextStarInternal(nextStmts[i], stmt2)) {
			isInMiddleOfSearch = false;
			return true;
		}
	}
	return false;
}

template <typename T>
vector<T> MapTable <T>::getValues (T key) {
	return primaryMap[key];
}

template <typename T>
vector<T> MapTable <T>::getValuesStar (T key) {
	
}