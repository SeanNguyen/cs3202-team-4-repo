#pragma once

#include "Parser.h"

#include <string>
#include <iostream>

//PUBLIC METHODS
Parser::Parser() {
	Parser::isDataProcessed = false;
	outputFileName = "output.txt";
}

Parser::~Parser() {

}

/* Description: parse function will parse the SIMPLE source and store 
information of tables in Parser private data structure. */
void Parser::parse(string fileName)
{
	bool isValid = getFileData(fileName);
	if (isValid)
	{
		readFileData();
	}
}

/*
* Description: This function builds VarTable in PKB.
* Input	  : None.
* Output	  : None.
*/
void Parser::buildVarTable()
{
	for (size_t index=0; index < varName.size(); index++)
	{
		pkb.insertVar(varName[index]);
	}
}

/*
* Description: This function builds FollowTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildFollowTable()
{
	for (size_t index=0; index < depthLv.size(); ++index)
	{
		int f = getFollowedStmt(index);
		if (f >= 0)
		{
			pkb.insertFollows(f+1, index+1);
		}
	}
}

/*
* Description: This function builds ModifyTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildModifyTable()
{
	for(size_t index=0; index < modifies.size(); ++index)
	{
		int stmt = modifies.at(index).first - 1;
		int varIndex = pkb.getVarIndex(modifies.at(index).second);

		while (stmt >= 0)
		{
			pkb.insertModifies(stmt+1, varIndex);
			stmt = getParentStmt(stmt);
		}
	}
}

/*
* Description: This function builds ParentTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildParentTable()
{
	for (size_t index=0; index < depthLv.size(); ++index)
	{
		int p = getParentStmt(index);
		if (p >= 0)
		{
			pkb.insertParent(p+1, index+1);
		}
	}
}

/*
* Description: This function builds StatTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildStatTable()
{
	for(size_t index=0; index < stmtType.size(); ++index)
	{
		pkb.insertStmt(stmtType.at(index));
	}
}

/*
* Description: This function builds UseTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildUseTable()
{
	for(size_t index=0; index < uses.size(); ++index)
	{
		int stmt = uses.at(index).first - 1;
		int varIndex = pkb.getVarIndex(uses.at(index).second);
		while(stmt >= 0)
		{
			pkb.insertUses(stmt+1, varIndex);
			stmt = getParentStmt(stmt);
		}
	}
}

/*
* Description: this function look for input file using 
*				the directory user gives and preprocess the data 
* Input: file's directory
* Output: return true if file is found,
*		   otherwise return false
*/
bool Parser::getFileData(string fileDirectory) {
	ifstream file(fileDirectory.c_str());
	if (file.is_open()) {
		Parser::isDataProcessed = false;
		vector<string> fileData;
		fileData = preprocessData(file);
		file.close();
		return true;
	}
	return false;
}

//PRIVATE FUNCTIONS
/*
* Description: this function preprocess the data from input file.
*				It job includes: remove hashtab (comment), and 
*				separate elements
* Input: input file
* Output: a list of all preprocessed program lines 
*/
vector<string> Parser::preprocessData(ifstream& file) {
	string curLine;
	while(!file.eof()){
		getline(file, curLine);
		// remove all possible comments in program line
		if (curLine.find("\\")!=string::npos) {
			unsigned index = curLine.find("\\");
			curLine = curLine.substr(0, index);
		}

		// separate elements by white space
		// i.e. "=", "+", "{", "}", ";"
		for (size_t i=0; i<curLine.size(); i++) {
			char curChar = curLine.at(i);
			if (curChar=='=' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " = "); 
				i+=2;
			}
			if (curChar=='+' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " + "); 
				i+=2;
			}
			if (curChar=='{' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " { "); 
				i+=2;
			}
			if (curChar=='}' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " } "); 
				i+=2;
			}
			if (curChar==';' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " ; "); 
				i+=2;
			}
		}

		// save data to fileData
		if (curLine!="") {
			fileData.push_back(curLine);
		}
	}

	return fileData;
}

//main methods
void Parser::readFileData() {
	// rewrite logic in readFileData
	vector<string> elements = breakFileDataIntoElements();

	// initialize the depth of tree
	depth = 0;

	TNode progNode;

	// read list of elements, one by one
	for (int i=0; i<(int)elements.size(); i++) {
		string element = elements[i];
		if (element== KEYWORD_PROCEDURE) {
			int j=i;
			TNode procNode = readProcedure(elements, &i);
			if (j==0) {
				// set progNode's name = procNode's name
				progNode = PKB::createNode(Symbol::Program, procNode.getValue());
			}
			progNode.addChild(procNode);
		}
	}

	// set progNode as root of AST
	PKB::setASTRoot(progNode);

	// mark data as processed
	Parser::isDataProcessed = true;
}

TNode Parser::readProcedure(vector<string> elements, int *i) {
	// next element must be procedure name
	procName.push_back(elements[++*i]);
	currentProcessingProc = elements[*i];

	// create a node for procedure
	TNode procNode = PKB::createNode(Symbol::Procedure, currentProcessingProc);

	// next element must be open brace
	string element = elements[++*i];
	if (element=="{") {
		element = elements[++*i];
		// create stmtListNode
		TNode stmtListNode = readStmtList(elements, i);
		procNode.addChild(stmtListNode);
	} else {
		// throw error here
	}
	return procNode;
}

TNode Parser::readWhileStmt(vector<string> elements, int *i) {
	TNode whileNode = PKB::createNode(Symbol::While);
	string element = elements[++*i];
	// element must be a variable name used by this while stmt
	// create a node for this var and add it to var list
	TNode varNode = PKB::createNode(Symbol::Var, element);
	whileNode.addChild(varNode);
	varName.push_back(element);
	pair<int, string> usePair(stmtType.size(), element);
	uses.push_back(usePair);

	element = elements[++*i]; //supose to be  {

	TNode stmtListNode = readStmtList(elements, i);
	whileNode.addChild(stmtListNode);
	return whileNode;
}

TNode Parser::readAssignStmt(vector<string> elements, int *i) {
	TNode assignNode = PKB::createNode(Symbol::Assign);

	// the symbol at left side of equal sign ("=") must be var modified by this assignment
	string element = elements[*i];
	varName.push_back(element);
	pair<int, string> modifyPair(stmtType.size(), element);
	modifies.push_back(modifyPair);
	TNode varNode = PKB::createNode(Symbol::Var, element);
	assignNode.addChild(varNode);

	*i+=2;
	int j;
	// find the nearest semicolon
	for (j=*i; j<(int)elements.size(); j++) {
		if (elements[j]==";") 
			break;
	}

	TNode rightSideNode = readRightSideAssign(elements, *i, j-1);
	assignNode.addChild(rightSideNode);

	// update *i
	j=*i;

	return assignNode;
}

TNode Parser::readCallStmt (vector<string> elements, int *i) {
	//insert to depthLv Table
	depthLv.push_back(depth);

	//insert to stmtTable
	stmtType.push_back(KEYWORD_CALL);

	//create nodes in PKB
	TNode callNode = PKB::createNode(Symbol::Calls);
	string element = elements[++*i];
	TNode calledProcNode = PKB::createNode (Symbol::Procedure, element);
	callNode.addChild(calledProcNode);
	procName.push_back(element);

	//insert to callTable
	string callingProc = currentProcessingProc;
	string calledProc = element;
	pair <string, string> callPair(callingProc, calledProc);
	calls.push_back(callPair);

	element = elements[++*i]; //suppose to be a ;

	return callNode;
}

TNode Parser::readIfStmt (vector<string> elements, int *i) {
	//insert to depthLv Table
	depthLv.push_back(depth);

	//insert to stmt Table
	stmtType.push_back(KEYWORD_IF);

	//create Node in PKB
	TNode ifNode = PKB::createNode(Symbol::If);
	string element = elements[++*i]; // suppose to be a var
	TNode varNode = PKB::createNode(Symbol::Var, element);
	ifNode.addChild(varNode);
	varName.push_back(element);
	pair<int, string> usePair(stmtType.size(), element);
	uses.push_back(usePair);

	//process stmt list
	TNode stmtListNode = readStmtList(elements, i);
	ifNode.addChild(stmtListNode);
	return ifNode;
}

//Helper Methods
TNode Parser::readRightSideAssign(vector<string> elements, int i, int j) {
	// if there is only one element
	if (j-i==0) {
		// the element must be a var or const used by this assign
		string element = elements[i];
		// check if this is a var or a const
		if (isNumber(element)) {
			PKB::insertConst(element);
			TNode constNode = PKB::createNode(Symbol::Const, element);
			return constNode;
		} else {
			varName.push_back(element);
			pair<int, string> usePair(stmtType.size(), element);
			uses.push_back(usePair);
			TNode varNode = PKB::createNode(Symbol::Var, element);
			return varNode;
		}
	} else {
		// second element from right side must be plus expression ("+")
		string element = elements[j-1];
		if (element=="+") {
			TNode plusNode = PKB::createNode(Symbol::Plus);
			// recursively process left side of plus expression
			TNode leftSideNode = readRightSideAssign(elements, i, j-2);

			plusNode.addChild(leftSideNode);

			// get element at j at check it type
			element = elements[j];
			if (isNumber(element)) {
				PKB::insertConst(element);
				TNode constNode = PKB::createNode(Symbol::Const, element);
				plusNode.addChild(constNode);
			} else {
				varName.push_back(element);
				pair<int, string> usePair(stmtType.size(), element);
				uses.push_back(usePair);
				TNode varNode = PKB::createNode(Symbol::Var, element);
				plusNode.addChild(varNode);
			}
			return plusNode;
		} else {
			// throw error here
		}
	}

	return PKB::createNode();
}

TNode Parser::readStmtList (vector<string> elements, int *i) {
	TNode stmtListNode = PKB::createNode(Symbol::StmtList);

	depth++;

	for (int j=*i; j<(int)elements.size(); j++) {
		string element = elements[j];
		if (element==KEYWORD_WHILE) {
			stmtType.push_back(KEYWORD_WHILE);
			depthLv.push_back(depth);
			// again, call the function readWhileStmt to get a whileNode
			TNode whileNode2 = readWhileStmt(elements, &j);
			stmtListNode.addChild(whileNode2);
		} else if (element == KEYWORD_IF) {
			TNode ifNode = readIfStmt(elements, &j);
			stmtListNode.addChild(ifNode);
		} else if (element == KEYWORD_CALL) {
			TNode callNode = readCallStmt(elements, &j);
			stmtListNode.addChild(callNode);
		} else if (element=="}") {
			*i = j;
			depth--;
			break;
		} else {
			if (j<(int)elements.size()-1 && elements[j+1]=="=") {
				stmtType.push_back(KEYWORD_ASSIGNMENT);
				depthLv.push_back(depth);
				TNode assignNode = readAssignStmt(elements, &j);
				stmtListNode.addChild(assignNode);
			}
		}
	}
	return stmtListNode;
}

vector<string> Parser::breakFileDataIntoElements() {
	vector<string> elements;
	for (size_t i=0; i< fileData.size(); i++) {
		string element;
		string line = fileData[i];
		istringstream ss;
		ss.str(line);
		while (ss >> element) {
			elements.push_back(element);
		}
	}
	return elements;
}

bool Parser::isNumber(const string str) {
	string::const_iterator it = str.begin();
	while (it != str.end() && isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

int Parser::getFollowedStmt(int i) {
	if (i>0) {
		int lv = depthLv.at(i);
		for (int j=i-1; j>=0; j--) {
			if (depthLv.at(j)==lv-1) return -1;
			if (depthLv.at(j)==lv) return j;
		}
	}
	return -1;
}

int Parser::getParentStmt(int i) {
	int lv = depthLv.at(i);
	if (i>0 && lv!=0) {
		for (int j=i-1; j>=0; j--) {
			if (depthLv.at(j)==lv-1) return j;
		}
	}
	return -1;
}