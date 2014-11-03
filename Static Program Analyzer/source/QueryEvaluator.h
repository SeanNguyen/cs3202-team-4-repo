#ifndef QueryEvaluator_h
#define QUeryEvaluator_h

#include "..\AutoTester\source\AbstractWrapper.h"
#include "QueryRepresentator.h"
#include "ResultManager.h"
#include "PKB.h"

#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;

const int ARG1 = 0;
const int ARG2 = 1;

class QueryEvaluator {
public:
	void Evaluate();
	vector<string> getResult(int index);
	vector<vector<string>> getAllResult();
private:
	SymbolTable table;
	QueryTree tree;
	bool checkValid;
	vector<vector<string>> resultList;

	void evaluateQuery();
	bool evaluateClause(TNode * clause_node, ResultTable * temp_result);
	bool evaluateClause(TNode * clause_node, vector<int> row, vector<vector<int>> * new_rows);
	bool evaluateSTClause(TNode * ST_node, vector<int> row, vector<vector<int>> * new_rows);
	bool evaluatePTClause(TNode * PT_node, vector<int> row, vector<vector<int>> * new_rows);
	bool evaluateWClause(TNode * W_node, vector<int> row, vector<vector<int>> * new_rows);

	bool isRelation(Symbol relation, int arg1, int arg2);
	vector<int> getArgInRelation(Symbol relation, int arg, int arg_unknown);

	vector<string> extractResult();
	vector<string> extractResult(TNode * result_node, ResultManager * rm, bool is_satisfied);

	vector<string> getSymbolsUsedBy(TNode * node);
	int getIndexOfConst(TNode * const_node, Symbol relation, int argIndex);
	bool isNumber(string s);
	void fillResultTable(ResultTable * t);
	void fillResultList(TNode * result_node, ResultTable * t, vector<string> * result);
	string fillResult(TNode * result_node, vector<int> values);
	string fillResult(TNode * node, int value);
	vector<int> getAllPKBValues(string symbol_name);
	vector<string> getUnknownSymbols(ResultTable * table);
	string getAttrValue(TNode * node, int index);
	vector<int> getAttrIndex(TNode * node, string attr_value);
};

#endif