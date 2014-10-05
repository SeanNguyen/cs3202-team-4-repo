#include "ModifyTable.h"

#include <vector>
#include <iostream> //debugging

// Constructor
Modify::Modify(){
	MAX_SIZE = 100;
	ModifyTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE,false));
	ModifyProcVarTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE,false));
}

//  Method to check if modifies relationship exists
bool Modify::isModifies(int s1, int varIndex){

	if(s1 < 0 || varIndex < 0){
		return false;
	}

	//Just check if that particular element in the 2d vector is 1.
	if(ModifyTable[s1][varIndex] == 1){
		return true;
	}
	return false;
}

//  Method to check if modifies relationship exists
bool Modify::isModifiesProc(int proc1, int varIndex){

	if(proc1 < 0 || varIndex < 0){
		return false;
	}

	//Just check if that particular element in the 2d vector is 1.
	if(ModifyProcVarTable[proc1][varIndex] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Modify::insertModifies(int s1, int varIndex){

	if(s1 < 0 || varIndex < 0){
		return -1;
	}

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(ModifyTable.size() > (size_t) MAX_SIZE){
		ModifyTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if(isModifies(s1, varIndex)){
		return -1;
	} else {
		ModifyTable[s1][varIndex] = 1;
		return (ModifyTable.size() - 1);
	}
	
}

// Method to insert a pair of proc number and variable
int Modify::insertModifiesProc(int proc1, int varIndex){

	if(proc1 < 0 || varIndex < 0){
		return -1;
	}

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(ModifyProcVarTable.size() > (size_t) MAX_SIZE){
		ModifyProcVarTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if(isModifiesProc(proc1, varIndex)){
		return -1;
	} else {
		ModifyProcVarTable[proc1][varIndex] = 1;
		return (ModifyProcVarTable.size() - 1);
	}
	
}

//Method to get the variables modified in stmt s1
std::vector<int> Modify::getModifiedVarAtStmt(int s1){
	vector<int> modifiedVar;

	if(s1 < 0){
		return modifiedVar;
	}

	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[s1][i] == 1){
			modifiedVar.push_back(i);
		}
	}
	
	return modifiedVar;
}

//Method to get the variables modified in proc proc1
std::vector<int> Modify::getModifiedVarAtProc(int proc1){
	vector<int> modifiedVar;

	if(proc1 < 0){
		return modifiedVar;
	}

	for(std::size_t i = 0; i < ModifyProcVarTable.size(); i++){
		if(ModifyProcVarTable[proc1][i] == 1){
			modifiedVar.push_back(i);
		}
	}
	
	return modifiedVar;
}

// Method to get the list of stmt modifying var
std::vector<int> Modify::getStmtModifyingVar(int varIndex)
{
	vector<int> modifyStmt;

	if(varIndex < 0){
		return modifyStmt;
	}

	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i][varIndex] == 1){
			modifyStmt.push_back(i);
		}
	}
	return modifyStmt;
}

// Method to get the list of proc modifying var
std::vector<int> Modify::getProcModifyingVar(int varIndex)
{
	vector<int> modifyProc;

	if(varIndex < 0){
		return modifyProc;
	}

	for(std::size_t i = 0; i < ModifyProcVarTable.size(); i++){
		if(ModifyProcVarTable[i][varIndex] == 1){
			modifyProc.push_back(i);
		}
	}
	return modifyProc;
}
