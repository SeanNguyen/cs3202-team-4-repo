#pragma once

#include "Parser.h"

#include <string>
#include <iostream>

/* PARAMETERS*/
/* This parameter ensures that
 * function readFileData() runs only once
 */
bool Parser::isDataProcessed = false;

/* Write all information of source to outputFile. outputFile is used as a reference to build integration testing between Parser and tables. */
string outputFileName = "output.txt";

/* PUBLIC FUNCTIONS */

// Default constructor
Parser::Parser()
{

}

/* Description: parse function will parse the SIMPLE source and store information of tables in Parser private data structure. */
void Parser::parse(string fileName)
{
	bool isValid = getFileData(fileName);
	if (isValid)
	{
		getAST();
	}
}

//void Parser::buildPKBTables()
//{
//	buildVarTable();
//}
//

/*
 * Description: This function builds VarTable in PKB.
 * Input	  : None.
 * Output	  : None.
 */
void Parser::buildVarTable()
{
	PKB pkb;
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
	PKB pkb;
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
	PKB pkb;
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
	PKB pkb;
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
	PKB pkb;
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
	PKB pkb;
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
	cout<< "This is not a file directory" <<endl;
	return false;
}

/*
 * Description: this function get the AST from the program
 * Input: no input
 * Output: (next iteration) AST of the program
 */
void Parser::getAST() {
	return readFileData();
}

void Parser::getProcTable() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

void Parser::getVarTable() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

void Parser::getFollows() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

void Parser::getParent() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

void Parser::getModifies() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

void Parser::getUses() {
	if (!Parser::isDataProcessed) {
		readFileData();
	}
}

/* PRIVATE FUNCTIONS */
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

/*
 * Description: this function reads fileData after the preprocessing phase.
 *				It create the AST and data for building tables
 *				Supposedly, it should return the AST of the program 
 * Input: no input
 * Output: (in next iteration) return AST
 */

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

	/*
	string prevElement;
	string curElement;
	int nestLv = 0;
	bool isInsideProc = false;
	
	for (size_t i=0; i<fileData.size(); i++) {
		string line = fileData[i];
		istringstream ss;
		ss.str(line);

		while (ss >> curElement) {
			// get procedure name
			if (prevElement=="procedure") {
				//cout<< "Name of procedure: " curElement <<endl;
				// create a node for procedure, return reference
				procName.push_back(curElement);
			}
			// recognize statement types
			if (curElement=="=") {
				depthLv.push_back(nestLv);
				// create a node for assignment, return reference
				stmtType.push_back("assignment");
				
				// recognize previous element as variable
				varName.push_back(prevElement);
				// recognize modifies relationship
				pair<int, string> temp (stmtType.size(), prevElement);
				modifies.push_back(temp);
			}
			if (curElement=="while") {
				// create a node for while, return reference
				depthLv.push_back(nestLv);
				stmtType.push_back("while:stmtList");
			}

			if (curElement=="{") {
				if (isInsideProc==false) {
					// acknowledge the beginning of procedure
					isInsideProc = true;
					//cout << "Begin reading procedure" <<endl <<endl;
				} else {
					// acknowledge new nesting level
					nestLv++;
					//cout<< "Meet a nest at level "<< nestLv <<endl;
				}
			}

			if (curElement=="+") {
				//cout<< "Found plus expression (+) " <<endl;
			}
			
			if (curElement=="}") {
				if (isInsideProc && nestLv==0) {
					// acknowledge end of procedure
					isInsideProc = false;
					cout << endl << "End of procedure" << endl;
				} else {
					nestLv--;
					//cout<< "End a nest at level" << nestedLevel +1 <<endl;
				}
			}

			if (prevElement=="while") {
				// recognize curElement as variable
				//cout<< "Find variable: " << curElement << " used." <<endl;
				varName.push_back(curElement);
				// recognize Uses relationship
				pair<int, string> temp (stmtType.size(), curElement);
				uses.push_back(temp);
			}

			if (prevElement=="=") {
				if (isNumber(curElement)) {
					// recognize curElement as constant
					//cout << "Find constant: " << curElement << endl;
					PKB::insertConst(curElement);
				} else {
					// recognize curElement as variable
					//cout << "Find variable: " << curElement << " used." <<endl;	
					varName.push_back(curElement);
					// recognize Uses relationship
					pair<int, string> temp (stmtType.size(), curElement);
					uses.push_back(temp);
				}
				
			}
			if (prevElement=="+") {
				if (isNumber(curElement)) {
					// recognize curElement as constant
					//cout << "Find constant: " << curElement << endl;
				} else {
					// recognize curElement as variable
					//cout << "Find variable: " << curElement << " used." <<endl;	
					varName.push_back(curElement);
					// recognize Uses relationship
					pair<int, string> temp (stmtType.size(), curElement);
					uses.push_back(temp);
				}
			}

			prevElement = curElement;
		}
	}
	*/

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
		// cout << "Start reading procedure" <<endl;

		// create stmtListNode
		TNode stmtListNode = PKB::createNode("stmtList", "");
		for (int j=*i; j< (int)elements.size(); j++) {
			element = elements[j];
			if (element=="while") {
				//cout << "Find while at lv " << depth <<endl;
				stmtType.push_back("while:stmtList");
				depthLv.push_back(depth);
				TNode whileNode = readWhileStmt(elements, &j);
				stmtListNode.setChild(whileNode);
			} else if (element=="}") {
				//cout <<"End of procedure" <<endl;
				*i = j;

				// break the loop here
				break;
			} else {
				if (j<(int)elements.size()-1 && elements[j+1]=="=") {
					//cout << "Find assignment at lv " << depth <<endl;
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
	//cout << "Find var " << element <<endl;
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
			//	cout << "Find while at lv " << depth <<endl;
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
				//cout << "Find assignment at lv " << depth <<endl;
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
	//cout << "Find var: " <<element <<endl;
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

TNode Parser::readRightSideAssign(vector<string> elements, int i, int j) {
	// if there is only one element
	if (j-i==0) {
		// the element must be a var or const used by this assign
		string element = elements[i];
		// check if this is a var or a const
		if (isNumber(element)) {
			//cout << "Find const " <<element <<endl;
			PKB::insertConst(element);
			TNode constNode = PKB::createNode("constant", element);
			return constNode;
		} else {
			//cout << "Find variable " <<element <<endl;
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
			//cout << "Found plus expression" <<endl;
			TNode plusNode = PKB::createNode("expression", "plus");
			// recursively process left side of plus expression
			TNode leftSideNode = readRightSideAssign(elements, i, j-2);

			plusNode.setChild(leftSideNode);

			// get element at j at check it type
			element = elements[j];
			if (isNumber(element)) {
				//cout << "Find const " <<element <<endl;
				PKB::insertConst(element);
				TNode constNode = PKB::createNode("constant", element);
				plusNode.setChild(constNode);
			} else {
				//cout << "Find variable " <<element <<endl;
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


/* TESTING FUNCTIONS */
void Parser::printFileData() {
	cout<< "Print out file data after preprocessing:" <<endl <<endl;
	for (size_t i=0; i<fileData.size(); i++) {
		cout<< fileData.at(i)<<endl;
	}
	cout << endl << "End of file " <<endl;
	return;
}

void Parser::printProc() {
	cout << endl << "Name of procedures" << endl;
	for (size_t i=0; i<procName.size(); i++) {
		cout << "  " << procName[i]<<endl;
		
	}
}

void Parser::printVar() {
	cout << endl << "Name of variables" << endl;
	for (size_t i=0; i<varName.size(); i++) {
		cout << "  " << varName[i]<<endl;
	}

	// Write to outputFile
	ofstream outputFile (outputFileName);
	if (outputFile.is_open())
	{
		outputFile << "Var Table: \n";
		for (size_t i=0; i<varName.size(); i++) 
		{
			ostringstream oss;
			oss << i << " " << varName[i] << "\n";
			string line = oss.str();
			outputFile << line;
		}
		outputFile.close();
	}
	
}

void Parser::printStmtTypes() {
	cout << endl << "List of statement types" << endl;
	for (size_t i=0; i<stmtType.size(); i++) {
		cout << "  "<< i+1 << "	"<< stmtType[i]<<endl;
	}

	// Write to output file.
	ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::out | std::ofstream::app);
	outputFile << "Statement Table: \n";
	for (size_t i=0; i<stmtType.size(); i++) 
	{
		ostringstream oss;
		oss << i+1 << " " << stmtType[i] << "\n";
		string line = oss.str();
		outputFile << line;	
	}
	outputFile.close();

}

void Parser::printFollows() {
	cout << endl << "List of Follows()" << endl;
	for (size_t i=0; i<depthLv.size(); i++) {
		int f = getFollowedStmt(i);
		if (f>=0) { 
			cout << "  Follows(" << f+1 << ", " << i+1 << ")" <<endl;
		}
	}

	// Write to output file.
	ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::out | std::ofstream::app);
	outputFile << "Follow Table: \n";
	for (size_t i=0; i<depthLv.size(); i++) 
	{
		int f = getFollowedStmt(i);
		if (f >= 0)
		{
			ostringstream oss;
			oss << f+1 << " " << i+1 << "\n";
			string line = oss.str();
			outputFile << line;
		}	
	}
	outputFile.close();
	
}

void Parser::printParent() {
	cout << endl << "List of Parent()" << endl;
	for (size_t i=0; i<depthLv.size(); i++) {
		int p = getParentStmt(i);
		if (p>=0) { 
			cout << "  Parent(" << p+1 << ", " << i+1 << ")" <<endl;
		}
	}

	// Write to output file.
	ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::out | std::ofstream::app);
	outputFile << "Parent Table: \n";
	for (size_t i=0; i<depthLv.size(); i++) 
	{
		int p = getParentStmt(i);
		if (p >= 0)
		{
			ostringstream oss;
			oss << p+1 << " " << i+1 << "\n";
			string line = oss.str();
			outputFile << line;
		}	
	}
	outputFile.close();

}

void Parser::printModifies() {
	cout << endl << "List of Modifies()" << endl;
	for (size_t i=0; i<modifies.size(); i++) {
		int stmt = modifies.at(i).first - 1;
		string var = modifies.at(i).second;
		while (stmt>=0) {
			cout << "  Modifies(" << stmt + 1 << ", " << var << ")" <<endl;
			stmt = getParentStmt(stmt);
		}
	}

	// Write to output file.
	ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::out | std::ofstream::app);
	outputFile << "Modify Table: \n";
	for (size_t i=0; i<modifies.size(); i++) 
	{
		int stmt = modifies.at(i).first - 1;
		string var = modifies.at(i).second;
		while (stmt>=0) 
		{
			ostringstream oss;
			oss << stmt + 1 << " " << var << "\n";
			string line = oss.str();
			outputFile << line;
			
			stmt = getParentStmt(stmt);
		}	
	}
	outputFile.close();
}

void Parser::printUses() {
	cout << endl << "List of Uses()" << endl;
	for (size_t i=0; i<uses.size(); i++) {
		int stmt = uses.at(i).first - 1;
		string var = uses.at(i).second;
		while (stmt>=0) {
			cout << "  Uses(" << stmt + 1 << ", " << var << ")" <<endl;
			stmt = getParentStmt(stmt);
		}
	}

	// Write to output file.
	ofstream outputFile;
	outputFile.open (outputFileName, std::ofstream::out | std::ofstream::app);
	outputFile << "Uses Table: \n";
	for (size_t i=0; i<uses.size(); i++) 
	{
		int stmt = uses.at(i).first - 1;
		string var = uses.at(i).second;
		while (stmt>=0) 
		{
			ostringstream oss;
			oss << stmt + 1 << " "  << var << "\n";
			string line = oss.str();
			outputFile << line;
			stmt = getParentStmt(stmt);
		}	
	}
	outputFile.close();
}

/* SUPPORTING FUNCTIONS */

/*
 * Description: this function breaks file data into separate elements (symbols)
 * Input: null
 * Output: vector of all elements
 */
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

/*
 * Description: this function check whether the input string is a number or not
 * Input: string str
 * Output: return true if str is a number; otherwise return false
 */
bool Parser::isNumber(const string str) {
	string::const_iterator it = str.begin();
    while (it != str.end() && isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

/*
 * Description: this function finds the stmt followed
 *				by the given stmt
 * Input: index i of stmt
 * Output: return index of stmt followed by given stmt,
 *		   otherwise return -1
 */
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

/*
 * Description: this function finds the parent stmt
 *				of the given stmt
 * Input: index i of stmt
 * Output: return index of parent stmt of the given stmt,
 *		   otherwise return -1
 */
int Parser::getParentStmt(int i) {
	int lv = depthLv.at(i);
	if (i>0 && lv!=0) {
		for (int j=i-1; j>=0; j--) {
			if (depthLv.at(j)==lv-1) return j;
		}
	}
	return -1;
}

// just for testing
//int main() {
//	Parser p; string fileDirectory;
//	cout<< "Please enter file directory: " ;
//	cin >> fileDirectory;
//	bool isValidDirectory = p.getFileData(fileDirectory);
//	if (isValidDirectory) {
//		//p.printFileData(); 
//		p.getAST();
//		p.printProc();
//		p.printVar();
//		p.printStmtTypes();
//		p.printFollows();
//		p.printParent();
//		p.printModifies();
//		p.printUses();
//	}
//	system("pause");
//}
