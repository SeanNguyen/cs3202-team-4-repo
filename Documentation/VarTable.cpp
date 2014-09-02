#include "VarTable.h"
#include <vector> 
#include <iostream>

int VarTable::insertVar(string name) 
/*{
	for(size_t index=0; index < varTable.size(); index++)
	{
		if(varTable.at(index).compare(name) == 0)
		{
			return -1;
		}
	}
	varTable.push_back(name);
	return varTable.size()-1;
}
*/
{
	//this for loop checks to see if the variable already exists 
	for(size_t i=0;i<varTable.size();i++)
	{
		if(varTable.at(i)==name)
			return -1;
	}

	//otherwise insert the variable to the end of the vector and return index
	varTable.push_back(name);
	int index= varTable.size()-1; 
	return index;
}

int VarTable::getVarIndex(string name)
{
	for(size_t i=0;i<varTable.size();i++)
	{
		if(varTable.at(i)==name)
			return i;
	}

	return -1 ;
}

string VarTable::getVarName(int index) 
{
	if((varTable.size()-1)>=(size_t)index)
		return varTable.at(index); 

	return "variable not found";
}

int VarTable::getSize()
{
	return varTable.size();
}