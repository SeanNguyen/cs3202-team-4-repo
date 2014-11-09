#include "Tree.h"

Tree::Tree() {
	size = 0;
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

int Tree::getSize() { return size; }

TNode * Tree::getRoot() {
	if (root!=NULL)
		return root;
	return new TNode(Undefined);
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

void Tree::calculateSize() {
	if (root!=NULL) {
		size = calculateSize(root); 
	}
}

int Tree::calculateSize(TNode * node) {
	if (node==NULL) return 0;
	int count=1;
	for (int i=0; i<node->getNumChildren(); i++) {
		count += calculateSize(node->getChildAtIndex(i));
	}
	return count;
}