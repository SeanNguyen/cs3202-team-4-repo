#include "TNode.h"

TNode::TNode() {
	type = Undefined;
	value = "";
}

TNode::TNode(Symbol _type) {
	type = _type;
	value = "";
}

TNode::TNode(Symbol _type, string _value) {
	type = _type;
	value = _value;
}

Symbol TNode::getType() {
	return type;
}

string TNode::getValue() {
	return value;
}

int TNode::getNumChildren() {
	return children.size();
}

TNode * TNode::getChildAtIndex(int i) {
	if (i<0 || i >=  this -> getNumChildren()) {
		throw "Out of bounds";
	}
	return children[i];
}

int TNode::addChild(TNode * child) {
	children.push_back(child);
	return children.size()-1;
}

void TNode::printTNode() {
	printTNode(0);
}

void TNode::printTNode(int depth) {
	for (int i=0; i<depth; i++) {
		cout << "  ";
	}
	cout << SyntaxHelper::SymbolToString(type) << " " << value << " " << getNumChildren()<<endl;
	for (size_t i=0; i<children.size(); i++) {
		TNode child = *getChildAtIndex(i);
		child.printTNode(depth+1);
	}
}

// sort the list of children based on their values
// from lowest to highest
// apply merge sort
void TNode::sortChildrenList() {
	int size = getNumChildren();
	children = sortChildrenList(0, size-1);
}

vector<TNode *> TNode::sortChildrenList(int start, int end) {
	vector<TNode *> list;
	if (start>end) {
		return list;
	}
	if (start==end) {
		list.push_back(children[start]);
		return list;
	}
	int midpoint = (start+end)/2;
	vector<TNode *> firstHalf = sortChildrenList(start, midpoint);
	vector<TNode *> secondHalf = sortChildrenList(midpoint+1, end);
	list = mergeList(firstHalf, secondHalf);
	return list;
}

vector<TNode *> TNode::mergeList(vector<TNode *> list1, vector<TNode *> list2) {
	vector<TNode *> list;
	unsigned int i=0; unsigned int j=0;
	while (i<list1.size() && j<list2.size()) {
		string val1 = list1[i] ->getValue();
		string val2 = list2[j] ->getValue();
		if (val1<val2) {
			list.push_back(list1[i]);
			i++;
		} else {
			list.push_back(list2[j]);
			j++;
		}
	}
	while(i<list1.size()) {
		list.push_back(list1[i]);
		i++;
	}
	while(j<list2.size()) {
		list.push_back(list2[j]);
		j++;
	}
	return list;
}