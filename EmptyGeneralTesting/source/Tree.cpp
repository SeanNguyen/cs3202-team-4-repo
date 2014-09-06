#include "Tree.h"

Tree::Tree() {
}

void Tree::setRoot(TNode node) {
	root = node;
}

TNode & Tree::getRoot() {
	return root;
}