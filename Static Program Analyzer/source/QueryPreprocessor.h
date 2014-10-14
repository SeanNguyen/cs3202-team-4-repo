#ifndef QueryPreprocessor_h
#define QueryPreprocessor_h

#include "QueryRepresentator.h"
#include "TNode.h"
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
	void preprocessDeclaration(SymbolTable& table, string declaration, vector<string>& errors);
	void preprocessQueryPart(QueryTree& tree, SymbolTable table, string queryPart, vector<string>& errors);
	TNode * preprocessResultNode(vector<string> list, SymbolTable table, vector<string> & errors, int i);
	TNode * preprocessSuchThatCondition(vector<string> suchthat, SymbolTable table, vector<string>& errors);
	TNode * preprocessPatternCondition(vector<string> pattern, SymbolTable table, vector<string>& errors);
	TNode * preprocessAssignPattern(string name, vector<string> pattern, SymbolTable table, vector<string>& errors);
	TNode * preprocessWhilePattern(string name, vector<string> pattern, SymbolTable table, vector<string>& errors);
	TNode * preprocessIfPattern(string name, vector<string> pattern, SymbolTable table, vector<string>& errors);
	TNode * preprocessExpressionNode(vector<string> pattern, vector<string>& errors);
	TNode * preprocessWithCondition(vector<string> list, SymbolTable table, vector<string>& errors, int i);
	TNode * preprocessTupleResult(vector<string> list, SymbolTable table, vector<string>& errors);

	vector<string> breakStringIntoWords(string str);
	unsigned int findFirstElement(vector<string> list, unsigned i, string element);
	unsigned int findLastElement(vector<string> list, unsigned i, string element);
	bool isNumber(string str);
	vector<string> subList(vector<string> list, int i, int j);
	int getLastIndexOfTokenNotInsideBracket(vector<string> list, string token);
};

#endif