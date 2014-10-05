#pragma once
#include "Table.h"
#include <vector>

using namespace std;

template <typename T> 
class ListTable : public Table {

private:
	vector <T> list;

public:
	ListTable(void);
	~ListTable(void);

	template<typename T>
	int insert (T element) {
		list.push_back (element);
		return list.size();
	}

	template<typename T>
	int getIndexes (T value) {
		vector<int> indexes;

		for(size_t i=0; i < statTable.size(); i++) {
			if(statTable.at(i) == name)
				indexes.push_back(i);
		}
		return indexes ;
	}

	template<typename T>
	T getValue (int index) {
		if (index < 0 || index > list.size())
			return NULL;
		return list.at(index);
	}

	template<typename T>
	int getSize () {
		return list.size();
	}
};

