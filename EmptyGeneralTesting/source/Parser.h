#pragma once
#include "PKB.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


class Parser
{

//attributes
private:
	//data
	vector<string> fileData;
	vector<string> procName;
	vector<string> varName;
	vector<string> stmtType;
	vector<int> depthLv;
	vector<pair<int, string>> modifies;
	vector<pair<int, string>> uses;
	vector<pair<string, string>> calls;

	//references
	PKB pkb;
	
	int currentIndex;
	vector <string> tokens;
	int currentDepth;

	bool isDataProcessed;
	string currentProcessingProc;
	string outputFileName;

//public methods
public:
	Parser();
	~Parser();
	void parse(string fileName);
	void buildPKB();
	void buildVarTable();
	void buildFollowTable();
	void buildModifyTable();
	void buildParentTable();
	void buildStatTable();
	void buildUseTable();
	void buildProcTable();
	void buildCallTable();
	bool getFileData(string fileDirectory);

	//testing methods
	int getProcNumber();
	int getVarNumber();
	int getStmtNumber();
	int getModifyPairNumber();
	int getUsePairNumber();
	int getCallPairNumber();

//private helper methods
private:
	void readFileData();
	vector<string> preprocessData(ifstream& file);
	TNode* readProcedure();
	TNode* readStmtList();
	TNode* readWhileStmt();
	TNode* readCallStmt();
	TNode* readIfStmt();
	TNode* readAssignStmt();
	TNode* readExpression(vector<string> expressionTokens);
	TNode* readTerm(vector<string> termTokens);
	TNode* readFactor(vector<string> factorTokens);
	

	void match(string expectedToken);
	string getNextToken();
	string peekForwardToken (int numberOfIndexForward);
	void error();
	vector<string> breakFileDataIntoElements();
	bool isNumber(const string str);
	int getFollowedStmt(int i);
	int getParentStmt(int i);
	int getLastIndexOfTokenNotIndsideBracket (vector<string> tokens, string token);
};