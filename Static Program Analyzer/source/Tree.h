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
	int getSize();
	int getNumChildren(TNode * node);
	TNode *getChildAtIndex(TNode * node, int i);
	void printTree();
	int countNode(Symbol type, string value);
	void calculateSize();
private:
	int size;
	TNode *root;
	int countNode(TNode * node, Symbol type, string value);

	int calculateSize(TNode * node);
};