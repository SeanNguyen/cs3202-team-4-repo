#include "QueryRanker.h"

QueryRanker::QueryRanker() {}

QueryRanker::~QueryRanker() {}

void QueryRanker::RankQueries() {
	int size = QueryRepresentator::getSize();
	for (int i=0; i<size; i++) {
		RankQuery(i);
	}
	return;
}

void QueryRanker::RankQuery(int index) {
	SymbolTable table = QueryRepresentator::getSymbolTable(index);
	Tree tree = QueryRepresentator::getQueryTree(index);

	vector<int> occurences = calcSymbolOccurences(table, tree);
	//QueryRepresentator::sortTable(index, occurences);
}

vector<int> QueryRanker::calcSymbolOccurences(SymbolTable table, Tree tree) {
	vector<int> result;
	int size = table.getSize();
	for (int i=0; i<size; i++) {
		string name = table.getName(i);
		int count = tree.countNode(QuerySymbol, name);
		result.push_back(count);
	}

	return result;
}