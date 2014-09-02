
#include "Follow.h"


#include <vector>
#include <utility> //pair
#include <iostream>

using namespace std;

Follow followObject;

// Constructor
Follow::Follow(){
	
}

// Method to return if 2 statement number s1 is followed by s2
bool Follow::isFollows(int s1, int s2){

	std::pair<int,int> thisPair = std::make_pair(s1, s2);

	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[i] == thisPair){
			return true;
		}
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

	std::pair<int,int> thisPair = std::make_pair(s1, s2);

	//check if it exists
	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[i] == thisPair){
			return -1;
		}
	}
	followTable.push_back(thisPair);
	return (followTable.size() - 1);
	//return true;
}

// Method to get the following statement to statement number s1
int Follow::getFollowingStmt(int s1){
	
	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[i].first == s1){
			return followTable[i].second;
		}
	}
	return -1;
}

// Method to get statement which is followed by statement s1
int Follow::getFollowedStmt(int s1){

	for(std::size_t i = 0; i < followTable.size(); i++){
		if(followTable[i].second == s1){
			return followTable[i].first;
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
		list.push_back(followTable[i].second);
	}
	return list;
}

//  Method to get statement which is followed stmt
std::vector<int> Follow::getAllFollowedStmt(){
	
	std::vector<int> list;

	for(std::size_t i = 0; i < followTable.size(); i++){
		list.push_back(followTable[i].first);
	}
	return list;
}

//  Method to get statement which is followed star by statement s1
int Follow::getSize(){
	return followTable.size();
}



