#include "QueryProcessor.h"
#include "../AutoTester/source/AbstractWrapper.h"

// constructors
QueryProcessor::QueryProcessor() {
}

QueryProcessor::QueryProcessor(string directory) {
	this -> fileDirectory = directory;
}

// method to call by other classes
vector<vector<string>> QueryProcessor::Process() {
	
	QueryPreprocessor preprocessor(fileDirectory);
	QueryEvaluator evaluator;
	
	preprocessor.Preprocess();
	
	evaluator.Evaluate();
	
	return evaluator.getAllResult();
	
	vector<vector<string>> a;
	return a;
}

vector<string> QueryProcessor::Process(string query) {
	QueryPreprocessor preprocessor("");
	QueryEvaluator evaluator;

	if (AbstractWrapper::GlobalStop) {
		vector<string> results;
		return results;
	}

	preprocessor.Preprocess(query);
	evaluator.Evaluate();

	return evaluator.getResult(0);
}
