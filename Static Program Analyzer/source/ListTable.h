#pragma once
#include "Table.h"
#include <vector>

using namespace std;

template <typename T> 
class ListTable : public Table {

private:
	vector <T> list;

public:
	ListTable(void) {}
	~ListTable(void) {}

	void insert (T element) {
		list.push_back (element);
	}

	vector <int> getIndexes (T value) {
		vector <int> result;
		for (int i = 0; i < list.size(); i++) {
			if (value == list.at(i))
				result.push_back(i);
		}
		return result;
	}

	T getValue (int index) {
		if (index < 0 || index >= list.size())
			return NULL;
		return list.at(index);
	}

	int getSize () {
		return list.size();
	}
};