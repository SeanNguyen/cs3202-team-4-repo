#pragma once

#include "ResultTable.h"

class ResultManager {
public:
	ResultManager();
	
	bool containsTable(vector<string> symbols);
	int getSize();
	//ResultTable * getTable(vector<string> symbols);
	ResultTable * getTable(int index);
	ResultTable * extractTable(vector<string> symbols);
	ResultTable * mergeTables(ResultTable * t1, ResultTable * t2);
	
	void insertTable(ResultTable * table);
private:
	vector<ResultTable *> tables;
	int size;

	vector<string> extractSymbols(ResultTable * t, vector<string> s);
	bool hasSharedSymbols(ResultTable * t1, ResultTable * t2);
	vector<string> getSharedSymbols(ResultTable * t1, ResultTable * t2);
	vector<string> mergeSymbols(vector<string> s1, vector<string> s2);
	vector<int> mergeRow(vector<int> r1, vector<int> r2, vector<int> shared_id1, vector<int> shared_id2);
};