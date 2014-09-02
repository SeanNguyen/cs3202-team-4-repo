#include "Tree.h"

TNode Tree::createNode(string type, string value) {
	TNode node(type, value);
	return node;
}

TNode Tree::getRoot() {
	return this -> root;
}

int Tree::getNumChildren(TNode node) {
	return node.getNumChildren();
}

TNode Tree::getChildAtIndex(TNode node, int index) {
	return node.getChildAtIndex(index);
}

void Tree::setRoot(TNode node) {
	this -> root = node;
}

int Tree::setChild(TNode parent, TNode child) {
	return parent.setChild(child);
}

bool Tree::compareTree(Tree tree1, Tree tree2) {
	TNode root1 = tree1.getRoot();
	TNode root2 = tree2.getRoot();

	if (root1.getType()==root2.getType() &&
		root1.getValue()==root2.getValue()) {
		if (root1.getNumChildren()==root2.getNumChildren()) {
			if (root1.getNumChildren()!=0) { 
				for (int i=0; i<root1.getNumChildren(); i++) {
					TNode child1 = root1.getChildAtIndex(i);
					TNode child2 = root2.getChildAtIndex(i);
					Tree subtree1; subtree1.setRoot(child1);
					Tree subtree2; subtree2.setRoot(child2);
					if (!Tree::compareTree(subtree1, subtree2)) {
						return false;
					}
				}
			}
			return true;
		}
	}

	return false;
}

void Tree::printTree() {
	printTreeNode(0, root);
}

void Tree::printTreeNode(int depth, TNode node) {
	for(int i=0; i<depth; i++) {
		cout<<" ";
	}
	cout<<node.getType()<<" "<<node.getValue()<<endl;
	for(int i=0; i<node.getNumChildren(); i++) {
		TNode child = node.getChildAtIndex(i);
		printTreeNode(depth+1, child);
	} 
}