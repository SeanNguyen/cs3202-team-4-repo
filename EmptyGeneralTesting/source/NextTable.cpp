#include "NextTable.h"
#include <algorithm>
#include <vector>

int Next::insertNext(int stmt1, int stmt2){
	if(isNext(stmt1, stmt2)){
		return -1;
	} else {
		this->mapNext[stmt1].push_back(stmt2);
		this->mapPrevious[stmt2].push_back(stmt1);
		return (stmt1);
	}
	
}

bool Next::isNext(int stmt1, int stmt2){
	vector <int> n1NextStmts = this->mapNext[stmt1];
	bool searchResult = std::find(n1NextStmts.begin(), n1NextStmts.end(), stmt2) != n1NextStmts.end();
	return searchResult;
}

bool Next::isNextStar (int stmt1, int stmt2) {
	vector <int> nextStmts = this->mapNext[stmt1];
	if (isNext(stmt1, stmt2))
		return true;
	//apply depth first search here
	for (size_t i = 0; i < this->mapNext[stmt1].size(); i++) {
		if (isNextStar(nextStmts[i], stmt2))
			return true;
	}
	return false;
}

vector<int> Next::getNextStmts(int stmtNo){
	return this->mapNext[stmtNo];
}

vector<int> Next::getNextStarStmts(int stmtNo){
	vector <int> result = this->mapNext[stmtNo];
	for (size_t i = 0; i < this->mapNext[stmtNo].size(); i++) {
		vector <int> nextStarOfNextStmt = getNextStarStmts(this->mapNext[stmtNo].at(i));
		result.insert (result.end(), nextStarOfNextStmt.begin(), nextStarOfNextStmt.end());
	}
	return result;
}

vector<int> Next::getPreviousStmts(int stmtNo){
	return this->mapPrevious[stmtNo];
}

vector<int> Next::getPreviousStarStmts(int stmtNo){
	vector <int> result = this->mapPrevious[stmtNo];
	for (size_t i = 0; i < this->mapPrevious[stmtNo].size(); i++) {
		vector <int> previousStarOfNextStmt = getPreviousStarStmts(this->mapPrevious[stmtNo].at(i));
		result.insert (result.end(), previousStarOfNextStmt.begin(), previousStarOfNextStmt.end());
	}
	return result;
}
