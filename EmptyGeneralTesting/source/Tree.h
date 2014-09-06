#pragma once

#include "TNode.h"

class Tree {
public:
	Tree();
	void setRoot(TNode node);
	TNode & getRoot();
private:
	TNode root;
};