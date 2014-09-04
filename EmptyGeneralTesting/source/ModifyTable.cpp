#include "ModifyTable.h"

#include <vector>
#include <iostream> //debugging

// Constructor
Modify::Modify(){
	MAX_SIZE = 100;
	ModifyTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE,0));
}

//  Method to check if modifies relationship exists
bool Modify::isModifies(int s1, int varIndex){

	//Just check if that particular element in the 2d vector is 1.
	if(ModifyTable[s1][varIndex] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of stmt number and variable
int Modify::insertModifies(int s1, int varIndex){

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(ModifyTable.size() > (size_t) MAX_SIZE){
		ModifyTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE,0));
		MAX_SIZE *= 2;
	}

	if(isModifies(s1, varIndex)){
		return -1;
	} else {
		ModifyTable[s1][varIndex] = 1;
		return (ModifyTable.size() - 1);
	}
	
}

//Method to get the variables modified in stmt s1
std::vector<int> Modify::getModifiedVarAtStmt(int s1){
	vector<int> modifiedVar;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[s1][i] == 1){
			modifiedVar.push_back(i);
		}
	}
	
	return modifiedVar;
}

// Method to get the list of stmt modifying var
std::vector<int> Modify::getStmtModifyingVar(int varIndex)
{
	vector<int> modifyStmt;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		if(ModifyTable[i][varIndex] == 1){
			modifyStmt.push_back(i);
		}
	}
	return modifyStmt;
}

//Method to get all statements modifying some variable
std::vector<int> Modify::getAllModifyingStmt(){
	vector<int> stmt;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		for(std::size_t j = 0; j < ModifyTable[i].size(); j++){
			if(ModifyTable[i][j] == 1){
				stmt.push_back(i);
			}
		}
	}

	return stmt;
}

//Method to get all variables being modified 
std::vector<int> Modify::getAllModifiedVar(){
	vector<int> var;
	for(std::size_t i = 0; i < ModifyTable.size(); i++){
		for(std::size_t j = 0; j < ModifyTable[i].size(); j++){
			if(ModifyTable[i][j] == 1){
				var.push_back(j);
			}
		}
	}

	return var;
}

int Modify::getSize()
{
	return ModifyTable.size();
}

//void Modify::printTable()
//{
//	for( i=0;i<ModifyTable.size(); i++) {
//      for (int j=0;j<ModifyTable[i].size(); j++)
//        cout << ModifyTable[i][j] << " "; 
//      cout << " " << endl;
//   }
//	
//}