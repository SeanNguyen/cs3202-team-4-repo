#include <cppunit/config/SourcePrefix.h>
#include "SystemTest1.h"
#include "DesignExtractor.h"

void SystemTest1::setUp() {
	PKB::resetPKB();
}

void SystemTest1::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( SystemTest1 );

void SystemTest1::test1() {
	string source = "..\\..\\Tests\\Source1.txt";
	string queries = "..\\..\\Tests\\Queries1_TestBasic.txt";
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

}

void SystemTest1::testCallsCallStar() {
	/*string source = "..\\..\\Tests\\SourceSimpleCall.txt";
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
*/
}

void SystemTest1::test2() {
	string source = "..\\..\\Tests\\Source2.txt";
	string queries = "..\\..\\Tests\\TestBasicUsesForStmt_Query2.txt";
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

}

void SystemTest1::test3() {
	string source = "..\\..\\Tests\\Source3.txt";
	string queries = "..\\..\\Tests\\TestPatternandSuchthat_Query3.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();
	DesignExtractor de;
	de.buildPKB();

	vector<vector<string>> results = qp.Process();

	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
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
	string source = "..\\..\\Tests\\Source6.txt";
	string queries = "..\\..\\Tests\\TestBasicUses_Query6.txt";
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

void SystemTest1::testNext() {
	string source = "..\\..\\Tests\\source SIMPLE iter 2 consultaiton.txt";
	string queries = "..\\..\\Tests\\test queries iter 2 consultaiton.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	//cout << "Test Next Star: isNextStar(1, 1) = " << PKB::isNextStar(1, 1) <<endl;

	vector<vector<string>> results = qp.Process();

	cout << endl << "----TEST----" <<endl;
	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
	
}

void SystemTest1::test7() {
	string source = "..\\..\\Tests\\Source7.txt";
	string queries = "..\\..\\Tests\\TestBasicFollows_Query7.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	cout << endl << "----TEST 7----" <<endl;
	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
}

void SystemTest1::test8() {
	string source = "..\\..\\Tests\\Source8.txt";
	string queries = "..\\..\\Tests\\Queries8_1-WithClause.txt";
	Parser parser;
	QueryProcessor qp(queries);
	
	parser.parse(source);
	parser.buildPKB();

	vector<vector<string>> results = qp.Process();

	cout << endl << "----TEST 7----" <<endl;
	for (size_t i=0; i<results.size(); i++) {
		cout << "Query " << i+1 << ": ";
		for (size_t j=0; j< results[i].size(); j++) {
			cout << results[i][j] << " ";
		}
		cout <<endl;
	}
} 

void SystemTest1::test9(){
	string source = "..\\..\\Tests\\Source1.txt";
	Parser parser;
	PKB pkb;
	DesignExtractor de;
	
	parser.parse(source);
	parser.buildPKB();
	de.buildPKB();

	cout << "reached here";
	cout <<  pkb.getContainTableSize();
	cout <<endl;

}