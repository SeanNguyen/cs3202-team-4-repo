#include "ResultTable.h"

ResultTable::ResultTable() {
	symbolSize = 0;
	size = 0;
}

ResultTable::~ResultTable() {
}

bool ResultTable::containsSymbol(string name) {
	for (int i=0; i<symbolSize; i++) {
		if (name==symbols[i]) return true;
	}
	return false;
}

bool ResultTable::containsSymbol(vector<string> names) {
	for (size_t i=0; i<names.size(); i++) {
		if (!containsSymbol(names[i])) return false; 
	}
	return true;
}

vector<string> ResultTable::getAllSymbols() {
	return symbols;
}

int ResultTable::getSymbolSize() { return symbolSize; }

int ResultTable::getSymbolIndex(string name) {
	for (int i=0; i<symbolSize; i++) {
		if (name==symbols[i]) return i;
	}
	return -1;
}

vector<int> ResultTable::getSymbolIndex(vector<string> names) {
	vector<int> results;

	for (size_t i=0; i<names.size(); i++) {
		int index = getSymbolIndex(names[i]);
		if (index==-1) {
			results.clear();
			break;
		}
		results.push_back(index);
	}
	return results;
}

string ResultTable::getSymbol(int index) {
	if (index<0 || index>=symbolSize) return "";
	return symbols[index];
}

void ResultTable::insertSymbol(vector<string> s) {
	for (unsigned i=0;i<s.size(); i++) {
		insertSymbol(s[i]);
	}
}

void ResultTable::insertSymbol(string s) {
	if (!containsSymbol(s)) {
		symbols.push_back(s);
		vector<int> new_cols;
		valCols.push_back(new_cols);
		symbolSize++;
	}
}

bool ResultTable::containsValRow(vector<int> r, bool correctness) {
	for (int i=0; i<size; i++) {
		vector<int> row = valRows[i];
		bool correct = correctRows[i];
		if (compareVector(row, r) && correct == correctness) return true;
	}
	return false;
}

int ResultTable::getSize() {	return size;	}

int ResultTable::getValRowIndex(vector<int> r) {
	for (int i=0; i<size; i++) {
		vector<int> row = valRows[i];
		if (compareVector(row, r)) return i;
	}
	return -1;
}

vector<int> ResultTable::getValRow(int index) {
	vector<int> result;
	if (index<0 || index>=size) return result;
	return valRows[index];
}

void ResultTable::insertValRow(vector<vector<int>> rows, bool correctness) {
	int size = rows.size();
	for (int i=0; i<size; i++) {
		insertValRow(rows[i], correctness);
	}
}

void ResultTable::insertValRow(vector<int> r, bool correctness) {
	if (!containsValRow(r, correctness)) { 
		valRows.push_back(r);
		for (size_t i=0; i<symbolSize; i++) {
			if (i<r.size()) { 
				valCols[i].push_back(r[i]);
			} else {
				valCols[i].push_back(-1);
			}
		}
		correctRows.push_back(correctness);
		size++;
	}
}

void ResultTable::deleleInvalidRows() {
	for (int i=0; i<size; i++) {
		if (!correctRows[i]) {
			valRows.erase(valRows.begin()+i);
			correctRows.erase(correctRows.begin()+i);
			i--; size--;
		}
		/*int rowSize = valRows[i].size();
		if (rowSize!= symbolSize) {
			valRows.erase(valRows.begin()+i);
			--i; --size;
		} else {
			if (find(valRows[i].begin(), valRows[i].end(), -1)!=valRows[i].end()) {
				valRows.erase(valRows.begin()+i);
				--i; --size;
			}
		}*/
	}
}

// pre-condition: s.size()!=0 && this -> symbols contains s
ResultTable * ResultTable::extractData(vector<string> s) {
	ResultTable * t = new ResultTable();
	if (s.size()==0 || !containsVector(symbols, s)) return t;
	t -> insertSymbol(s);

	vector<int> indexes;
	for (unsigned i=0; i<s.size(); i++) {
		indexes.push_back(getSymbolIndex(s[i]));
	}

	for (int i=0; i<size; i++) {
		vector<int> row = valRows[i];
		vector<int> r;
		for (unsigned j=0; j<indexes.size(); j++) {
			int index = indexes[j];
			r.push_back(row[index]);
		}
		t ->insertValRow(r, false);
	}

	return t;
}



bool ResultTable::compareVector(vector<int> a, vector<int> b) {
	int size_a = a.size(); int size_b = b.size();
	int i=0;
	while(i<size_a && i<size_b) {
		if (a[i]!=b[i]) return false;
		i++;
	}
	while (i<size_a) {
		if (a[i]!=-1) return false;
		i++;
	}
	while (i<size_b) {
		if (b[i]!=-1) return false;
		i++;
	}
	return true;
}

bool ResultTable::containsVector(vector<string> a, vector<string> b) {
	int size_a = a.size(); int size_b = b.size();
	if (size_a<size_b) return false;
	for (int i=0; i<size_b; i++) {
		if (!containsSymbol(b[i])) return false;
	}
	return true;
}

void ResultTable::printTable() {
	string symbolLine = "";
	for (int i=0; i<symbolSize; i++) {
		symbolLine += symbols[i] + " || " ;  
	}
	cout << symbolLine <<endl;
	for (int i=0; i<size; i++) {
		vector<int> value = valRows[i];
		for (size_t j=0; j<value.size(); j++) {
			cout << value[j] << "    ";
		}
		cout << endl;
	}
	cout <<endl;
}