#ifndef Call_h
#define Call_h

#include <vector>
#include <utility>
#include <iostream>

using namespace std;



class Call
{
public :

	std::vector<std::vector<bool>> callTable;
	

	// Constructor
	Call();  
  
	// Method to check if calls relationship exists
	bool isCalls(int proc1, int proc2);
  
	// Method to insert a pair of proc
	int insertCalls(int proc1, int proc2);

	// Method to get the list of proc called by proc1
	std::vector<int> getCalledByProc(int proc1);

	// Method to get the list of proc calling proc1
	std::vector<int> getCallingProc(int proc1);

	//Method to get all calling Proc
	std::vector<int> getAllCallingProc();

	//Method to get all proc being called
	std::vector<int> getAllCalledProc();

	//Method to get the number of records in the table.
	int getSize();

	//Method for debugging - will be removed when submit.
	//void printTable();

private:
	std::vector<int> proclist;
	int MAX_SIZE;
};
#endif
