#include <map>
#include <vector>
#include <algorithm>
#include "Table.h"

using namespace std;

template <typename T>
class MapTable : public Table {

private:
	map <T, vector<T>> keyValueMap;
	map <T, vector<T>> reversedKeyValueMap;
	map <T, vector<T>> keyValueStarMap;
	map <T, vector<T>> reversedKeyValueStarMap;

	map <T, bool> processedFlags;

public:
	MapTable(void) {}
	~MapTable(void) {}

	bool insert (T key, T value) {
		if (isMapped(key, value))
			return true;
		keyValueMap[key].push_back(value);
		return true;
	}

	bool isMapped (T key, T value) {
		vector <T> values = keyValueMap[key];
		return find(values.begin(), values.end(), value) != values.end();
	}

	bool isMappedStar (T key, T value, bool isStartingPoint) {
		if (isStartingPoint)
			processedFlags.clear();

		if (processedFlags.count(key) != 0 && processedFlags[key] == true)
			return false;
		else
			processedFlags[key] = true;

		if (isMapped(key, value)) {
			return true;
		}

		vector <T> values = keyValueMap[key];
		//apply depth first search here
		for (size_t i = 0; i < values.size(); i++) {
			if (isMappedStar(values[i], value, false)) {
				return true;
			}
		}
		return false;
	}

	vector<T> getValues (T key) {
		return keyValueMap[key];
	}

	vector<T> getValuesStar (T key) {
		return keyValueStarMap[key];
	}

	vector<T> getIndexes (T value) {
		return reversedKeyValueMap[value];
	}

	vector<T> getIndexesStar (T value) {
		return reversedKeyValueStarMap[value];
	}

	void preCalculateStarTable() {
		for (map<T, vector<T>>::iterator it = keyValueMap.begin(); it != keyValueMap.end(); ++it) {
			T key = it->first;
			vector<T> starResults = calculateValuesStar(key, true);
			keyValueStarMap[key] = starResults;
		}

		for (map<T, vector<T>>::iterator it = reversedKeyValueMap.begin(); it != reversedKeyValueMap.end(); ++it) {
			T value = it->first;
			vector<T> starResults = calculateIndexesStar(value, true);
			reversedKeyValueStarMap[value] = starResults;
		}
	}

	int getSize() {
		return keyValueMap.size();
	}

private:
	vector<T> calculateValuesStar(T key, bool isStartingPoint) {
		if (isStartingPoint)
			processedFlags.clear();

		vector <T> results;
		if (processedFlags.count(key) != 0 && processedFlags[key] == true) {
			return results;
		} else if (!isStartingPoint) {
			results.push_back(key);
			processedFlags[key] = true;
		}

		vector <T> values = keyValueMap[key];
		//apply depth first search here
		for (size_t i = 0; i < values.size(); i++) {
			vector <T> tempList = calculateValuesStar(values.at(i), false);
			results.insert(results.end(), tempList.begin(), tempList.end());
		}
		return results;
	}

	vector<T> calculateIndexesStar(T value, bool isStartingPoint) {
		if (isStartingPoint)
			processedFlags.clear();

		vector <T> results;
		if (processedFlags.count(value) != 0 && processedFlags[value] == true) {
			return results;
		} else if (!isStartingPoint) {
			results.push_back(value);
			processedFlags[value] = true;
		}

		vector <T> values = keyValueMap[value];
		//apply depth first search here
		for (size_t i = 0; i < values.size(); i++) {
			vector <T> tempList = calculateIndexesStar(values.at(i), false);
			results.insert(results.end(), tempList.begin(), tempList.end());
		}
		return results;
	}
};