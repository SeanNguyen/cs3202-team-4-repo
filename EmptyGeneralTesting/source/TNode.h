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
	string getValue();
	int getNumChildren();
	TNode & getChildAtIndex(int i);
	int addChild(TNode child);
private:
	Symbol type;
	string value;
	vector<TNode> children;
};