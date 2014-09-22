#include "NextTable.h"

#include <vector>
#include <iostream> //debugging

// Constructor
Next::Next(){
	MAX_SIZE = 100;
	nextTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
}

// Method to check if next relationship exists
bool Next::isNext(int n1, int n2){

	//Just check if that particular element in the 2d vector is 1.
	if(nextTable[n1][n2] == 1){
		return true;
	}
	return false;
}

// Method to insert a pair of line numbers
int Next::insertNext(int n1, int n2){

	//If the max size if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(nextTable.size() > (size_t) MAX_SIZE){
		nextTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE,false));
		MAX_SIZE *= 2;
	}

	if(isNext(n1, n2)){
		return -1;
	} else {
		nextTable[n1][n2] = 1;
		return (nextTable.size() - 1);
	}
	
}

//bool Next::isCallStar(int proc1, int proc2){
//	
//	bool isCallStar = false;
//	if (proc1 >= 1 && proc2 >= 1)
//	{
//		vector<int> callingStarProc = getCallingStarProc(proc2);
//		for(size_t index=0; index < callingStarProc.size(); index++)
//		{
//			if (callingStarProc.at(index) == proc1)
//			{
//				isCallStar = true;
//			}
//		}
//	}
//	return isCallStar;
//}

// private helper function for getCallingStarStmt.
//std::vector<int> Call::getCallingStarProcHelper(int proc1, std::vector<int> &accumulated_result)
//{	
//	if(getCallingProc(proc1).empty()){
//		return accumulated_result;
//	}
//	std::vector<int> procList = getCallingProc(proc1);
//
//	accumulated_result.insert(accumulated_result.end(), procList.begin(), procList.end());
//	for(size_t index=0; index < procList.size(); index++)
//	{
//		getCallingStarProcHelper(procList.at(index), accumulated_result);
//	}
//	return accumulated_result;
//}
//
//// private helper function for getCalledByStarStmt.
//std::vector<int> Call::getCalledByStarProcHelper(int proc1, std::vector<int> &accumulated_result)
//{	
//	if(getCalledByProc(proc1).empty()){
//		return accumulated_result;
//	}
//	std::vector<int> procList = getCalledByProc(proc1);
//
//	accumulated_result.insert(accumulated_result.end(), procList.begin(), procList.end());
//	for(size_t index=0; index < procList.size(); index++)
//	{
//		getCalledByStarProcHelper(procList.at(index), accumulated_result);
//	}
//	return accumulated_result;
//}
//  
//// Method to get the following statement to statement number s1
////assuming there will be inserts like (1, 2), (1, 3) then a list is better.
//std::vector<int> Call::getCallingStarProc(int proc1){
//
//	std::vector<int> callingStar;
//	callingStar = getCallingStarProcHelper(proc1, callingStar);
//
//	return callingStar;
//
//}
//
//std::vector<int> Call::getCalledByStarProc(int proc1){
//	std::vector<int> calledByStar;
//	calledByStar = getCalledByStarProcHelper(proc1, calledByStar);
//	return calledByStar;
//}

// Method to get the list of line numbers next to n1
std::vector<int> Next::getNextOneLine(int n1){
	vector<int> nextLines;
	for(std::size_t i = 0; i < nextTable.size(); i++){
		if(nextTable[n1][i] == 1){
			nextLines.push_back(i);
		}
	}
	
	return nextLines;
}

// Method to get the list of proc calling proc1
std::vector<int> Next::getNextTwoLine(int n1)
{
	vector<int> nextLines;
	for(std::size_t i = 0; i < nextTable.size(); i++){
		if(nextTable[i][n1] == 1){
			nextLines.push_back(i);
		}
	}
	return nextLines;
}
