#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
	
	// create a Parser obj
	Parser parser;
	parser.parse(filename);
	parser.buildVarTable();
	parser.buildStatTable();
	parser.buildFollowTable();
	parser.buildParentTable();
	parser.buildModifyTable();
	parser.buildUseTable();

	while (true) {
		cout << "Error! Why can you run?" <<endl;
	}
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
  QueryProcessor queryProcessor;
  std::vector<std::string> resultVector = queryProcessor.Process(query);
  for (size_t i=0; i<resultVector.size(); i++) {
	  results.push_back(resultVector[i]);
	  results.push_back("TESTING");
  }	
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}