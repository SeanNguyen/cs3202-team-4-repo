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
private:
	Symbol type;
	string value;
	vector<TNode*> children;

	void printTNode(int depth);
};