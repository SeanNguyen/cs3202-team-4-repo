#pragma once

#include "Parser.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

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

void Parser::buildPKB() {
	buildProcTable();
	buildStatTable();
	buildVarTable();

	buildCallTable();
	buildFollowTable();
	buildModifyTable();
	buildParentTable();
	buildUseTable();
	buildCFG();
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
		string parentProc = getParentProc (stmt);
		int procIndex = pkb.getProcIndex (parentProc).front();
		pkb.insertModifiesProc (procIndex, varIndex);

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
	for (size_t i = 0; i < this->procName.size(); i++) {
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
	for (size_t i = 0; i < this->calls.size(); i++) {
		pair <string, string> callPair = this->calls[i];
		int callingStmt = pkb.getProcIndex(callPair.first).front();
		int callingProc = pkb.getProcIndex(getParentProc(callingStmt)).front();
		int calledProc = pkb.getProcIndex(callPair.second).front();
		pkb.insertCalls(callingProc, calledProc);
		pkb.insertCallStmt(callingStmt, calledProc);
	}
}

void Parser::buildCFG() {
	for (size_t i = 0; i < stmtType.size(); i++) {
			buildControlFlowPath(i);
	}
	for (size_t i = 0; i < CFGNodes.size(); i++) {
		vector <int>  nextStmts = CFGNodes[i];
		for (size_t j = 0; j < nextStmts.size(); j++) {
			PKB::insertNext(i, nextStmts[j]);
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
			if (curChar=='*' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " * "); 
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
			if (curChar=='(' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " ( "); 
				i+=2;
			}
			if (curChar==')' && ((int)i==0 || curLine.at(i)!=' ')) {
				curLine = curLine.replace(i, 1, " ) "); 
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
	this->currentIndex = UINT_MAX;
	this->isDataProcessed = false;

	TNode* progNode = PKB::createNode(Program);

	while (this->currentIndex == UINT_MAX || this->currentIndex < this->tokens.size() - 1) {
		TNode* procedureNode = readProcedure();
		progNode->addChild(procedureNode);
	}

	// set progNode as root of AST
	PKB::setASTRoot(progNode);

	// mark data as processed
	Parser::isDataProcessed = true;
}

TNode* Parser::readProcedure() {
	match(KEYWORD_PROCEDURE);
	currentProcessingProc = getNextToken();
	procName.push_back(currentProcessingProc);
	this->currentDepth = 0;
	this->mapStartingStmtProc[this->stmtType.size()] = currentProcessingProc;

	// create a node for procedure
	TNode* procNode = PKB::createNode(Procedure, currentProcessingProc);
	TNode* stmtListNode = readStmtList();
	procNode->addChild(stmtListNode);

	int endOfProc = stmtType.size();
	return procNode;
}

TNode* Parser::readStmtList() {
	match(KEYWORD_OPENCURLYBRACKET);
	TNode* stmtListNode = PKB::createNode(StmtList);
	this->currentDepth++;

	while (true) {
		string nextToken = peekForwardToken(1);
		if (nextToken == KEYWORD_CLOSECURLYBRACKET)
			break;
		TNode* stmtNode = readStmt();
		stmtListNode->addChild(stmtNode);
	}

	match(KEYWORD_CLOSECURLYBRACKET);
	if (stmtListNode->getNumChildren() == 0)
		error();
	this->currentDepth--;
	return stmtListNode;
}

TNode* Parser::readStmt() {
	this->depthLv.push_back(currentDepth);
	this->thenStmtFlags.push_back(0);
	this->CFGNodes.push_back(vector<int>());
	this->processedCFGStmtFlags.push_back(0);

	TNode* stmtNode;
	string nextToken = peekForwardToken(1);
	if (nextToken == KEYWORD_WHILE) {
		stmtNode = readWhileStmt();
	} else if (nextToken == KEYWORD_IF) {
		stmtNode = readIfStmt();
	} else if (nextToken == KEYWORD_CALL) {
		stmtNode = readCallStmt();
	} else {
		stmtNode = readAssignStmt();
	}
	return stmtNode;
}

TNode* Parser::readWhileStmt() {
	match(KEYWORD_WHILE);

	//Stmt
	TNode* whileNode = PKB::createNode(While);
	this->stmtType.push_back(KEYWORD_WHILE);

	//Variable
	string conditionVar = getNextToken();
	TNode* varNode = PKB::createNode(Var, conditionVar);
	whileNode->addChild(varNode);
	varName.push_back(conditionVar);
	pair<int, string> usePair(stmtType.size(), conditionVar);
	uses.push_back(usePair);

	TNode* stmtListNode = readStmtList();
	whileNode->addChild(stmtListNode);

	return whileNode;
}

TNode* Parser::readCallStmt () {
	match(KEYWORD_CALL);
	stmtType.push_back(KEYWORD_CALL);

	//create nodes in PKB
	TNode* callNode = PKB::createNode(CallStmt);

	string calledProcedureName = getNextToken();
	this->mapCallingStmtProc[stmtType.size() - 1] = calledProcedureName;
	TNode* calledProcNode = PKB::createNode (Procedure, calledProcedureName);
	callNode->addChild(calledProcNode);
	procName.push_back(calledProcedureName);

	//insert to callTable
	pair <string, string> callPair(currentProcessingProc, calledProcedureName);
	calls.push_back(callPair);

	match(KEYWORD_SEMICOLON);

	return callNode;
}

TNode* Parser::readIfStmt () {
	match(KEYWORD_IF);
	stmtType.push_back(KEYWORD_IF);

	//create Node in PKB
	TNode* ifNode = PKB::createNode(If);
	string conditionVar = getNextToken();
	TNode* varNode = PKB::createNode(Var, conditionVar);
	ifNode->addChild(varNode);
	varName.push_back(conditionVar);
	pair<int, string> usePair(stmtType.size(), conditionVar);
	uses.push_back(usePair);

	//process stmt list of "then"
	match(KEYWORD_THEN);
	size_t startOfThenStmtList = this->stmtType.size();
	TNode* thenNode = readStmtList();
	size_t endOfThenStmtList = this->stmtType.size() - 1;
	ifNode->addChild(thenNode);

	for (size_t i = startOfThenStmtList; i <= endOfThenStmtList; i++) {
		if (depthLv[i] - 1 == currentDepth)
			this->thenStmtFlags[i] = 1;
	}

	//processstmt list of "else"
	match(KEYWORD_ELSE);
	TNode* elseNode = readStmtList();
	ifNode->addChild(elseNode);

	return ifNode;
}

TNode* Parser::readAssignStmt() {
	TNode* assignNode = PKB::createNode(Assign);
	this->stmtType.push_back(KEYWORD_ASSIGN);

	string leftHandSideVar = getNextToken();
	varName.push_back(leftHandSideVar);
	pair<int, string> modifyPair(stmtType.size(), leftHandSideVar);
	modifies.push_back(modifyPair);
	TNode* varNode = PKB::createNode(Var, leftHandSideVar);
	assignNode->addChild(varNode);

	match (KEYWORD_EQUALSIGN);

	vector<string> expressionTokens;
	//parse the nearest ";"
	for (size_t i = this->currentIndex; i <this->tokens.size(); i++) {
		string currentPeekedToken = peekForwardToken(i - this->currentIndex);
		if (currentPeekedToken == KEYWORD_SEMICOLON) {
			expressionTokens = vector<string>(this->tokens.begin() + this->currentIndex + 1, this->tokens.begin() + i);
			this->currentIndex = i - 1;
			break;
		}
	}

	if (expressionTokens.empty()) {
		error();
	}

	TNode* expression = readExpression(expressionTokens);
	assignNode->addChild(expression);
	match(KEYWORD_SEMICOLON);

	return assignNode;
}

TNode* Parser::readExpression(vector<string> expressionTokens) {
	int lastPlusSignIndex = getLastIndexOfTokenNotInsideBracket(expressionTokens, KEYWORD_PLUSSIGN);
	int lastMinusSignIndex = getLastIndexOfTokenNotInsideBracket(expressionTokens, KEYWORD_MINUSSIGN);
	int lastSignIndex = max(lastPlusSignIndex, lastMinusSignIndex);

	if (lastSignIndex < 0) {
		return readTerm(expressionTokens);
	}

	vector<string> subExpressionTokens (expressionTokens.begin(), expressionTokens.begin() + lastSignIndex);
	vector<string> termTokens (expressionTokens.begin() + lastSignIndex + 1, expressionTokens.end());
	TNode* subExpresstionNode = readExpression(subExpressionTokens);
	TNode* termNode = readTerm(termTokens);
	TNode* signNode;
	if (lastSignIndex == lastPlusSignIndex) {
		signNode = PKB::createNode(Plus);
	} else if (lastSignIndex == lastMinusSignIndex) {
		signNode = PKB::createNode(Minus);
	}
	signNode->addChild(subExpresstionNode);
	signNode->addChild(termNode);
	return signNode;
}

TNode* Parser::readTerm(vector<string> termTokens) {
	size_t lastMulSignIndex = getLastIndexOfTokenNotInsideBracket(termTokens, KEYWORD_MULTIPLYSIGN);
	if (lastMulSignIndex > 0 && lastMulSignIndex < termTokens.size() - 1) {
		vector<string> subTermTokens;
		vector<string> factorTokens;
		for (size_t i = 0; i < termTokens.size(); i++) {
			if (i < lastMulSignIndex)
				subTermTokens.push_back(termTokens[i]);
			if (i > lastMulSignIndex)
				factorTokens.push_back(termTokens[i]);
		}
		TNode* mulNode = PKB::createNode(Times);
		TNode* subTermNode = readTerm(subTermTokens);
		TNode* factorNode = readFactor(factorTokens);
		mulNode->addChild(subTermNode);
		mulNode->addChild(factorNode);
		return mulNode;
	} else {
		return readFactor(termTokens);
	}
}

TNode* Parser::readFactor(vector<string> factorTokens) {
	string firstToken = factorTokens.front();
	string lastToken = factorTokens.back();
	if (firstToken == KEYWORD_OPENBRACKET && lastToken == KEYWORD_CLOSEBRACKET) {
		vector<string> expressionTokens (factorTokens.begin() + 1, factorTokens.end() - 1);
		return readExpression(expressionTokens);
	} else if (isNumber(firstToken) && factorTokens.size() == 1) {
		PKB::insertConst(firstToken);
		return PKB::createNode(Const, firstToken);
	} else  if (factorTokens.size() == 1) {
		varName.push_back(firstToken);
		pair<int, string> usePair(stmtType.size(), firstToken);
		uses.push_back(usePair);
		return PKB::createNode(Var, firstToken);
	}
	error();
	return NULL;
}

//Helper Methods
void Parser::match(string expectedToken) {
	string realToken = getNextToken();
	if (expectedToken != realToken) {
		error();
	}
}

string Parser::getNextToken() {
	if (this->currentIndex == UINT_MAX ) {
		this->currentIndex = 0;
	} else {
		this->currentIndex++;
	}

	if (this->currentIndex >= this->tokens.size())
		error();
	string token = this->tokens[this->currentIndex];
	return token;
}

string Parser::peekForwardToken (int numberOfIndexForward) {
	size_t peekedIndex = currentIndex + numberOfIndexForward;
	string result;
	if (peekedIndex < this->tokens.size()) {
		result = this->tokens[peekedIndex];
	}
	return result;
}

void Parser::error() {
	throw bad_exception("There are some syntax or logic errors in your SIMPLE source code");
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
			if (isStartingStmtOfProc(j + 1)) return -1;
			if (depthLv.at(j)==lv-1) return -1;
			if (depthLv.at(j)==lv && thenStmtFlags[i] == thenStmtFlags[j]) return j;
		}
	}
	return -1;
}

int Parser::getFollowingStmt(int i) {
	int numberOfStmt = this->stmtType.size();
	if (i < numberOfStmt - 1) {
		int lv = depthLv.at(i);
		for (int j=i + 1; j < numberOfStmt; j++) {
			if (isStartingStmtOfProc(j)) return -1;
			if (depthLv.at(j)==lv-1) return -1;
			if (depthLv.at(j)==lv && thenStmtFlags[i] == thenStmtFlags[j]) return j;
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

int Parser::getLastIndexOfTokenNotInsideBracket (vector<string> tokens, string token) {
	int nestedLv = 0;
	vector <int> tokenNestedLvs(tokens.size());
	for (size_t i = 0; i < tokens.size(); i++) {
		tokenNestedLvs[i] = nestedLv;
		if (tokens[i] == KEYWORD_OPENBRACKET)
			nestedLv++;
		if (tokens[i] == KEYWORD_CLOSEBRACKET)
			nestedLv--;
	}
	for (int i = tokens.size() - 1; i >= 0; i--) {
		if (tokens[i] == token && tokenNestedLvs[i] == 0)
			return i;
	}
	return -1;
}

void Parser::buildControlFlowPath(size_t stmtNo) {
	if (this->processedCFGStmtFlags[stmtNo] == 1)
		return;
	processedCFGStmtFlags[stmtNo] = 1;
	vector <int> nextStmts = getNextNodeInControlFlow(stmtNo);
	for (size_t i = 0; i < nextStmts.size(); i++) {
		int nextStmt = nextStmts[i];
		CFGNodes[stmtNo].push_back(nextStmt);
		buildControlFlowPath(nextStmt);
	}
}

vector <int> Parser::getNextNodeInControlFlow(int stmtNo) {
	vector <int> result;

	//consider children stmts
	string type = stmtType[stmtNo];
	if (type == KEYWORD_WHILE) {
		result.push_back(stmtNo + 1);
	} else if (type == KEYWORD_CALL) {
		//In this case we consider stmt after call is not count, uncomment when we consider it again
		/*string calledProc = this->mapCallingStmtProc[stmtNo];
		int startingStmtOfProc;
		for (std::map<int, string>::iterator value = mapStartingStmtProc.begin(); value != mapStartingStmtProc.end(); value++) {
			if (value->second == calledProc) {
				startingStmtOfProc = value->first;
				break;
			}
		}
		result.push_back(startingStmtOfProc);*/
	} else if (type == KEYWORD_IF) {
		vector <int> childrenStmts = getChildrenStmts(stmtNo);
		int startElseStmtNo;
		for (size_t i = 0; i < childrenStmts.size(); i++) {
			int childStmtNo = childrenStmts[i];
			if (thenStmtFlags[childStmtNo] == 0) {
				startElseStmtNo = childStmtNo;
				break;
			}
		}
		result.push_back(stmtNo + 1);
		result.push_back(startElseStmtNo);
	}


	//consider these are nested stmts
	int parentStmtNo = getParentStmt(stmtNo);
	if (parentStmtNo == -1) {
		int followingStmt = getFollowingStmt(stmtNo);
		if (followingStmt != -1)
			result.push_back(followingStmt);

	} else if (stmtType[parentStmtNo] == KEYWORD_WHILE) {
		int followingStmt = getFollowingStmt(stmtNo);
		if (followingStmt == -1)
			result.push_back(parentStmtNo);
		else
			result.push_back(followingStmt);

	} else if (stmtType[parentStmtNo] == KEYWORD_IF) {
		int followingStmt = getFollowingStmt(stmtNo);
		if (followingStmt > -1)
			result.push_back(followingStmt);
		else {
			vector <int> followingStmts = getNextNodeInControlFlow(parentStmtNo);
			if (followingStmts.size() == 3)
				result.push_back(followingStmts.back()); //supposed to be the one that not include children of if stmt
		}
	}

	return result;
}

vector <int> Parser::getChildrenStmts(int stmtNo) {
	vector <int> result;
	for (size_t i = stmtNo + 1; i < stmtType.size(); i++) {
		int parentDepthLv = depthLv[stmtNo];
		int currentDepthLv = depthLv[i];
		if (currentDepthLv <= parentDepthLv)
			break;
		if (currentDepthLv - 1 == parentDepthLv)
			result.push_back(i);
	}
	return result;
}

bool Parser::isStartingStmtOfProc (int stmtNo) {
	return this->mapStartingStmtProc.count(stmtNo) > 0;
}

string Parser::getParentProc (int stmt) {
	int result = -1;
	for (map <int, string>::iterator i = mapStartingStmtProc.begin(); i != mapStartingStmtProc.end(); i++)	{
		int statingStmt = i->first;
		if (stmt >= statingStmt && (result == -1 || result < statingStmt))
			result = statingStmt;
	}
	return this->mapStartingStmtProc[result];
}

//Testing methods
int Parser::getProcNumber() {
	return this->procName.size();
}

int Parser::getVarNumber() {
	return this->varName.size();
}

int Parser::getStmtNumber() {
	return this->stmtType.size();
}

int Parser::getThenStmtNumber() {
	int count = 0;
	for (size_t i = 0; i < this->thenStmtFlags.size(); i++)	{
		if (this->thenStmtFlags[i] == 1)
			count++;
	}
	return count;
}

int Parser::getModifyPairNumber() {
	return this->modifies.size();
}

int Parser::getUsePairNumber() {
	return this->uses.size();
}

int Parser::getCallPairNumber() {
	return this->calls.size();
}