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
* Description: This function builds ProcTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildProcTable() {
	for (int i = 0; i < this->procName.size(); i++) {
		string procedureName = this->procName[i];
		pkb.insertProc(procedureName);
	}
}

/*
* Description: This function builds CallTable in PKB.
* Input	  : None.
* Output     : None.
*/
void Parser::buildCallTable() {
	for (int i = 0; i < this->calls.size(); i++) {
		pair <string, string> callPair = this->calls[i];
		int callingProc = pkb.getProcIndex(callPair.first).front();
		int calledProc = pkb.getProcIndex(callPair.second).front();
		pkb.insertCalls(callingProc, calledProc);
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
	this->tokens = breakFileDataIntoElements();

	// initialize parsing properties
	this->currentIndex = 0;
	this->isDataProcessed = false;

	TNode progNode;

	while (this->currentIndex < this->tokens.size()) {
		TNode procedureNode = readProcedure();
		progNode.addChild(procedureNode);
	}

	// set progNode as root of AST
	PKB::setASTRoot(progNode);

	// mark data as processed
	Parser::isDataProcessed = true;
}

TNode Parser::readProcedure() {
	match(KEYWORD_PROCEDURE);
	currentProcessingProc = getCurrentToken();
	procName.push_back(currentProcessingProc);
	this->currentDepth = 0;

	// create a node for procedure
	TNode procNode = PKB::createNode(Symbol::Procedure, currentProcessingProc);

	TNode stmtListNode = readStmtList();
	procNode.addChild(stmtListNode);
	return procNode;
}

TNode Parser::readStmtList() {
	match(KEYWORD_OPENCURLYBRACKET);
	TNode stmtListNode = PKB::createNode(Symbol::StmtList);
	this->currentDepth++;

	while (true) {
		string nextToken = peekForwardToken(1);
		if (nextToken == KEYWORD_WHILE) {
			TNode whileNode = readWhileStmt();
			stmtListNode.addChild(whileNode);
		} else if (nextToken == KEYWORD_IF) {
			TNode ifNode = readIfStmt();
			stmtListNode.addChild(ifNode);
		} else if (nextToken == KEYWORD_CALL) {
			TNode callNode = readCallStmt();
			stmtListNode.addChild(callNode);
		} else if (nextToken == KEYWORD_CLOSECURLYBRACKET) {
			break;
		} else {
			TNode assignNode = readAssignStmt();
			stmtListNode.addChild(assignNode);
		}
	}

	match(KEYWORD_CLOSEBRACKET);
	this->currentDepth--;
	return stmtListNode;
}

TNode Parser::readWhileStmt() {
	match(KEYWORD_WHILE);
	TNode whileNode = PKB::createNode(Symbol::While);
	this->depthLv.push_back(currentDepth);
	this->stmtType.push_back(KEYWORD_WHILE);

	string conditionVar = getCurrentToken();
	TNode varNode = PKB::createNode(Symbol::Var, conditionVar);
	whileNode.addChild(varNode);
	varName.push_back(conditionVar);
	pair<int, string> usePair(stmtType.size(), conditionVar);
	uses.push_back(usePair);

	TNode stmtListNode = readStmtList();
	whileNode.addChild(stmtListNode);

	return whileNode;
}

TNode Parser::readCallStmt () {
	match(KEYWORD_CALL);
	this->depthLv.push_back(this->currentDepth);
	stmtType.push_back(KEYWORD_CALL);

	//create nodes in PKB
	TNode callNode = PKB::createNode(Symbol::Calls);

	string calledProcedureName = getCurrentToken();
	TNode calledProcNode = PKB::createNode (Symbol::Procedure, calledProcedureName);
	callNode.addChild(calledProcNode);
	procName.push_back(calledProcedureName);

	//insert to callTable
	pair <string, string> callPair(currentProcessingProc, calledProcedureName);
	calls.push_back(callPair);

	match(KEYWORD_SEMICOLON);

	return callNode;
}

TNode Parser::readIfStmt () {
	match(KEYWORD_IF);
	this->depthLv.push_back(currentDepth);
	stmtType.push_back(KEYWORD_IF);

	//create Node in PKB
	TNode ifNode = PKB::createNode(Symbol::If);
	string conditionVar = getCurrentToken();
	TNode varNode = PKB::createNode(Symbol::Var, conditionVar);
	ifNode.addChild(varNode);
	varName.push_back(conditionVar);
	pair<int, string> usePair(stmtType.size(), conditionVar);
	uses.push_back(usePair);

	//process stmt list
	TNode stmtListNode = readStmtList();
	ifNode.addChild(stmtListNode);
	return ifNode;
}

TNode Parser::readAssignStmt() {
	TNode assignNode = PKB::createNode(Symbol::Assign);
	this->depthLv.push_back(this->currentDepth);
	this->stmtType.push_back(KEYWORD_ASSIGN);

	string leftHandSideVar = getCurrentToken();
	varName.push_back(leftHandSideVar);
	pair<int, string> modifyPair(stmtType.size(), leftHandSideVar);
	modifies.push_back(modifyPair);
	TNode varNode = PKB::createNode(Symbol::Var, leftHandSideVar);
	assignNode.addChild(varNode);

	match (KEYWORD_EQUALSIGN);

	vector<string> expressionTokens;
	//parse the nearest ";"
	for (int i = this->currentIndex; i <this->tokens.size(); i++) {
		string currentPeekedToken = peekForwardToken(i - this->currentIndex);
		if (currentPeekedToken == KEYWORD_SEMICOLON) {
			expressionTokens = vector<string>(this->tokens.begin() + this->currentIndex, this->tokens.begin() + i);
			this->currentIndex = i;
			break;
		}
	}

	if (expressionTokens.empty()) {
		error();
	}

	TNode expression = readExpression(expressionTokens);
	assignNode.addChild(expression);
	match(KEYWORD_SEMICOLON);

	return assignNode;
}

TNode Parser::readExpression(vector<string> expressionTokens) {
	int lastPlusSignIndex = getLastIndexOfToken(expressionTokens, KEYWORD_PLUSSIGN);
	int lastMinusSignIndex = getLastIndexOfToken(expressionTokens, KEYWORD_MINUSSIGN);
	int lastSignIndex = max(lastPlusSignIndex, lastMinusSignIndex);

	if (lastSignIndex < 0) {
		return readTerm(expressionTokens);
	}
	
	vector<string> subExpressionTokens (expressionTokens.begin(), expressionTokens.begin() + lastSignIndex);
	vector<string> termTokens (expressionTokens.begin() + lastSignIndex + 1, expressionTokens.end());
	TNode subExpresstionNode = readExpression(subExpressionTokens);
	TNode termNode = readTerm(termTokens);
	TNode signNode;
	if (lastSignIndex == lastPlusSignIndex) {
		signNode = PKB::createNode(Symbol::Plus);
	} else if (lastSignIndex == lastMinusSignIndex) {
		signNode = PKB::createNode(Symbol::Minus);
	}
	signNode.addChild(subExpresstionNode);
	signNode.addChild(termNode);
	return signNode;
}

TNode Parser::readTerm(vector<string> termTokens) {
	int lastMulSignIndex = getLastIndexOfToken(termTokens, KEYWORD_MULTIPLYSIGN);
	if (lastMulSignIndex > 0 && lastMulSignIndex < termTokens.size() - 1) {
		vector<string> subTermTokens;
		vector<string> factorTokens;
		for (int i = 0; i < termTokens.size(); i++) {
			if (i < lastMulSignIndex)
				subTermTokens.push_back(termTokens[i]);
			if (i > lastMulSignIndex)
				factorTokens.push_back(termTokens[i]);
		}
		TNode mulNode = PKB::createNode(Symbol::Times);
		TNode subTermNode = readTerm(subTermTokens);
		TNode factorNode = readFactor(factorTokens);
		mulNode.addChild(subTermNode);
		mulNode.addChild(factorNode);
		return mulNode;
	} else {
		return readFactor(termTokens);
	}
}

TNode Parser::readFactor(vector<string> factorTokens) {
	string firstToken = factorTokens.front();
	string lastToken = factorTokens.back();
	if (firstToken == KEYWORD_OPENBRACKET && lastToken == KEYWORD_CLOSEBRACKET) {
		vector<string> expressionTokens (factorTokens.begin() + 1, factorTokens.end() - 1);
		return readExpression(expressionTokens);
	} else if (isNumber(firstToken) && factorTokens.size() == 1) {
		PKB::insertConst(firstToken);
		return PKB::createNode(Symbol::Const, firstToken);
	} else  if (factorTokens.size() == 1) {
		varName.push_back(firstToken);
		pair<int, string> usePair(stmtType.size(), firstToken);
		uses.push_back(usePair);
		return PKB::createNode(Symbol::Var, firstToken);
	}
	error();
}

//Helper Methods
void Parser::match(string expectedToken) {
	string realToken = getCurrentToken();
	if (expectedToken != realToken) {
		error();
	}
}

string Parser::getCurrentToken() {
	string token = this->tokens[this->currentIndex];
	this->currentIndex++;
	return token;
}

string Parser::peekForwardToken (int numberOfIndexForward) {
	int peekedIndex = currentIndex + numberOfIndexForward;
	string result;
	if (peekedIndex < this->tokens.size()) {
		result = this->tokens[peekedIndex];
	}
	return result;
}

void Parser::error() {
	throw new exception();
	exit(1);
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

int Parser::getLastIndexOfToken (vector<string> tokens, string token) {
	for (int i = tokens.size() - 1; i >= 0; i--) {
		if (tokens[i] == token)
			return i;
	}
	return -1;
}