#include "ResultManager.h"

ResultManager::ResultManager() {
	size = 0;
}

bool ResultManager::containsTable(vector<string> symbols) {
	for (int i=0; i<size; i++) {
		ResultTable * t = tables[i];
		if (t->containsSymbol(symbols)) return true;
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

	vector<string> shared_symbols = getSharedSymbols(t1, t2);
	vector<int> shared_index2 = t2->getSymbolIndex(shared_symbols);

	vector<string> merged_symbols = mergeSymbols(t1->getAllSymbols(), t2->getAllSymbols());

	ResultTable * t = new ResultTable();
	t->insertSymbol(merged_symbols);
	for (int i=0; i<t1->getSize(); i++) {
		vector<int> t1_row = t1->getValRow(i);
		for (int j=0; j<t2->getSize(); j++) {
			vector<int> t2_row = t2->getValRow(j);
			vector<int> merged_row = mergeRow(t1_row, t2_row, shared_index2);
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

vector<string> ResultManager::getSharedSymbols(ResultTable * t1, ResultTable * t2) {
	vector<string> results;

	int size1 = t1->getSymbolSize();
	for (int i=0; i<size1; i++) {
		string symbol = t1->getSymbol(i);
		if (t2->containsSymbol(symbol)) 
			results.push_back(symbol);
	}

	return results;
}

vector<string> ResultManager::mergeSymbols(vector<string> s1, vector<string> s2) {
	vector<string> result = s1;

	for (size_t i=0; i<s2.size(); i++) {
		if (find(result.begin(), result.end(), s2[i])==result.end()) 
			result.push_back(s2[i]);
	}

	return result;
}

vector<int> ResultManager::mergeRow(vector<int> r1, vector<int> r2, vector<int> shared_id2) {
	vector<int> result = r1;

	cout << "CHECKPOINT 001" <<endl;
	for (size_t i=0; r2.size(); i++) {
		if (find(shared_id2.begin(), shared_id2.end(), i)==shared_id2.end())
			result.push_back(r2[i]);
	}
	cout << "CHECKPOINT 002" <<endl;
	return result;
}