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
public:
	// methods
	Parser();
	void parse(string fileName);
	void buildVarTable();
	void buildFollowTable();
	void buildModifyTable();
	void buildParentTable();
	void buildStatTable();
	void buildUseTable();

	bool getFileData(string fileDirectory);
	void getAST();
	void getProcTable();
	void getVarTable();
	void getStmtTypes();
	void getFollows();
	void getParent();
	void getModifies();
	void getUses();

	// testing methods
	void printFileData();
	void printProc();
	void printVar();
	void printStmtTypes();
	void printFollows();
	void printParent();
	void printModifies();
	void printUses();

private:
	// private variables
	static bool Parser::isDataProcessed;
	vector<string> fileData;
	vector<string> procName;
	vector<string> varName;
	vector<string> stmtType;
	vector<int> depthLv;
	int depth;
	vector<pair<int, string>> modifies;
	vector<pair<int, string>> uses;

	// private methods
	// main methods
	void readFileData();
	vector<string> preprocessData(ifstream& file);
	TNode readProcedure(vector<string> elements, int *i);
	TNode readWhileStmt(vector<string> elements, int *i);
	TNode readAssignStmt(vector<string> elements, int *i);
	TNode readRightSideAssign(vector<string> elements, int i, int j);

	// supporting methods
	vector<string> breakFileDataIntoElements();
	bool isNumber(const string str);
	int getFollowedStmt(int i);
	int getParentStmt(int i);
};