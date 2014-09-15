# include "ProcTable.h"
# include <vector> 
#include<iostream>

int ProcTable::insertProc(string name) 
{	
	//this for loop checks to see if the variable already exists 

	//otherwise insert the variable to the end of the vector and return index
	procTable.push_back(name);
	int index= procTable.size(); 
	return index;
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

	return "procedure not found";
}

int ProcTable::getProcTableSize()
{
	return procTable.size();
}