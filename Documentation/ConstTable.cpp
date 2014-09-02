#include "ConstTable.h"

ConstTable::ConstTable() {
	this -> size = 0;
}

bool ConstTable::isConst(string value) {
	if (getIndex(value)>=0) {
		return true;
	}
	return false;
}

bool ConstTable::insertConst(string value) {
	if (!isConst(value)) {
		constList.push_back(value);
		size++;
		return true;
	}
	return false;
}

int ConstTable::getSize() {
	return size;
}

int ConstTable::getIndex(string value) {
	for (int i=0; i<size; i++) {
		if (constList[i] == value) {
			return i;
		}
	}
	return -1;
}

string ConstTable::getConst(int index) {
	if (index<0 || index >=size) {
		return "";
	}
	return constList[index];
}