#include "SymbolTable.h"

SymbolTable::SymbolTable() {
	this -> size = 0;
}

int SymbolTable::getSize() {
	return this -> size;
}

string SymbolTable::getType(string name) {
	for (int i=0; i<size; i++) {
		if (names[i]==name) 
			return types[i];
	}
	return "";
}

string SymbolTable::getType(int index) {
	if (size==0) {
		throw "";
	}
	if (index<0 && index >= size) {
		throw "";
	}
	return types[index];
}

string SymbolTable::getName(int index) {
	if (size==0) {
		throw "";
	}
	if (index<0 && index >= size) {
		throw "";
	}
	return names[index];
}

int SymbolTable::getIndex(string name) {
	for (size_t i=0; (int)i<size; i++) {
		if (names[i]==name)
			return (int)i;
	}
	return -1;
}

bool SymbolTable::isSymbol(string name) {
	if (getType(name)!="") 
		return true;
	return false;
}

int SymbolTable::setSymbol(string type, string name) {
	types.push_back(type);
	names.push_back(name);
	size++;
	return size;
}

void SymbolTable::printTable() {
	for (size_t i=0; (int)i<size; i++) {
		cout<<i<<" "<<types[i]<<" "<<names[i]<<endl;
	}
}