#ifndef QueryPreprocessor_h
#define QueryPreprocessor_h

#include "QueryRepresentator.h"
#include "QueryOptimizer.h"
#include "../AutoTester/source/AbstractWrapper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "SyntaxHelper.h"

using namespace std;

class QueryPreprocessor {
public:
	QueryPreprocessor();
	QueryPreprocessor(string directory);
	void Preprocess();
	void Preprocess(string query);
	// testing methods
	void printFileData();
private:
	vector<vector<string>> fileData;
	string fileDirectory;

	void readFileData();
	void preprocessFileData();
	void preprocessQuery(vector<string> query, int index);
	void preprocessDeclaration(string declaration);
	void preprocessQueryPart(string queryPart);
	TNode * preprocessResultNode(vector<string> list, int i);
	TNode * preprocessSuchThatCondition(vector<string> suchthat);
	TNode * preprocessPatternCondition(vector<string> pattern);
	TNode * preprocessWithCondition(vector<string> list, int i);

	TNode * preprocessAssignPattern(string name, vector<string> pattern);
	TNode * preprocessWhilePattern(string name, vector<string> pattern);
	TNode * preprocessIfPattern(string name, vector<string> pattern);
	TNode * preprocessExpressionNode(vector<string> pattern);
	TNode * preprocessTupleResult(vector<string> list);
	
	TNode * preprocessEntRef(vector<string> list);
	TNode * preprocessStmtRef(vector<string> list);
	TNode * preprocessLineRef(vector<string> list);
	TNode * preprocessVarRef(vector<string> list);
	TNode * preprocessAttrRef(vector<string> list);

	void countSymbol(string str);
	vector<string> breakStringIntoWords(string str);
	unsigned int findFirstElement(vector<string> list, unsigned i, string element);
	unsigned int findLastElement(vector<string> list, unsigned i, string element);
	vector<string> subList(vector<string> list, int i, int j);
	int getLastIndexOfTokenNotInsideBracket(vector<string> list, string token);

	// temporary storing data before pass to QueryRepresentator
	SymbolTable table;
	QueryTree tree;
	vector<string> errors;
	vector<int> symbolCount;
};

#endif