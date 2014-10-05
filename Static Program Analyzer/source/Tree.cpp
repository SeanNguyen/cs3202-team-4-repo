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