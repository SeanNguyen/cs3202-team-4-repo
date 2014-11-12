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
	vector<int> getSymbolIndex(vector<string> names);
	vector<string> getAllSymbols();
	string getSymbol(int index);
	bool containsSymbol(string name);
	bool containsSymbol(vector<string> names);
	void insertSymbol(vector<string> s);
	void insertSymbol(string s);

	bool containsValRow(vector<int> row, bool correctness);
	int getSize();
	int getValRowIndex(vector<int> row);
	vector<int> getValRow(int index);
	void insertValRow(vector<vector<int>> r, bool correctness);
	void insertValRow(vector<int> r, bool correctness);
	void deleleInvalidRows();

	ResultTable * extractData(vector<string> s);

	void printTable();
private:
	// sth to store the names of symbols
	vector<string> symbols;
	// sth to store rows of values of above symbols
	vector<vector<int>> valRows;
	vector<vector<int>> valCols;
	vector<bool> correctRows;
	// sth more to rmb frquently used data (size, symbol#)
	int size;
	int symbolSize;


	bool compareVector(vector<int> a, vector<int> b);
	bool containsVector(vector<string> a, vector<string> b);
};