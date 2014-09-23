#ifndef QueryEvaluator_h
#define QUeryEvaluator_h

#include "..\AutoTester\source\AbstractWrapper.h"
#include "QueryRepresentator.h"
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
	vector<vector<string>> resultList;
	SymbolTable table;
	QueryTree tree;
	bool checkValid;

	void evaluateQuery(); 
	void findResult(vector<string> values, vector<string>& result);
	void checkQueryCondition(int childIndex, vector<string> values, vector<string>& result, bool check);
	void checkSuchThatCondition(TNode node, vector<string> values, vector<string>& result, bool check, int childIndex);
	void checkPatternCondition(TNode node, vector<string> values, vector<string>& result, bool check, int childIndex);
	void checkWithCondition(TNode node, vector<string> values, vector<string>& result, bool check, int childIndex);
	void handleRelationNode(TNode & relationNode, vector<string> values, vector<string> & result, bool check, int childIndex);
	void handlePatternLeftHand(string stmt, TNode * leftNode, vector<string> & values, bool & check);
	void handlePatternRightHand(string stmt, TNode * rightNode, vector<string>& values, bool & check);
	
	vector<string> getArgumentValueInRelation(Symbol Relation, string arg1Value, Symbol arg1Type, string arg2Value, Symbol arg2Type, int argIndex);

	bool isRelation(Symbol relation, string arg1Value, string arg2Value);
	string getStoredValue(vector<string> values, string argName);

	vector<string> getAllArgValues(Symbol type);
	void updateResultList(vector<string> values, vector<string>& result);
	bool isResult(string val, vector<string> result);
	bool isDeclaredType(string val, string name, string type);
	vector<string> removeInvalidValues(vector<string> list, Symbol type);

	// unused methods
	bool isQueryConditionsSatisfied(vector<string> values);
	bool isSuchThatConditionSatisfied(vector<string> values, TNode node);
	bool isPatternConditionSatisfied(vector<string> values, TNode node);
	string getResultAfterEvaluation(vector<string> values);
	void addNewResult(vector<string>& resultList, string result);

	string intToString(int num);
	bool isNumber(string str);
	void printSymbolValues(vector <string> symbolValues);
};

#endif