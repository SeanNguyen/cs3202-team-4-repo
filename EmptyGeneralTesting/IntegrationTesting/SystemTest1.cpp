#include <cppunit/config/SourcePrefix.h>
#include "SystemTest1.h"

void SystemTest1::setUp() {
}

void SystemTest1::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( SystemTest1 );

void SystemTest1::test1() {
	string source = "..\\..\\Tests\\Source1.txt";
	string queries = "..\\..\\Tests\\Queries1.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildCallTable();
	parser.buildFollowTable();
	parser.buildModifyTable();
	parser.buildParentTable();
	parser.buildStatTable();
	parser.buildProcTable();
	parser.buildUseTable();
	parser.buildVarTable();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}

}