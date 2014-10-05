#ifndef Modify_h
#define Modify_h

#include <vector>
#include <utility>
#include <iostream>

using namespace std;



class Modify
{
public :

	std::vector<std::vector<bool>> ModifyTable;
	std::vector<std::vector<bool>> ModifyProcVarTable;
	

	// Constructor
	Modify();  
  
	// Method to check if modifies relationship exists
	bool isModifies(int s1, int varIndex);

	// Method to check if modifies relationship exists
	bool isModifiesProc(int proc1, int varIndex);               // <---NEW
  
	// Method to insert a pair of modifying stmt number and variable
	int insertModifies(int s1, int varIndex);

	//Method to insert a pair of modifying proc number and variable
	int insertModifiesProc(int proc1, int varIndex);                // <---NEW

	// Method to get the variables modified in stmt s1
	std::vector<int> getModifiedVarAtStmt(int s1);

	// Method to get the variables modified in proc proc1
	std::vector<int> getModifiedVarAtProc(int proc1);             // <---NEW       

	// Method to get the list of stmt modifying var
	std::vector<int> getStmtModifyingVar(int varIndex);

	// Method to get the list of proc modifying var
	std::vector<int> getProcModifyingVar(int varIndex);              // <---NEW   

	//Method to get all statements modifying some variable
	//std::vector<int> getAllModifyingStmt();

	//Method to get all variables being modified 
	//std::vector<int> getAllModifiedVar();

	//Method to get the number of records in the table.
	//int getSize();

	//Method for debugging - will be removed when submit.
	//void printTable();

private:
	std::vector<int> stmtlist;
	std::vector<int> varlist;
	int MAX_SIZE;
};
#endif
