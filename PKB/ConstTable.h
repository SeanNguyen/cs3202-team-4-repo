#ifndef ConstTable_h
#define ConstTable_h

#include <string>
#include <vector>

using namespace std;

class ConstTable {
public:
	ConstTable();
	bool isConst(string value);
	bool insertConst(string value);
	int getIndex(string value);
	string getConst(int index);
	int getSize();
private:
	vector<string> constList;
	int size;
};

#endif