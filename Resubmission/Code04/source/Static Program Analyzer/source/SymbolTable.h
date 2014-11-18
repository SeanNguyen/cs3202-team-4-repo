#ifndef SymbolTable_h
#define SymbolTable_h
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SymbolTable {
public:
	SymbolTable();

	int setSymbol(string type, string name);

	string getType(string name);
	string getType(int index);
	string getName(int index);
	int getIndex(string name);
	int getSize();
	
	bool isSymbol(string name);

	// testing method
	void printTable();
private:
	int size;
	vector<string> types;
	vector<string> names;
};
#endif;