#ifndef QueryRepresentator_h
#define QueryRepresentator_h

#include "QueryTree.h"
#include "SymbolTable.h"

#include <string>
#include <vector>

using namespace std;

class QueryRepresentator {
public:
	static SymbolTable *getSymbolTable(int index);
	static QueryTree *getQueryTree(int index);
	static bool getQueryValidity(int index);
	static int getSize();
	static int addQuery(SymbolTable table, QueryTree tree, bool isQueryValid);
	static void reset();
private:
	static vector<SymbolTable> tables;
	static vector<QueryTree> trees;
	static vector<int> queryValidities;
	static int size;
};

#endif
