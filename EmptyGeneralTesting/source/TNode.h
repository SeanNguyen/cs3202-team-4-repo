#pragma once

#include <string>
#include <vector>

#include "SyntaxHelper.h"

using namespace std;


class TNode {
public:
	TNode();
	TNode(Symbol _type);
	TNode(Symbol _type, int _value);
	Symbol getType();
	int getValue();
	int getNumChildren();
	TNode & getChildAtIndex(int i);
	void addChild(TNode child);
private:
	Symbol type;
	int value;
	vector<TNode> children;
};