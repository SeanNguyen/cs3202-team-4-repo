#pragma once

#include "QueryRepresentator.h"

class QueryRanker {
public:
	QueryRanker();
	~QueryRanker();
	void RankQueries();
private:
	void RankQuery(int index);
	vector<int> calcSymbolOccurences(SymbolTable table, Tree tree);
};