#include "ResultManager.h"

ResultManager::ResultManager() {
	size = 0;
}

bool ResultManager::containsTable(vector<string> symbols) {
	for (int i=0; i<size; i++) {
		ResultTable * t = tables[i];
		if (true) return true;
	}
	return false;
}

int ResultManager::getSize() {
	return size;
}

ResultTable * ResultManager::getTable(int index) {
	if (index<0 || index>=size) return new ResultTable();
	return tables[index];
}

// pre-condition: no symbol is saved in more than 1 table
ResultTable * ResultManager::extractTable(vector<string> symbols) {
	ResultTable * table = new ResultTable();
	for (int i=0; i<size; i++) {
		ResultTable * t = tables[i];
		vector<string> sub_symbols = extractSymbols(t, symbols);
		ResultTable * extract_table = t -> extractData(sub_symbols);
		mergeTables(table, extract_table);
	}
	return table;
}

ResultTable * ResultManager::mergeTables(ResultTable * t1, ResultTable * t2) {
	if (t1->getSymbolSize()==0) return t2;

	ResultTable * t = new ResultTable();
	for (int i=0; i<t1 ->getSymbolSize(); i++) {
		vector<int> t1_row = t1->getValRow(i);
		for (int j=0; j<t2->getSymbolSize(); j++) {
			vector<int> t2_row = t2->getValRow(j);
		}
	}

	return t;
}

void ResultManager::insertTable(ResultTable * table) {
	vector<string> symbols = table->getAllSymbols();
	if (!containsTable(symbols)) {
		tables.push_back(table);
		size++;
	}
}

vector<string> ResultManager::extractSymbols(ResultTable * t, vector<string> symbols) {
	vector<string> s = t->getAllSymbols();
	vector<string> result;
	for (unsigned i=0; i<symbols.size(); i++) {
		string symbol = symbols[i];
		if (find(s.begin(), s.end(), symbol) != s.end()) {
			result.push_back(symbol);
		}
	}

	return result;
}