#ifndef PROCTABLE_H_INCLUDED
#define PROCTABLE_H_INCLUDED

#include <vector>
#include <string>
using namespace std;

class ProcTable
{
private: 
	vector<string> procTable; 
	

public:
	
	int insertProc(string name);

	vector<int> getProcIndex(string name);
	string getProcName(int index);
	int getSize();
	
};

#endif