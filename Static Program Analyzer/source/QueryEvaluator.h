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

const int ARG1_UNKNOWN = 0;
const int ARG2_UNKNOWN = 1;

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
	bool evaluateClause(TNode * clause_node, vector<string> row, vector<vector<string>> * new_rows);
	bool evaluateSTClause(TNode * ST_node, vector<string> row, vector<vector<string>> * new_rows);
	bool evaluatePTClause(TNode * PT_node, vector<string> row, vector<vector<string>> * new_rows);
	bool evaluateWClause(TNode * W_node, vector<string> row, vector<vector<string>> * new_rows);

	vector<string> extractResult();
	vector<string> extractResult(TNode * result_node, ResultManager * rm, bool is_satisfied);

	vector<string> getSymbolsUsedBy(TNode * node);
};

#endif