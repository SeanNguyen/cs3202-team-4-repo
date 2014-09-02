/*
 * ParentTable is for storing Parent(parentStmt, childStmt) in the program; and computing Parent* relationship.
 * Things to do for next semester: replacing PTuple by pair in <utility> - less prone to error.
 */
#pragma once
#ifndef Parent_h
#define Parent_h

#include <string>
#include <vector>

//const int MAX_PARENT = 10000;
//
//struct PTuple
//{
//	int parent;
//	int child;
//};

		
		//std::vector<int> resultlist;

class ParentTable
{
	public:

		std::vector<std::vector<bool>> parentTable;

		// Default constructor
		ParentTable();

		bool isParent(int parentStmt, int childStmt);

		bool isParentStar(int parentStmt, int childStmt);

		int insertParent(int parentStmt, int childStmt);

		int getParentStmt(int childStmt);

		std::vector<int> getChildStmt(int parentStmt);

		std::vector<int> getParentStarStmt(int childStmt);

		std::vector<int> getChildStarStmt(int parentStmt);

		std::vector<int> getAllParentStmt();

		std::vector<int> getAllChildStmt();

		// method to get the size of the table.
		int getSize();

	private:
		// parent[i] is the parent stmt of child[i]
		/*std::vector<PTuple> parentTable;*/

		// auxilary data structures supporting for STAR functions.
		// it checks whether a particular stmt i has child or parent.
		//int hasChild[MAX_PARENT];
		//int hasParent[MAX_PARENT];
		std::vector<int> getChildStarStmtHelper(int parentStmt, std::vector<int> &accumulated_result);
		std::vector<int> getParentStarStmtHelper(int childStmt, std::vector<int> &accumulated_result);
		int MAX_SIZE;
		
};
#endif
