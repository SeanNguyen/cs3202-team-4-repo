#include <cppunit/config/SourcePrefix.h>
#include "SystemTest1.h"

void SystemTest1::setUp() {
	PKB::resetPKB();
}

void SystemTest1::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( SystemTest1 );

void SystemTest1::test1() {
	//string source = "..\\..\\Tests\\Source1.txt";
	//string queries = "..\\..\\Tests\\Queries1_TestBasic.txt";
	//Parser parser;
	//QueryProcessor qp(queries);
	//
	//parser.parse(source);
	//parser.buildPKB();

	//vector<vector<string>> results = qp.Process();

	//for (size_t i=0; i<results.size(); i++) {
	//	cout << "Query " << i+1 << ": ";
	//	for (size_t j=0; j< results[i].size(); j++) {
	//		cout << results[i][j] << " ";
	//	}
	//	cout <<endl;
	//}

}

void SystemTest1::testCallsCallStar() {
	string source = "..\\..\\Tests\\SourceSimpleCall.txt";
	string queries = "..\\..\\Tests\\QueriesSimpleCall.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	cout << "TEST ISCALL: Calls(\"Simple1\", \"Simple2\") = ";
	cout << PKB::isCalls(0, 1) <<endl; 

	cout << "TEST ISCALLSTAR: Calls*(\"Simple1\", \"Simple2\") = ";
	cout << PKB::isCallStar(0, 1) <<endl; 

	cout << "TEST ISCALLSTAR: Calls*(\"Simple1\", \"Simple3\") = ";
	cout << PKB::isCallStar(0, 2) <<endl; 

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}

}

void SystemTest1::test2() {
	/*string source = "..\\..\\Tests\\Source2.txt";
	string queries = "..\\..\\Tests\\Queries2_1.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}*/

}

void SystemTest1::test3() {
	/*string source = "..\\..\\Tests\\Source3.txt";
	string queries = "..\\..\\Tests\\Queries3.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
*/
}

void SystemTest1::test4() {
	/*string source = "..\\..\\Tests\\Source4.txt";
	string queries = "..\\..\\Tests\\Queries4.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
*/
}

void SystemTest1::test5() {
	/*string source = "..\\..\\Tests\\Source5.txt";
	string queries = "..\\..\\Tests\\Queries5.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
*/
}

void SystemTest1::test6() {
	/*string source = "..\\..\\Tests\\Source6.txt";
	string queries = "..\\..\\Tests\\Queries6.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
*/
}

void SystemTest1::testWithCls() {
	/*string source = "..\\..\\Tests\\Source1.txt";
	string queries = "..\\..\\Tests\\Queries8_1-WithClause.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}*/
}