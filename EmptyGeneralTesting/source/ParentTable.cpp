#include "ParentTable.h"
#include "Constants.h"
#include <algorithm>
#include <vector>
#include <iostream>

extern std::vector<int> OBJECT_NOT_FOUND;
extern const int MAX_PARENT;

ParentTable::ParentTable()
{
	for(int i = 0; i < MAX_PARENT; i++)
	{
		hasChild[i] = 0;
	}

	for(int i = 0; i < MAX_PARENT; i++)
	{
		hasParent[i] = 0;
	}
}

// method to check whether the tuple(parentStmt, childStmt) is recorded in Parent Table.
bool ParentTable::isParent(int parentStmt, int childStmt)
{
	bool isParent = false;

	std::pair<int, int> thisPair = std::make_pair(parentStmt, childStmt);
	for(size_t index=0; index < parentTable.size(); index++)
	{
		std::pair<int, int> p = parentTable.at(index);
		if(p.first == thisPair.first && p.second == thisPair.second)
		{
			return true;
		}
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
	if (isParent(parentStmt, childStmt))
	{
		return -1;
	}
	else
	{
		std::pair<int, int> newPair = std::make_pair(parentStmt, childStmt);

		parentTable.push_back(newPair);

		//update hasChild
		hasChild[parentStmt-1] = 1;
		hasParent[childStmt-1] = 1;
		return parentTable.size()-1;
	}
}

// method to get the statement number of parentStmt if tuple(parentStmt, childStmt) exists in the table.
// if childStmt is invalid e.g. -1 or not in the table, return -1.
int ParentTable::getParentStmt(int childStmt)
{
	int parentStmt = -1;
	for(size_t index=0; index < parentTable.size(); index++)
	{
		//PTuple t = parentTable.at(index);
		std::pair<int, int> thisPair = parentTable.at(index);
		
		if (thisPair.second == childStmt)
		{
			parentStmt = thisPair.first;
		}
	}
	return parentStmt;
}

// method to get the list of statement numbers of childStmt if tuple(parentStmt, childStmt) exists in the table.
// if parentStmt is invalid e.g. -1 or not in the table, return special value OBJECT NOT FOUND.
std::vector<int> ParentTable::getChildStmt(int parentStmt)
{
	std::vector<int> children;
	for (size_t index=0; index < parentTable.size(); index++)
	{
		//PTuple t = parentTable.at(index);
		std::pair<int, int> thisPair = parentTable.at(index);
		if (thisPair.first == parentStmt)
		{
			children.push_back(thisPair.second);
		}
	}

	if (children.size() == 0)
	{
		return OBJECT_NOT_FOUND;
	}
	else
	{
		return children;
	}


}

// method to get direct and indirect children of tuple(parentStmt, -).
// if parentStmt is invalid e.g. -1 or not in the table, return -1.
std::vector<int> ParentTable::getChildStarStmt(int parentStmt)
{
	std::vector<int> childrenStar;

	childrenStar = getChildStarStmtHelper(parentStmt, childrenStar);
	if (childrenStar.size() == 0)
	{
		return OBJECT_NOT_FOUND;
	}
	else
	{
		std::sort(childrenStar.begin(), childrenStar.end());
		return childrenStar;
	}
}

// private helper function for getChildStarStmt.
std::vector<int> ParentTable::getChildStarStmtHelper(int parentStmt, std::vector<int> &accumulated_result)
{
	if (hasChild[parentStmt-1] == 0) // a leaf
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
		return OBJECT_NOT_FOUND;
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
	if (hasParent[childStmt-1]==0)
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
	for(size_t index=0; index < parentTable.size(); index++)
	{
		allParents.push_back(parentTable.at(index).first);
	}
	return allParents;
}

// method to get all the child stmt that exist in the table.
std::vector<int> ParentTable::getAllChildStmt()
{
	std::vector<int> allChildren;
	for(size_t index=0; index < parentTable.size(); index++)
	{
		allChildren.push_back(parentTable.at(index).second);
	}
	return allChildren;
}

int ParentTable::getSize()
{
	return parentTable.size();
}