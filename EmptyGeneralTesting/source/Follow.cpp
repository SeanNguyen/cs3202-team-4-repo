
#include "Follow.h"


#include <vector>
#include <iostream>

using namespace std;

Follow followObject;

// Constructor
Follow::Follow(){
		MAX_SIZE = 100;
		followTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
}

// Method to return if 2 statement number s1 is followed by s2
bool Follow::isFollows(int s1, int s2){

	//for(int i=0;i<followTable.size(); i++) {
 //     for (int j=0;j<followTable[i].size(); j++)
 //       cout << followTable[i][j] << " "; 
 //     cout << endl;
 //  }
	
	if(Follow::followTable[s1][s2] == 1){
		return true;
	} 
	return false;


}

bool Follow::isFollowsStar(int s1, int s2)
{
	bool isFollowStar = false;
	if (s1 >= 1 && s2 >= 1)
	{
		vector<int> followingStarStmt = getFollowingStarStmt(s1);
		for(size_t index=0; index < followingStarStmt.size(); ++index)
		{
			if (followingStarStmt.at(index) == s2)
			{
				isFollowStar = true;
			}
		}
	}
	return isFollowStar;
}

// Method to insert a pair of following statement numbers
int Follow::insertFollows(int s1, int s2){


	//If the max size (100) if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(followTable.size() > (size_t) MAX_SIZE){
		followTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if(isFollows(s1, s2)){
		return -1;
	} else {
		followTable[s1][s2] = 1;
	}

	return (followTable.size() - 1);
}

// Method to get the following statement to statement number s1
int Follow::getFollowingStmt(int s1){
	
	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[s1][i] == 1){
			return i;
		}
	}
	return -1;
}

// Method to get statement which is followed by statement s1
int Follow::getFollowedStmt(int s1){

	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[i][s1] == 1){
			return i;
		}
	}
	return -1;
}

// private helper function for getFollowingStarStmt.
std::vector<int> Follow::getFollowingStarStmtHelper(int s1, std::vector<int> &accumulated_result)
{	
	if(getFollowingStmt(s1) == -1){
		return accumulated_result;
	}
	std::vector<int> stmtList;
	int value = getFollowingStmt(s1);
	stmtList.push_back(value);

	accumulated_result.insert(accumulated_result.end(), stmtList.begin(), stmtList.end());
	for(size_t index=0; index < stmtList.size(); index++)
	{
		getFollowingStarStmtHelper(stmtList.at(index), accumulated_result);
	}
	return accumulated_result;
}
  
// Method to get the following statement to statement number s1
//assuming there will be inserts like (1, 2), (1, 3) then a list is better.
std::vector<int> Follow::getFollowingStarStmt(int s1){

	std::vector<int> followingStar;
	followingStar = getFollowingStarStmtHelper(s1, followingStar);

	////get the immediate ones first
	//for(std::size_t i = 0; i < followTable.size(); i++){
	//	if(followTable[i].first == s1){
	//		resultlist.push_back(followTable[i].second);
	//		getFollowingStarStmt(followTable[i].second);
	//	}
	//}

	return followingStar;

}

// private helper function for getFollowedStarStmt.
std::vector<int> Follow::getFollowedStarStmtHelper(int s1, std::vector<int> &accumulated_result)
{
	if(getFollowedStmt(s1) == -1){
		return accumulated_result;
	}
	std::vector<int> stmtList;
	int value = getFollowedStmt(s1);
	stmtList.push_back(value);

	accumulated_result.insert(accumulated_result.end(), stmtList.begin(), stmtList.end());
	for(size_t index=0; index < stmtList.size(); index++)
	{
		getFollowedStarStmtHelper(stmtList.at(index), accumulated_result);
	}
	return accumulated_result;
}

//  Method to get statement which is followed star by statement s1
std::vector<int> Follow::getFollowedStarStmt(int s1){

	std::vector<int> followedStar;
	followedStar = getFollowedStarStmtHelper(s1, followedStar);

	//for(std::size_t i = 0; i < followTable.size(); i++){
	//	if(followTable[i].second == s1){
	//		resultlist.push_back(followTable[i].first);
	//		getFollowedStarStmt(followTable[i].first);
	//	}
	//}
	return followedStar;
}

//  Method to get statement which is a following statement 
std::vector<int> Follow::getAllFollowingStmt(){

	std::vector<int> list;

	for(std::size_t i = 0; i < followTable.size(); i++){
		for(std::size_t j = 0; j < followTable[i].size(); j++){
			if(followTable[i][j] == 1){
				list.push_back(j);
			}
		}
	}
	return list;
}

//  Method to get statement which is followed stmt
std::vector<int> Follow::getAllFollowedStmt(){
	
	std::vector<int> list;

	for(std::size_t i = 0; i < followTable.size(); i++){
		for(std::size_t j = 0; j < followTable[i].size(); j++){
			if(followTable[i][j] == 1){
				list.push_back(i);
			}
		}
	}
	return list;
}

//  Method to get number of statements
int Follow::getSize(){
	return followTable.size();
}



