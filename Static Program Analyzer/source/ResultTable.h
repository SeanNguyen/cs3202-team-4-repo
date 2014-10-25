#pragma once

#include <vector>
#include "SyntaxHelper.h"

class ResultTable {
public:
	ResultTable();
	~ResultTable();
	int getSymbolIndex(string name);
	string getSymbol(int index);
	bool containsSymbol(string name);

	vector<int> getValueRow(int index);
private:
	// sth to store the names of symbols
	// sth to store rows of values of above symbols
	// sth more to rmb frquently used data (size, symbol#)
};