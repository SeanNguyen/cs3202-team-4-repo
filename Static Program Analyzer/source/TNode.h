#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "SyntaxHelper.h"

using namespace std;


class TNode {
public:
	TNode();
	TNode(Symbol _type);
	TNode(Symbol _type, string _value);
	Symbol getType();
	string getValue();
	int getNumChildren();
	TNode * getChildAtIndex(int i);
	int addChild(TNode * child);
	void printTNode();
	void sortChildrenList();
private:
	Symbol type;
	string value;
	vector<TNode*> children;

	void printTNode(int depth);
	vector<TNode *> sortChildrenList(int start, int end);
	vector<TNode *> mergeList(vector<TNode *> list1, vector<TNode *> list2);
};