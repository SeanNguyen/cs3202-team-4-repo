#ifndef TNode_h
#define TNode_h

#include <string>
#include <vector>

using namespace std;

class TNode {
public:
	TNode();
	TNode(string type, string value);

	string getType();
	string getValue();
	int getNumChildren();
	TNode getChildAtIndex(int index);
	
	int setChild(TNode node);
private:
	string type;
	string value;
	vector<TNode> children;
};

#endif