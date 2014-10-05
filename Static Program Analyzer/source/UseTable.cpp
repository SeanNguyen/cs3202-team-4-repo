// UseTable.cpp : Defines the entry point for the console application.
#include "UseTable.h"

#include <vector>
#include <iostream> //debugging

// Constructor
Use::Use(){
	MAX_SIZE = 100;
	UseTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
	UseTableProc.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
}

//  Method to check if modifies relationship exists
bool Use::isUses(int s1, int varIndex){

	if(s1 < 0 || varIndex < 0){
		return false;
	}

	if(UseTable[s1][varIndex] == 1){
		return true;
	}
	return false;
}

bool Use::isUsesProc(int proc1, int varIndex){

	if(proc1 < 0 || varIndex < 0){
		return false;
	}
	
	if(UseTableProc[proc1][varIndex] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Use::insertUses(int s1, int varIndex){

	if(s1 < 0 || varIndex < 0){
		return false;
	}

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(UseTable.size() > (size_t) MAX_SIZE){
		UseTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if(UseTable[s1][varIndex] == 0){
		UseTable[s1][varIndex] = 1;
	} 
	return UseTable.size();
}

int Use::insertUsesProc(int proc1, int varIndex){

	if(proc1 < 0 || varIndex < 0){
		return -1;
	}

		//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(UseTableProc.size() > (size_t) MAX_SIZE){
		UseTableProc.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if(UseTableProc[proc1][varIndex] == 0){
		UseTableProc[proc1][varIndex] = 1;
	} 
	return UseTable.size();
}

//Method to get the variables modified in stmt s1
std::vector<int> Use::getUsedVarAtStmt(int s1){
	vector<int> usedVar;

	if(s1 < 0){
		return usedVar;
	}

	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[s1][i] == 1){
			usedVar.push_back(i);
		}
	}
	
	return usedVar;
}

std::vector<int> Use::getUsedVarAtProc(int proc1){
	vector<int> usedVar;

	if(proc1 < 0){
		return usedVar;
	}

	for(std::size_t i = 0; i < UseTableProc.size(); i++){
		if(UseTableProc[proc1][i] == 1){
			usedVar.push_back(i);
		}
	}
	
	return usedVar;
}

// Method to get the list of stmt modifying var
std::vector<int> Use::getStmtUsingVar(int varIndex)
{
	vector<int> useStmt;

	if(varIndex < 0){
		return useStmt;
	}

	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[i][varIndex] == 1){
			useStmt.push_back(i);
		}
	}
	return useStmt;
}


std::vector<int> Use::getProcUsingVar(int varIndex)
{
	vector<int> useProc;

	if(varIndex < 0){
		return useProc;
	}

	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTableProc[i][varIndex] == 1){
			useProc.push_back(i);
		}
	}
	return useProc;
}
