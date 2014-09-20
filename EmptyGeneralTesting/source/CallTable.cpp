#include "CallTable.h"

#include <vector>
#include <iostream> //debugging

// Constructor
Call::Call(){
	MAX_SIZE = 100;
	callTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
}

//  Method to check if calls relationship exists
bool Call::isCalls(int proc1, int proc2){

	//Just check if that particular element in the 2d vector is 1.
	if(callTable[proc1][proc2] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of proc
int Call::insertCalls(int proc1, int proc2){

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(callTable.size() > (size_t) MAX_SIZE){
		callTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE,false));
		MAX_SIZE *= 2;
	}

	if(isCalls(proc1, proc2)){
		return -1;
	} else {
		callTable[proc1][proc2] = 1;
		return (callTable.size() - 1);
	}
	
}

bool Call::isCallStar(int proc1, int proc2){
	
	bool isCallStar = false;
	if (proc1 >= 1 && proc2 >= 1)
	{
		vector<int> callingStarProc = getCallingStarProc(proc2);
		for(size_t index=0; index < callingStarProc.size(); index++)
		{
			if (callingStarProc.at(index) == proc1)
			{
				isCallStar = true;
			}
		}
	}
	return isCallStar;
}

// private helper function for getCallingStarStmt.
std::vector<int> Call::getCallingStarProcHelper(int proc1, std::vector<int> &accumulated_result)
{	
	if(getCallingProc(proc1).empty()){
		return accumulated_result;
	}
	std::vector<int> procList = getCallingProc(proc1);

	accumulated_result.insert(accumulated_result.end(), procList.begin(), procList.end());
	for(size_t index=0; index < procList.size(); index++)
	{
		getCallingStarProcHelper(procList.at(index), accumulated_result);
	}
	return accumulated_result;
}

// private helper function for getCalledByStarStmt.
std::vector<int> Call::getCalledByStarProcHelper(int proc1, std::vector<int> &accumulated_result)
{	
	if(getCalledByProc(proc1).empty()){
		return accumulated_result;
	}
	std::vector<int> procList = getCalledByProc(proc1);

	accumulated_result.insert(accumulated_result.end(), procList.begin(), procList.end());
	for(size_t index=0; index < procList.size(); index++)
	{
		getCalledByStarProcHelper(procList.at(index), accumulated_result);
	}
	return accumulated_result;
}
  
// Method to get the following statement to statement number s1
//assuming there will be inserts like (1, 2), (1, 3) then a list is better.
std::vector<int> Call::getCallingStarProc(int proc1){

	std::vector<int> callingStar;
	callingStar = getCallingStarProcHelper(proc1, callingStar);

	return callingStar;

}

std::vector<int> Call::getCalledByStarProc(int proc1){
	std::vector<int> calledByStar;
	calledByStar = getCalledByStarProcHelper(proc1, calledByStar);
	return calledByStar;
}

//Method to get the proc called in proc1
std::vector<int> Call::getCalledByProc(int proc1){
	vector<int> calledProc;
	for(std::size_t i = 0; i < callTable.size(); i++){
		if(callTable[proc1][i] == 1){
			calledProc.push_back(i);
		}
	}
	
	return calledProc;
}

// Method to get the list of proc calling proc1
std::vector<int> Call::getCallingProc(int proc1)
{
	vector<int> callingProc;
	for(std::size_t i = 0; i < callTable.size(); i++){
		if(callTable[i][proc1] == 1){
			callingProc.push_back(i);
		}
	}
	return callingProc;
}

//Method to get all statements modifying some variable
//std::vector<int> Call::getAllCallingProc(){
//	vector<int> procList;
//	for(std::size_t i = 0; i < callTable.size(); i++){
//		for(std::size_t j = 0; j < callTable[i].size(); j++){
//			if(callTable[i][j] == 1){
//				procList.push_back(i);
//			}
//		}
//	}
//
//	return procList;
//}
//
////Method to get all variables being modified 
//std::vector<int> Call::getAllCalledProc(){
//	vector<int> procList;
//	for(std::size_t i = 0; i < callTable.size(); i++){
//		for(std::size_t j = 0; j < callTable[i].size(); j++){
//			if(callTable[i][j] == 1){
//				procList.push_back(j);
//			}
//		}
//	}
//
//	return procList;
//}

//void Modify::printTable()
//{
//	for( i=0;i<ModifyTable.size(); i++) {
//      for (int j=0;j<ModifyTable[i].size(); j++)
//        cout << ModifyTable[i][j] << " "; 
//      cout << " " << endl;
//   }
//	
//}