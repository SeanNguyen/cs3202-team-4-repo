#ifndef Use_h
#define Use_h

#include <vector>
#include <utility>
#include <iostream>

using namespace std;
class Use
{
public :

	vector<vector<bool>> UseTable;
	vector<vector<bool>> UseTableProc;

	// Constructor
	Use();  
  
	// Method to check if uses relationship exists
	bool isUses(int s1, int varIndex);
  
	// Method to insert a pair of following stmt number and variable
	int insertUses(int s1, int varIndex);

	// Method to get the variables used in stmt s1
	std::vector<int> getUsedVarAtStmt(int s1);

	// Method to get the list of stmt using var
	std::vector<int> getStmtUsingVar(int varIndex);


	///NEW METHODS///

	// Method to check if uses relationship exists
	bool isUsesProc(int proc1, int varIndex);
  
	// Method to insert a pair of uses proc number and variable
	int insertUsesProc(int proc1, int varIndex);

	// Method to get the variables used in proc proc1
	std::vector<int> getUsedVarAtProc(int proc1);

	// Method to get the list of proc using var
	std::vector<int> getProcUsingVar(int varIndex);

	//Method to get all statements using some variable
	//std::vector<int> getAllUsingStmt();

	////Method to get all variables being used 
	//std::vector<int> getAllUsedVar();

	////Method to get the number of records in the table.
	//int getSize();

	//Method for debugging - will be removed when submit.
	//void printTable();

private:
	int MAX_SIZE;
};
#endif
