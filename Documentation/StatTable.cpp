# include "StatTable.h"
# include <vector> 
#include<iostream>

int StatTable::insertStmt(string name) 
{	
	//this for loop checks to see if the variable already exists 

	//otherwise insert the variable to the end of the vector and return index
	statTable.push_back(name);
	int index= statTable.size(); 
	return index;
}

vector<int> StatTable::getStmtIndex(string name)
{
	vector<int> indexes;

	for(size_t i=0;i<statTable.size();i++)
	{
		if(statTable.at(i)==name)
			indexes.push_back(i+1);
	}

	return indexes ;
}

string StatTable::getStmtName(int index) 
{
	index--;

	if((statTable.size()-1)>=(size_t)index)
		return statTable.at(index); 

	return "variable not found";
}

int StatTable::getSize()
{
	return statTable.size();
}