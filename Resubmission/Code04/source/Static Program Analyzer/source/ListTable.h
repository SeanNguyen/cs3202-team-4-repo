#pragma once
#include "Table.h"
#include <vector>
#include <algorithm>

using namespace std;

template <typename T> 
class ListTable : public Table {

private:
	vector <T> list;

public:
	ListTable(void) {}
	~ListTable(void) {}

	bool insert (T element) {
		list.push_back (element);
		return true;
	}

	vector <int> getIndexes (T value) {
		vector <int> result;
		for (size_t i = 0; i < list.size(); i++) {
			if (value == list.at(i))
				result.push_back(i);
		}
		return result;
	}

	T getValue (size_t index) {
		if (index < 0 || index >= list.size())
			return NULL;
		return list.at(index);
	}

	int getSize () {
		return list.size();
	}

	bool exist(T value) {
		return find (list.begin(), list.end(), value) != list.end();
	}
};