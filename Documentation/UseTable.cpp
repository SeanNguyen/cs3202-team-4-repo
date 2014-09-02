// UseTable.cpp : Defines the entry point for the console application.
#include "UseTable.h"

#include <vector>
#include <utility> //pair
#include <iostream> //debugging

// Constructor
Use::Use(){
	
}

//  Method to check if modifies relationship exists
bool Use::isUses(int s1, int varIndex){

	std::pair<int,int> thisPair = std::make_pair(s1, varIndex);

	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[i] == thisPair){
			return true;
		}
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Use::insertUses(int s1, int varIndex){

	std::pair<int,int> thisPair = std::make_pair(s1, varIndex);

	//check if it exists
	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[i] == thisPair){
			return -1;
		}
	}
	UseTable.push_back(thisPair);
	return (UseTable.size() - 1);
}

//Method to get the variables modified in stmt s1
std::vector<int> Use::getUsedVarAtStmt(int s1){
	vector<int> modifiedVar;
	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[i].first == s1){
			modifiedVar.push_back(UseTable[i].second);
		}
	}
	
	return modifiedVar;
}

// Method to get the list of stmt modifying var
std::vector<int> Use::getStmtUsingVar(int varIndex)
{
	vector<int> modifyStmt;
	for(std::size_t i = 0; i < UseTable.size(); i++){
		if(UseTable[i].second == varIndex){
			modifyStmt.push_back(UseTable[i].first);
		}
	}
	return modifyStmt;
}

//Method to get all statements modifying some variable
std::vector<int> Use::getAllUsingStmt(){
	vector<int> stmt;
	for(std::size_t i = 0; i < UseTable.size(); i++){
		stmt.push_back(UseTable[i].first);
	}

	return stmt;
}

//Method to get all variables being modified 
std::vector<int> Use::getAllUsedVar(){
	vector<int> var;
	for(std::size_t i = 0; i < UseTable.size(); i++){
		var.push_back(UseTable[i].second);
	}

	return var;
}

int Use::getSize()
{
	return UseTable.size();
}

void Use::printTable()
{
	for(size_t index=0; index < UseTable.size(); ++index)
	{
		pair<int, int> thisPair = UseTable.at(index);
		cout << thisPair.first << " " << thisPair.second << endl;
	}
	cout << " " << endl;
}

//Private method to  make a pair of stmt numbers
  //std::pair<int,int> make_pair (int x, int y)
  //{
  //  return ( std::pair<int,int>(x,y) );
  //}