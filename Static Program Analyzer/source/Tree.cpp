#include "Tree.h"

Tree::Tree() {
	TNode * node = new TNode();
	setRoot(node);
}

TNode * Tree::createNode() { 
	TNode * node = new TNode();
	return node;
}

TNode * Tree::createNode(Symbol type) {
	TNode * node = new TNode(type);
	return node;
}

TNode * Tree::createNode(Symbol type, string value) {
	TNode * node = new TNode(type, value);
	return node;
}

void Tree::setRoot(TNode * node) {
	root = node;
}

int Tree::addChild(TNode * parent, TNode * child) {
	return parent -> addChild(child);
}

TNode * Tree::getRoot() {
	return root;
}

int Tree::getNumChildren(TNode * node) {
	return node -> getNumChildren();
}

TNode * Tree::getChildAtIndex(TNode * node, int i) {
	return node -> getChildAtIndex(i);
}

void Tree::printTree() {
	TNode * root = getRoot();
	cout <<endl;
	root -> printTNode();
	cout <<endl;
}

int Tree::countNode(Symbol type, string value) {
	int count = 0;
	TNode * root = getRoot();
	return countNode(root, type, value);
}

int Tree::countNode(TNode * node, Symbol type, string value) {
	int count = 0;
	if (node ->equals(type, value)) count = 1;
	for (int i=0; i<node->getNumChildren(); i++) {
		TNode * child = node->getChildAtIndex(i);
		count += countNode(child, type, value);
	}
	return count;
}
