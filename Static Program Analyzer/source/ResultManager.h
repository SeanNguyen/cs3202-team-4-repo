#pragma once

#include "ResultTable.h"

class ResultManager {
public:
	ResultManager();
	
	bool containsTable(vector<string> symbols);
	//ResultTable * getTable(vector<string> symbols);
	ResultTable * getTable(int index);
	ResultTable * extractTable(vector<string> symbols);
	ResultTable * mergeTables(ResultTable * t1, ResultTable * t2);
	
	void insertTable(ResultTable * table);
private:
	vector<ResultTable *> tables;
	int size;

	vector<string> extractSymbols(ResultTable * t, vector<string> s);
};