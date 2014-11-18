#include "ResultManager.h"
#include "..\AutoTester\source\AbstractWrapper.h"

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
	table->insertSymbol(symbols);
	for (int i=0; i<size; i++) {
		ResultTable * t = tables[i];
		vector<string> sub_symbols = extractSymbols(t, symbols);
		if (sub_symbols.size()!=0) {
			ResultTable * extract_table = t -> extractData(sub_symbols);
			table = mergeTables(table, extract_table);
		}
	}
	return table;
}

ResultTable * ResultManager::mergeTables(ResultTable * t1, ResultTable * t2) {
	if (t1->getSymbolSize()==0) return t2;

	//cout << "CHECKPOINT 000 " << t1->getSymbolSize() << " " << t2->getSymbolSize() <<endl;
	//cout << "CHECKPOINT 001 " << t1->getSize() << " " << t2->getSize() <<endl;
	vector<string> shared_symbols = getSharedSymbols(t1, t2);
	vector<int> shared_index1 = t1->getSymbolIndex(shared_symbols);
	vector<int> shared_index2 = t2->getSymbolIndex(shared_symbols);

	vector<string> merged_symbols = mergeSymbols(t1->getAllSymbols(), t2->getAllSymbols());

	ResultTable * t = new ResultTable();
	t->insertSymbol(merged_symbols);

	if (t1->getSize()==0) {
		vector<int> t1_row (t1->getSymbolSize(), -1);
		for (int j=0; j<t2->getSize(); j++) {
			vector<int> t2_row = t2->getValRow(j);
			vector<int> merged_row = mergeRow(t1_row, t2_row, shared_index1, shared_index2);
			if (!merged_row.empty())
				t->insertValRow(merged_row, false);
		}
	} else if (t2->getSize()==0) {
		vector<int> t2_row (t2->getSymbolSize(), -1);
		for (int i=0; i<t1->getSize(); i++) {
			vector<int> t1_row = t1->getValRow(i);
			vector<int> merged_row = mergeRow(t1_row, t2_row, shared_index1, shared_index2);
			if (!merged_row.empty())
				t->insertValRow(merged_row, false);
		}
	} else {
		for (int i=0; i<t1->getSize(); i++) {
			vector<int> t1_row = t1->getValRow(i);
			for (int j=0; j<t2->getSize(); j++) {
				vector<int> t2_row = t2->getValRow(j);
				vector<int> merged_row = mergeRow(t1_row, t2_row, shared_index1, shared_index2);
				if (!merged_row.empty())
					t->insertValRow(merged_row, false);
			}
		}
	}

	//cout << "CHECKPOINT 002 " << t->getSize() <<endl; 
	return t;
}

// version 2 of insert:
// bfr inserting a table, merge every possible existed tables to it
void ResultManager::insertTable(ResultTable * table) {
	vector<string> symbols = table->getAllSymbols();
	for (int i=0; i<size; i++) {
		if (hasSharedSymbols(table, tables[i])) {
			//tables[i] = updateTable(tables[i], table);
			table = mergeTables(table, tables[i]);
			tables.erase(tables.begin()+i);
			--i; --size;
		}
	}
	tables.push_back(table);
	size++;
}

ResultTable * ResultManager::updateTable(ResultTable * t, ResultTable * table) {
	ResultTable * result = new ResultTable();
	result->insertSymbol(table->getAllSymbols());
	vector<string> shared_symbols = getSharedSymbols(t, table);
	vector<int> shared_index1 = table->getSymbolIndex(shared_symbols);
	vector<int> shared_index2 = t->getSymbolIndex(shared_symbols);
	for (int i=0; i<table->getSize(); i++) {
		vector <int> row = table->getValRow(i);
		for (int j=0; j<t->getSize(); j++) {
			vector<int> r = t->getValRow(j);
			vector<int> merged_r = mergeRow(row, r, shared_index1, shared_index2);
			if (merged_r.size()!=0) {
				result->insertValRow(row, true);
			}
		}
	}
	return result;
}

vector<string> ResultManager::extractSymbols(ResultTable * t, vector<string> symbols) {
	vector<string> s = t->getAllSymbols();
	vector<string> result;
	for (unsigned i=0; i<symbols.size(); i++) {
		string symbol = symbols[i];
		if (find(s.begin(), s.end(), symbol) != s.end() &&
			find(result.begin(), result.end(), symbol)== result.end()) {
			result.push_back(symbol);
		}
	}

	return result;
}
 
bool ResultManager::hasSharedSymbols(ResultTable * t1, ResultTable * t2) {
	vector<string> shared_symbols = getSharedSymbols(t1, t2);
	if (shared_symbols.empty()) return false;
	return true;
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

vector<int> ResultManager::mergeRow(vector<int> r1, vector<int> r2, vector<int> shared_id1, vector<int> shared_id2) {
	vector<int> result = r1;

	for (size_t i=0; i<shared_id1.size(); i++) {
		int i1 = shared_id1[i]; int i2 = shared_id2[i];
		if (r1[i1]!=r2[i2] && r1[i1]!=-1 && r2[i2]!=-1) {
			result.clear();
			return result;
		}
		if (r1[i1]==-1 && r2[i2]!=-1) {
			result[i1]=r2[i2];
		}
		if (AbstractWrapper::GlobalStop) {
			return result;
		}
	}

	for (size_t i=0; i<r2.size(); i++) {
		if (find(shared_id2.begin(), shared_id2.end(), i)==shared_id2.end()) {
			result.push_back(r2[i]);
		}
	}
	return result;
}