# include "ProcTable.h"
# include <vector> 
#include <iostream>
#include <algorithm>

int ProcTable::insertProc(string name) 
{	
	//otherwise insert the variable to the end of the vector and return index

	for (size_t index = 0; index < procTable.size(); index++){
		if(std::find(procTable.begin(), procTable.end(), name)== procTable.end()){
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
			indexes.push_back(i+1);
	}

	return indexes ;
}

string ProcTable::getProcName(int index) 
{
	index--;

	if((procTable.size()-1)>=(size_t)index)
		return procTable.at(index); 

	return "variable not found";
}

int ProcTable::getSize()
{
	return procTable.size();
}