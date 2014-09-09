#include "TNode.h"

TNode::TNode() {
	type = Undefined;
	value = "";
}

TNode::TNode(Symbol _type) {
	type = _type;
	value = "";
}

TNode::TNode(Symbol _type, string _value) {
	type = _type;
	value = _value;
}

Symbol TNode::getType() {
	return type;
}

string TNode::getValue() {
	return value;
}

int TNode::getNumChildren() {
	return children.size();
}

TNode *TNode::getChildAtIndex(int i) {
	if (i<0 || i >=  this -> getNumChildren()) {
		throw "Out of bounds";
	}
	return children[i];
}

int TNode::addChild(TNode &child) {
	children.push_back(&child);
	return children.size()-1;
}