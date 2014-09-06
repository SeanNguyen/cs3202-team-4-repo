#include "Tree.h"

Tree::Tree() {
}

TNode & Tree::createNode() {
	return TNode node;
}

TNode & Tree::createNode(Symbol type) {
	return TNode node(type);
}

TNode & Tree::createNode(Symbol type, string value) {
	return TNode node(type, value);
}

void Tree::setRoot(TNode node) {
	root = node;
}

int Tree::addChild(TNode parent, TNode child) {
	return parent.addChild(child);
}

TNode & Tree::getRoot() {
	return root;
}

int Tree::getNumChildren(TNode node) {
	return node.getNumChildren();
}

TNode & getChildAtIndex(TNode node, int i) {
	return node.getChildAtIndex(i);
}