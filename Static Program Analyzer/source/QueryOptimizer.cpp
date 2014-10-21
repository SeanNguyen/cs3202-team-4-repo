#include "QueryOptimizer.h"

void QueryOptimizer::optimizeQuery(SymbolTable & table, QueryTree & tree, vector<int> & count) {
	sortTable(table, count);
	sortTree(tree, table);
}

void QueryOptimizer::sortTable(SymbolTable & table, vector<int> & count) {
	SymbolTable sort_table;
	vector<int> sort_count = count;
	int size = table.getSize();

	table = sortTable(table, count, 0, size-1);
	for (size_t i=0; i<table.getSize(); i++) {
		string name = table.getName(i);
	}
}

void QueryOptimizer::sortTree(QueryTree & tree, SymbolTable & table) {
	TNode * root = tree.getRoot();
	int size = root ->getNumChildren();
	for (int i=0; i<size; i++) {
		TNode * node = root ->getChildAtIndex(i);
		rankNode(node, table);
	}

	root -> sortChildrenList();
}

SymbolTable QueryOptimizer::sortTable(SymbolTable table, vector<int> & count, int start, int end) {
	if (end <= start) {
		return table;
	}
	int mid = (start+end)/2;
	SymbolTable t1 = sortTable(table, count, start, mid);
	SymbolTable t2 = sortTable(table, count, mid+1, end);
	return mergeTable(t1, t2, count, start, mid, end);
}

SymbolTable  QueryOptimizer::mergeTable(SymbolTable t1, SymbolTable t2, vector<int> & count,
										int start, int mid, int end) {
	SymbolTable table;
	vector<int> new_count;
	int size = count.size();

	for (int i=0; i<start; i++) {
		string name = t1.getName(i);
		string type = t1.getType(name);
		table.setSymbol(type, name);
		new_count.push_back(count[i]);
	}

	int i = start; int j = mid+1;
	string name = ""; string type = "";
	while(i<=mid && j<=end) {
		if (count[i]>count[j]) {
			name = t1.getName(i);
			type = t1.getType(name);
			new_count.push_back(count[i]);
			i++; 
		} else {
			name = t2.getName(j);
			type = t2.getType(name);
			new_count.push_back(count[j]);
			j++;
		}
		table.setSymbol(type, name);
	}

	while (i<=mid) {
		name = t1.getName(i);
		type = t1.getType(name);
		new_count.push_back(count[i]);
		table.setSymbol(type, name);
		i++;
	}


	while (j<=end) {
		name = t2.getName(j);
		type = t2.getType(name);
		new_count.push_back(count[j]); 
		table.setSymbol(type, name);
		j++;
	}

	for (int i=end+1; i<size; i++) {
		string name = t2.getName(i);
		string type = t2.getType(name);
		table.setSymbol(type, name);
		new_count.push_back(count[i]);
	}

	count = new_count;
	return table;
}

void QueryOptimizer::rankNode(TNode * node, SymbolTable & table) {
	Symbol type = node ->getType();
	if (type==ResultCls || type==SuchThatCls || type==PatternCls || type==WithCls) {
		int nodeType = rankNodeType(type);
		int childOccurences = rankChildOccurences(node, table);
		int rank = nodeType + childOccurences;
		node ->setValue(to_string((long long) rank));
	}
}

int QueryOptimizer::rankNodeType(Symbol type) {
	switch (type) {
	case ResultCls:
		return 0;
	case SuchThatCls:
		return 2;
	case PatternCls:
		return 3;
	case WithCls:
		return 1;
	default:
		return 4;
	}
}

int QueryOptimizer::rankChildOccurences(TNode * node, SymbolTable & table) {
	int rank = 0;

	Symbol type = node -> getType();
	switch (type) {
	case Const:
		rank = 0; break;
	case Underline:
		{
			if (node->getNumChildren()==0) {
				rank = 1;
			} else {
				rank = QueryOptimizer::EXPRESSION_RANK;
			}
			break;
		}
	case QuerySymbol:
		{
			string name = node ->getValue();
			int index = table.getIndex(name);
			rank = index+2;
			break;
		}
	case No_Underline:
		rank = QueryOptimizer::EXPRESSION_RANK; break;
	case Undefined:
		rank = QueryOptimizer::UNDEFINE_RANK; break;
	default:
		{
			int size = node ->getNumChildren();
			for (int i=0; i<size; i++) {
				TNode * child = node ->getChildAtIndex(i);
				rank += rankChildOccurences(child, table);
			}
		}
	}

	return rank;
}
