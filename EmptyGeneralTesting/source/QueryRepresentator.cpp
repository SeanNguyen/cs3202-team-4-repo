
#include "QueryRepresentator.h"

/* INTIALIZATION */

// Initialize all static variables
vector<SymbolTable> QueryRepresentator::tables;
vector<QueryTree> QueryRepresentator::trees;
vector<int> QueryRepresentator::queryValidities;
int QueryRepresentator::size = 0;


/* PUBLIC METHODS */

// Description: this method is to add new query into QueryRepresentator
int QueryRepresentator::addQuery(SymbolTable table, QueryTree tree, bool isQueryValid) {
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
	return size;
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