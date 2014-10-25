#pragma once

#include <algorithm>
#include "SymbolTable.h"
#include "QueryTree.h"

class QueryOptimizer {
public:
	static void optimizeQuery(SymbolTable & table, QueryTree & tree, vector<int> & count);
	static void sortTable(SymbolTable & table, vector<int> & count);
	static void sortTree(QueryTree & tree, SymbolTable & table);
private:
	static SymbolTable sortTable(SymbolTable table, vector<int> & count, int start, int end);
	static SymbolTable mergeTable(SymbolTable t1, SymbolTable t2, vector<int> & count, int start, int mid, int end);

	static void rankNode(TNode * node, SymbolTable & table);
	static int rankNodeType(Symbol type);
	static int rankChildOccurences(TNode * node, SymbolTable & table);

	static const int EXPRESSION_RANK = 10;
	static const int UNDEFINE_RANK = 1000;
};