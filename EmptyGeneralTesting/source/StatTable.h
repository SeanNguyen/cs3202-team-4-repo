#ifndef STATTABLE_H_INCLUDED
#define STATTABLE_H_INCLUDED

#include <vector>
#include <string>
using namespace std;

class StatTable
{
private: 
	vector<string> statTable; //why must we use std::
	

public:
	

	//bool isVarName(string varName) { return result }
	//use getVarIndex function 
	//VarTable(){} 
	int insertStmt(string name);

	vector<int> getStmtIndex(string name);
	string getStmtName(int index);
	int getSize();
	
};

#endif