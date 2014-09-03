#include "ModifyTable.h"

#include <vector>
#include <utility> //pair
#include <iostream> //debugging

// Constructor
Modify::Modify(){
	
}

//  Method to check if modifies relationship exists
bool Modify::isModifies(int s1, int varIndex){

	std::pair<int,int> thisPair = std::make_pair(s1, varIndex);

	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i] == thisPair){
			return true;
		}
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Modify::insertModifies(int s1, int varIndex){

	std::pair<int,int> thisPair = std::make_pair(s1, varIndex);

	//check if it exists
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i] == thisPair){
			return -1;
		}
	}
	ModifyTable.push_back(thisPair);
	return (ModifyTable.size() - 1);
}

//Method to get the variables modified in stmt s1
std::vector<int> Modify::getModifiedVarAtStmt(int s1){
	vector<int> modifiedVar;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i].first == s1){
			modifiedVar.push_back(ModifyTable[i].second);
		}
	}
	
	return modifiedVar;
}

// Method to get the list of stmt modifying var
std::vector<int> Modify::getStmtModifyingVar(int varIndex)
{
	vector<int> modifyStmt;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i].second == varIndex){
			modifyStmt.push_back(ModifyTable[i].first);
		}
	}
	return modifyStmt;
}

//Method to get all statements modifying some variable
std::vector<int> Modify::getAllModifyingStmt(){
	vector<int> stmt;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		stmt.push_back(ModifyTable[i].first);
	}

	return stmt;
}

//Method to get all variables being modified 
std::vector<int> Modify::getAllModifiedVar(){
	vector<int> var;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		var.push_back(ModifyTable[i].second);
	}

	return var;
}

//Private method to  make a pair of stmt numbers
  //std::pair<int,int> make_pair (int x, int y)
  //{
  //  return ( std::pair<int,int>(x,y) );
  //}

int Modify::getSize()
{
	return ModifyTable.size();
}

void Modify::printTable()
{
	for(size_t index=0; index < ModifyTable.size(); ++index)
	{
		pair<int, int> thisPair = ModifyTable.at(index);
		cout << thisPair.first << " " << thisPair.second << endl;
	}
	cout << " " << endl;
}