#include "TNode.h"

TNode::TNode() {
	this -> value = "";
	this -> type = "";
}

TNode::TNode(string type, string value) {
	this -> type = type;
	this -> value = value;
}

string TNode::getType() {
	return this -> type;
}

string TNode::getValue() {
	return this -> value;
}

int TNode::getNumChildren() {
	return this -> children.size();
}

TNode TNode::getChildAtIndex(int index) {
	if (getNumChildren()==0) {
		throw "Error: TNode has no child";
	} 
	if (index<0 || index>getNumChildren()) {
			throw "Error: index out of range";
	}
	return children[index]; 
}

int TNode::setChild(TNode node) {
	children.push_back(node);
	return children.size();
}