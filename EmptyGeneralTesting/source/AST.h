#ifndef AST_h
#define AST_h

#include "Tree.h"

class AST : public Tree {
public:
TNode * findNodeOfStmt(int index);
bool hasSubTree(Tree tree);
bool isSameTree(Tree tree);

private:
TNode * findNodeOfStmt(TNode * node, int& count, int index); 
};

#endif
