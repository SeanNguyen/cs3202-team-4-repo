#pragma once

#include "TNode.h"

class Tree {
public:
	Tree();
	TNode * createNode();
	TNode * createNode(Symbol type);
	TNode * createNode(Symbol type, string value);
	int addChild(TNode * parent, TNode * child);
	void setRoot(TNode * node);
	TNode * getRoot();
	int getNumChildren(TNode * node);
	TNode *getChildAtIndex(TNode * node, int i);
	void printTree();
private:
	TNode *root;
};