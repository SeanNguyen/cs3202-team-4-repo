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
	static void resetGlobalId();
	static int getGlobalId();
	int getID();
	Symbol getType();
	string getValue();
	void setValue(string _value);
	int getNumChildren();
	TNode * getChildAtIndex(int i);
	int addChild(TNode * child);
	void printTNode();
	void sortChildrenList();
	bool equals(Symbol type, string value);
private:
	int id;
	static int GLOBAL_ID;
	Symbol type;
	string value;
	vector<TNode*> children;

	void printTNode(int depth);
	vector<TNode *> sortChildrenList(int start, int end);
	vector<TNode *> mergeList(vector<TNode *> list1, vector<TNode *> list2);
};