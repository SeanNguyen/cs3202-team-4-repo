#ifndef VARTABLE_H_INCLUDED
#define VARTABLE_H_INCLUDED

#include <vector>
#include <string>
using namespace std;

class VarTable
{
private: 
	vector<string> varTable; //why must we use std::
	

public:
	

	//bool isVarName(string varName) { return result }
	//use getVarIndex function 
	//VarTable(){} 
	int insertVar(string name);

	int getVarIndex(string name);

	string getVarName(int index);

	int getSize();

	
};

#endif  