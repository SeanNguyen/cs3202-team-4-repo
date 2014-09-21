#include "ParentTable.h"
#include "Constants.h"
#include <vector>
#include <algorithm>

//extern std::vector<int> OBJECT_NOT_FOUND;
//extern const int MAX_PARENT;

ParentTable::ParentTable()
{
	MAX_SIZE = 100;
	parentTable.resize(MAX_SIZE, std::vector<bool>(MAX_SIZE, false));
}

// method to check whether the tuple(parentStmt, childStmt) is recorded in Parent Table.
bool ParentTable::isParent(int parentStmt, int childStmt)
{
	if(parentTable[parentStmt][childStmt] == 1){
		return true;
	}
	return false;
}

// method to check whether Parent*(parentStmt, childStmt) holds.
// there are 3 cases: parentStmt has no child -> obviously false.
// case 2: parentStmt has children, but childStmt is not in that list -> false.
// case 3: true.
bool ParentTable::isParentStar(int parentStmt, int childStmt)
{
	bool isParentStar = false;
	if (parentStmt >= 1 && childStmt >= 1)
	{
		std::vector<int> childrenStar = getChildStarStmt(parentStmt);
		for (size_t index = 0; index < childrenStar.size(); ++index)
		{
			if (childrenStar.at(index) == childStmt)
			{
				isParentStar = true;
			}
		}
	}
	return isParentStar;
}

// method to insert a tuple(parentStmt, childStmt) to Parent Table if it is not in the table.
// Otherwise, return -1 and the table remains unchanged.
int ParentTable::insertParent(int parentStmt, int childStmt)
{

	//If the max size (100) if the 2d vector is reached, the 2d vector is resized to double its size.
	//The extended set contains all 0 (boolean)
	//Also, update the MAX_SIZE global variable.
	if(parentTable.size() > (size_t) MAX_SIZE){
		parentTable.resize(MAX_SIZE*2, std::vector<bool>(MAX_SIZE, false));
		MAX_SIZE *= 2;
	}

	if (isParent(parentStmt, childStmt))
	{
		return -1;
	}
	else
	{
		parentTable[parentStmt][childStmt] = 1;
		return parentTable.size()-1;
	}
}

// method to get the statement number of parentStmt if tuple(parentStmt, childStmt) exists in the table.
// if childStmt is invalid e.g. -1 or not in the table, return -1.
int ParentTable::getParentStmt(int childStmt)
{
	for(std::size_t i = 0; i < parentTable.size(); i++){
		if(parentTable[i][childStmt] == 1){
			return i;
		}
	}
	return -1;
}

// method to get the list of statement numbers of childStmt if tuple(parentStmt, childStmt) exists in the table.
// if parentStmt is invalid e.g. -1 or not in the table, return special value OBJECT NOT FOUND.
std::vector<int> ParentTable::getChildStmt(int parentStmt)
{
	std::vector<int> children;
	for(std::size_t i = 0; i < parentTable.size(); i++){
		if(parentTable[parentStmt][i] == 1){
			children.push_back(i);
		}
	}
	return children;

}

// method to get direct and indirect children of tuple(parentStmt, -).
// if parentStmt is invalid e.g. -1 or not in the table, return -1.
std::vector<int> ParentTable::getChildStarStmt(int parentStmt)
{
	std::vector<int> childStar;
	childStar = getChildStarStmtHelper(parentStmt, childStar);

	return childStar;
}

// private helper function for getChildStarStmt.
std::vector<int> ParentTable::getChildStarStmtHelper(int parentStmt, std::vector<int> &accumulated_result)
{
	if (getChildStmt(parentStmt).empty()) 
	{
		// do nothing
	}
	else
	{
		std::vector<int> children = getChildStmt(parentStmt);
		accumulated_result.insert(accumulated_result.end(), children.begin(), children.end());
		for(size_t index=0; index < children.size(); index++)
		{
			getChildStarStmtHelper(children.at(index), accumulated_result);
		}
	}
	return accumulated_result;
}

// method to get the list of parent stmts where tuple(parentStmt, childStmt) satisfies Parent*(parentStmt, childStmt).
// if childStmt is invalid e.g. -1 or not in the table, return -1.
std::vector<int> ParentTable::getParentStarStmt(int childStmt)
{
	std::vector<int> parentStar;
	parentStar = getParentStarStmtHelper(childStmt, parentStar);
	if (parentStar.size() == 0)
	{
		return parentStar; //just return empty
	}
	else
	{
		std::sort(parentStar.begin(), parentStar.end());
		return parentStar;
	}
}

// private helper function for getParentStarStmt.
std::vector<int> ParentTable::getParentStarStmtHelper(int childStmt, std::vector<int> &accumulated_result)
{
	if (getChildStmt(childStmt).empty())
	{
		// do nothing
	}
	else
	{
		std::vector<int> result;
		int parent = getParentStmt(childStmt);
		result.push_back(parent);
		accumulated_result.insert(accumulated_result.end(), result.begin(), result.end());
		getParentStarStmtHelper(parent, accumulated_result);
	}
	return accumulated_result;
}

// method to get all the parent stmt that exist in the table.
std::vector<int> ParentTable::getAllParentStmt()
{
	std::vector<int> allParents;
	for(std::size_t i = 0; i < parentTable.size(); i++){
		for(std::size_t j = 0; j < parentTable[i].size(); j++){
			if(parentTable[i][j] == 1){
				allParents.push_back(i);
		}
		}
		
	}
	return allParents;
}

// method to get all the child stmt that exist in the table.
std::vector<int> ParentTable::getAllChildStmt()
{
	std::vector<int> allChildren;
	for(std::size_t i = 0; i < parentTable.size(); i++){
		for(std::size_t j = 0; j < parentTable[i].size(); j++){
			if(parentTable[i][j] == 1){
				allChildren.push_back(j);
			}
		}
		
	}
	return allChildren;
}

int ParentTable::getSize()
{
	return parentTable.size();
}