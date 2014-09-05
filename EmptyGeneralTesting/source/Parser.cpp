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
		if (element== "procedure") {
			int j=i;
			TNode procNode = readProcedure(elements, &i);
			if (j==0) {
				// set progNode's name = procNode's name
				progNode = PKB::createNode("program", procNode.getValue());
			}
			progNode.setChild(procNode);
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
	string procName = elements[*i];

	// create a node for procedure
	TNode procNode = PKB::createNode("procedure", procName);

	// next element must be open brace
	string element = elements[++*i];
	if (element=="{") {
		// create stmtListNode
		TNode stmtListNode = PKB::createNode("stmtList", "");
		for (int j=*i; j< (int)elements.size(); j++) {
			element = elements[j];
			if (element=="while") {
				stmtType.push_back("while:stmtList");
				depthLv.push_back(depth);
				TNode whileNode = readWhileStmt(elements, &j);
				stmtListNode.setChild(whileNode);
			} else if (element=="}") {
				*i = j;
				break;
			} else {
				if (j<(int)elements.size()-1 && elements[j+1]=="=") {
					stmtType.push_back("assignment");
					depthLv.push_back(depth);
					TNode assignNode = readAssignStmt(elements, &j);
					stmtListNode.setChild(assignNode);
				}
			}
		}
		procNode.setChild(stmtListNode);
	} else {
		// throw error here
	}
	return procNode;
}

TNode Parser::readWhileStmt(vector<string> elements, int *i) {
	TNode whileNode = PKB::createNode("while", "");
	string element = elements[++*i];
	// element must be a variable name used by this while stmt
	// create a node for this var and add it to var list
	TNode varNode = PKB::createNode("variable", element);
	whileNode.setChild(varNode);
	varName.push_back(element);
	pair<int, string> usePair(stmtType.size(), element);
	uses.push_back(usePair);

	element = elements[++*i];
	// element must be an open brace
	// create a node for stmtList
	TNode stmtListNode = PKB::createNode("stmtList", "");
	
	depth++;

	for (int j=*i; j<(int)elements.size(); j++) {
		element = elements[j];
		if (element=="while") {
			stmtType.push_back("while:stmtList");
			depthLv.push_back(depth);
			// again, call the function readWhileStmt to get a whileNode
			TNode whileNode2 = readWhileStmt(elements, &j);
			stmtListNode.setChild(whileNode2);
		} else if (element=="}") {
			// end while, break here
			// update *i first
			*i = j;
			// update depth: return it to 1 lv higher
			depth--;
			break;
		} else {
			if (j<(int)elements.size()-1 && elements[j+1]=="=") {
				stmtType.push_back("assignment");
				depthLv.push_back(depth);
				TNode assignNode = readAssignStmt(elements, &j);
				stmtListNode.setChild(assignNode);
			}
		}
	}

	whileNode.setChild(stmtListNode);
	return whileNode;
}

TNode Parser::readAssignStmt(vector<string> elements, int *i) {
	TNode assignNode = PKB::createNode("assignment", "");

	// the symbol at left side of equal sign ("=") must be var modified by this assignment
	string element = elements[*i];
	varName.push_back(element);
	pair<int, string> modifyPair(stmtType.size(), element);
	modifies.push_back(modifyPair);
	TNode varNode = PKB::createNode("variable", element);
	assignNode.setChild(varNode);

	*i+=2;
	int j;
	// find the nearest semicolon
	for (j=*i; j<(int)elements.size(); j++) {
		if (elements[j]==";") 
			break;
	}

	TNode rightSideNode = readRightSideAssign(elements, *i, j-1);
	assignNode.setChild(rightSideNode);
	
	// update *i
	j=*i;

	return assignNode;
}

TNode Parser::readCallStmt (vector<string> elements, int *i) {
	TNode callNode = PKB::createNode("call", "");
	TNode dummyNode = TNode();
	return dummyNode;
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
			TNode constNode = PKB::createNode("constant", element);
			return constNode;
		} else {
			varName.push_back(element);
			pair<int, string> usePair(stmtType.size(), element);
			uses.push_back(usePair);
			TNode varNode = PKB::createNode("variable", element);
			return varNode;
		}
	} else {
		// second element from right side must be plus expression ("+")
		string element = elements[j-1];
		if (element=="+") {
			TNode plusNode = PKB::createNode("expression", "plus");
			// recursively process left side of plus expression
			TNode leftSideNode = readRightSideAssign(elements, i, j-2);

			plusNode.setChild(leftSideNode);

			// get element at j at check it type
			element = elements[j];
			if (isNumber(element)) {
				PKB::insertConst(element);
				TNode constNode = PKB::createNode("constant", element);
				plusNode.setChild(constNode);
			} else {
				varName.push_back(element);
				pair<int, string> usePair(stmtType.size(), element);
				uses.push_back(usePair);
				TNode varNode = PKB::createNode("variable", element);
				plusNode.setChild(varNode);
			}
			return plusNode;
		} else {
			// throw error here
		}
	}

	return PKB::createNode("", "");
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