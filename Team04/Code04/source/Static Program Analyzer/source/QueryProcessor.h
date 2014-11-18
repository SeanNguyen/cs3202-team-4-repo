#ifndef QueryProcessor_h
#define QueryProcessors_h

#include "QueryPreprocessor.h"
#include "QueryEvaluator.h"

#include <vector>
#include <string>

using namespace std;

class QueryProcessor {
public:
	QueryProcessor();
	QueryProcessor(string directory);
	vector<vector<string>> Process();
	vector<string> Process(string query);
private:
	string fileDirectory;
};

#endif