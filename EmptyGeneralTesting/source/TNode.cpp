#include "TNode.h"

TNode::TNode() {
	type = Undefined;
	value = 0;
}

TNode::TNode(Symbol _type) {
	type = _type;
	value = 0;
}

TNode::TNode(Symbol _type, int _value) {
	type = _type;
	value = _value;
}

Symbol TNode::getType() {
	return type;
}

int TNode::getValue() {
	return value;
}

int TNode::getNumChildren() {
	return children.size();
}

TNode & TNode::getChildAtIndex(int i) {
	if (i<0 || i >=  this -> getNumChildren()) {
		throw "Out of bounds";
	}
	return children[i];
}

void TNode::addChild(TNode child) {
	children.push_back(child);
}