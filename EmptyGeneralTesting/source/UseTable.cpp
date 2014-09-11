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

	if(UseTable[s1][varIndex] == 1){
		return true;
	}
	return false;
}

bool Use::isUsesProc(int proc1, int varIndex){
	
	if(UseTableProc[proc1][varIndex] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Use::insertUses(int s1, int varIndex){

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
	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[s1][i] == 1){
			usedVar.push_back(i);
		}
	}
	
	return usedVar;
}

std::vector<int> Use::getUsedVarAtProc(int proc1){
	vector<int> usedVar;
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
	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTableProc[i][varIndex] == 1){
			useProc.push_back(i);
		}
	}
	return useProc;
}
//
////Method to get all statements modifying some variable
//std::vector<int> Use::getAllUsingStmt(){
//	vector<int> stmt;
//	for(std::size_t i = 0; i < UseTable.size(); i++){
//		for(std::size_t j = 0; j < UseTable[i].size(); j++){
//			if(UseTable[i][j] == 1){
//				stmt.push_back(i);
//			}
//		}
//	}
//
//	return stmt;
//}
//
////Method to get all variables being modified 
//std::vector<int> Use::getAllUsedVar(){
//	vector<int> var;
//	for(std::size_t i = 0; i < UseTable.size(); i++){
//		for(std::size_t j = 0; j < UseTable[i].size(); j++){
//			if(UseTable[i][j] == 1){
//				var.push_back(j);
//			}
//		}
//	}
//
//	return var;
//}
//
//int Use::getSize()
//{
//	return UseTable.size();
//}

//void Use::printTable()
//{
//	for(size_t index=0; index < UseTable.size(); ++index)
//	{
//		pair<int, int> thisPair = UseTable.at(index);
//		cout << thisPair.first << " " << thisPair.second << endl;
//	}
//	cout << " " << endl;
//}

//Private method to  make a pair of stmt numbers
  //std::pair<int,int> make_pair (int x, int y)
  //{
  //  return ( std::pair<int,int>(x,y) );
  //}