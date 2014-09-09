#include "Tree.h"

Tree::Tree() {
}

TNode Tree::createNode() { 
	return TNode();
}

TNode Tree::createNode(Symbol type) {
	TNode node(type);
	return node;
}

TNode Tree::createNode(Symbol type, string value) {
	TNode node(type, value);
	return node;
}

void Tree::setRoot(TNode &node) {
	root = &node;
}

int Tree::addChild(TNode &parent, TNode &child) {
	return parent.addChild(child);
}

TNode *Tree::getRoot() {
	return root;
}

int Tree::getNumChildren(TNode &node) {
	return node.getNumChildren();
}

TNode *Tree::getChildAtIndex(TNode &node, int i) {
	return node.getChildAtIndex(i);
}