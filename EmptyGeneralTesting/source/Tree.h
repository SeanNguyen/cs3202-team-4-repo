#ifndef Tree_h
#define Tree_h

#include "TNode.h"
#include <iostream>

using namespace std;

class Tree {
public:
	TNode createNode(string type, string value);

	TNode getRoot();
	int getNumChildren(TNode node);
	TNode getChildAtIndex(TNode node, int index);

	void setRoot(TNode node);
	int setChild(TNode parent, TNode child);

	static bool compareTree(Tree tree1, Tree tree2);

	// testing method
	void printTree();
	void printTreeNode(int depth, TNode node);
protected:
	TNode root;
};

#endif