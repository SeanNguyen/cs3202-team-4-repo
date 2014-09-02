#ifndef Follow_h
#define Follow_h

#include <vector>
#include <utility>
#include <iostream>

class Follow
{
	public :

		std::vector<std::pair<int, int>> followTable;
		std::vector<int> resultlist;

		// Constructor
		Follow();  
  
		// Method to return if 2 statement number s1 is followed by s2
		bool isFollows(int s1, int s2);

		bool isFollowsStar(int s1, int s2);
  
		// Method to insert a pair of following statement numbers
		int insertFollows(int s1, int s2);

		// Method to get the following statement to statement number s1
		int getFollowingStmt(int s1);

		// Method to get statement which is followed by statement s1
		int getFollowedStmt(int s1);
  
		// Method to get the following statement to statement number s1
		std::vector<int> getFollowingStarStmt(int s1);

		//  Method to get statement which is followed star by statement s1
		std::vector<int> getFollowedStarStmt(int s1);

		//  Method to get statement which is followed star by statement s1
		std::vector<int> getAllFollowingStmt();

		//  Method to get statement which is followed star by statement s1
		std::vector<int> getAllFollowedStmt();

		//  Method to get statement which is followed star by statement s1
		int getSize();

	private:
		std::vector<int> getFollowedStarStmtHelper(int s1, std::vector<int> &accumulated_result);
		std::vector<int> getFollowingStarStmtHelper(int s1, std::vector<int> &accumulated_result);

};
#endif
