
#include "QueryRepresentator.h"

/* INTIALIZATION */

// Initialize all static variables
vector<SymbolTable> QueryRepresentator::tables;
vector<QueryTree> QueryRepresentator::trees;
vector<int> QueryRepresentator::queryValidities;
int QueryRepresentator::size = 0;


/* PUBLIC METHODS */

// Description: this method is to add new query into QueryRepresentator
int QueryRepresentator::addQuery(SymbolTable &table, QueryTree &tree, bool isQueryValid) {
	tables.push_back(table);
	trees.push_back(tree);
	if (isQueryValid) {
		queryValidities.push_back(1);
	} else {
		queryValidities.push_back(0);
	}
	size++;
	return size;
}

// Description: this method is to get number of queries
int QueryRepresentator::getSize() {
	return trees.size();
}

// Description: this method is to get SymbolTable of query at index "index"
SymbolTable QueryRepresentator::getSymbolTable(int index) {
	if (index<0 || index >=size) {
		SymbolTable table;
		return table;
	}
	if (size==0) {
		SymbolTable table;
		return table;
	}
	return tables[index];
}

// Description: this method is to get QueryTree of query at index "index"
QueryTree QueryRepresentator::getQueryTree(int index) {
	if (index<0 || index >=size) {
		QueryTree tree;
		return tree;
	}
	if (size==0) {
		QueryTree tree;
		return tree;
	}
	return trees[index];
}

// Description: this method is to check query's validity at index "index"
bool QueryRepresentator::getQueryValidity(int index) {
	if (index<0 || index >=size) {
		return false;
	}
	if (size==0) {
		return false;
	}
	return (queryValidities[index]==1)? true : false;
}
// Description: this method is to reset all data in QueryRepresentator
// it only needs to be called by QueryPreprocessor 
void QueryRepresentator::reset() {
	tables.clear();
	trees.clear();
	queryValidities.clear();
	size = 0;
	return;
}

void QueryRepresentator::sortTable(int index, vector<string> symbolRanks) {
	SymbolTable table = getSymbolTable(index);

	// merge sort
	int size = table.getSize();
	SymbolTable new_table = sortTable(table, symbolRanks, 0, size-1);
	// replace old table with new table
	tables[index] = new_table;
}

SymbolTable QueryRepresentator::sortTable(SymbolTable table, vector<string> ranks, int start, int end) {
	if (start==end) {
		SymbolTable new_table;
		string type = table.getType(start);
		string name = table.getName(start);
		new_table.setSymbol(type, name);
		return new_table;
	}

	int mid = (start+end)/2;
	SymbolTable table1 = sortTable(table, ranks, start, mid);
	SymbolTable table2 = sortTable(table, ranks, mid+1, end);

	SymbolTable new_table = mergeTables(table1, table2);

	return new_table;
}

SymbolTable QueryRepresentator::mergeTables(SymbolTable t1, SymbolTable t2) {
	int size1 = t1.getSize(); int size2 = t2.getSize();
	while (size1>0 || size2>0) {
	}
	return t1;
}