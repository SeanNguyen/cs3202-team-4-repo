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
	bool isDataProcessed;
	string outputFileName;

	vector<string> fileData;
	vector<string> procName;
	vector<string> varName;
	vector<string> stmtType;
	vector<int> depthLv;
	int depth;
	vector<pair<int, string>> modifies;
	vector<pair<int, string>> uses;

//public methods
public:
	Parser();
	void parse(string fileName);
	void buildVarTable();
	void buildFollowTable();
	void buildModifyTable();
	void buildParentTable();
	void buildStatTable();
	void buildUseTable();
	bool getFileData(string fileDirectory);

//private helper methods
private:
	void readFileData();
	vector<string> preprocessData(ifstream& file);
	TNode readProcedure(vector<string> elements, int *i);
	TNode readWhileStmt(vector<string> elements, int *i);
	TNode readAssignStmt(vector<string> elements, int *i);
	TNode readCallStmt (vector<string> elements, int *i);

	TNode readRightSideAssign(vector<string> elements, int i, int j);
	vector<string> breakFileDataIntoElements();
	bool isNumber(const string str);
	int getFollowedStmt(int i);
	int getParentStmt(int i);
};