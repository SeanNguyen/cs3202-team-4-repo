#include "AST.h"

// Description: this method is to find the node with stmt# "index" in AST
// Apply DFS
TNode AST::findNodeOfStmt(int index) {
	TNode root = getRoot();

	// call recursive method
	int count = 0;
	TNode result = findNodeOfStmt(root, count, index);

	return result;
} 

bool AST::hasSubTree(Tree tree) {
	TNode _root = tree.getRoot();
	TNode root = getRoot();

	// base case
	if (isSameTree(tree)) return true;
	
	int size = root.getNumChildren();
	for(int i=0; i<size; i++) {
		TNode child = root.getChildAtIndex(i);
		AST subAST; subAST.setRoot(child);
		if (subAST.hasSubTree(tree)) {
			return true;
		}
	}

	return false;
}

bool AST::isSameTree(Tree tree) {
	TNode _root = tree.getRoot();
	TNode root = getRoot();

	if (root.getType()==_root.getType() &&
		root.getValue()==_root.getValue()) {
			if (_root.getNumChildren()==0) {
				return true;
			} else {
				if (root.getNumChildren()!=_root.getNumChildren()) return false;
				for (int i=0; i<root.getNumChildren(); i++) {
					AST subAST; subAST.setRoot(root.getChildAtIndex(i));
					Tree subTree; subTree.setRoot(_root.getChildAtIndex(i));
					if (!subAST.isSameTree(subTree)) return false;
				}
				return true;
			}
	}
	return false;
}

TNode AST::findNodeOfStmt(TNode node, int& count, int index) {
	// only update *count if encounting those following nodes
	if (node.getType()=="while" || node.getType()=="assignment") {
		count++;
	}
	// base case
	if (count == index) {
		return node;
	} else {
		int size = node.getNumChildren();
		if (size!=0) {
			for (int i=0; i<size; i++) {
				TNode child = node.getChildAtIndex(i);
				TNode result = findNodeOfStmt(child, count, index);
				if (result.getType()!="") {
					return result;
				}
			}
		}
		
	}

	// return a null value here
	TNode throwNode("", "");
	return throwNode;
}