#pragma once

#include <vector>
#include <algorithm>
#include "SyntaxHelper.h"
#include <iostream>

class ResultTable {
public:
	ResultTable();
	~ResultTable();
	int getSymbolSize();
	int getSymbolIndex(string name);
	vector<string> getAllSymbols();
	string getSymbol(int index);
	bool containsSymbol(string name);
	void insertSymbol(vector<string> s);
	void insertSymbol(string s);

	bool containsValRow(vector<string> row);
	int getSize();
	int getValRowIndex(vector<string> row);
	vector<string> getValRow(int index);
	void insertValRow(vector<vector<string>> r);
	void insertValRow(vector<string> r);
	void deleleInvalidRows();

	ResultTable * extractData(vector<string> s);
private:
	// sth to store the names of symbols
	vector<string> symbols;
	// sth to store rows of values of above symbols
	vector<vector<string>> valRows;
	vector<vector<string>> valCols;
	// sth more to rmb frquently used data (size, symbol#)
	int size;
	int symbolSize;


	bool compareVector(vector<string> a, vector<string> b);
	bool containsVector(vector<string> a, vector<string> b);
};