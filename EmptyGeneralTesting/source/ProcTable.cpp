# include "ProcTable.h"
# include <vector> 
#include <iostream>
#include <algorithm>


bool ProcTable::isProc(string name) {
	for (size_t i=0; i<procTable.size(); i++) {
		if (procTable[i]==name) 
			return true;
	}
	return false;
}

int ProcTable::insertProc(string name) 
{	
	//otherwise insert the variable to the end of the vector and return index
	if (procTable.empty()) {
		procTable.push_back(name);
		int index= procTable.size(); 
		return index;
	}

	for (size_t index = 0; index < procTable.size(); index++){
		if(!isProc(name)){
			procTable.push_back(name);
			int index= procTable.size(); 
			return index;
		}
	}
	return -1;


	
}

vector<int> ProcTable::getProcIndex(string name)
{
	vector<int> indexes;

	for(size_t i=0;i<procTable.size();i++)
	{
		if(procTable.at(i)==name)
			indexes.push_back(i);
	}

	return indexes ;
}

string ProcTable::getProcName(int index) 
{
	if((procTable.size())>(size_t)index)
		return procTable.at(index); 

	return "procedure not found";
}

int ProcTable::getSize()
{
	return procTable.size();
}