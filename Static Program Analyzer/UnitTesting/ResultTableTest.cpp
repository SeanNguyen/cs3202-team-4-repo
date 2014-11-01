#include "ResultTable.h"
#include "ResultTableTest.h"

void TestResultTable::setUp() {}

void TestResultTable::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION( TestResultTable );

void TestResultTable::TestInsertSymbols() {
	ResultTable table;
	vector<string> symbols;
	symbols.push_back("s1");
	symbols.push_back("s2");
	symbols.push_back("s3");
	symbols.push_back("s4");
	symbols.push_back("s5");
	symbols.push_back("s3");
	table.insertSymbol(symbols);

	CPPUNIT_ASSERT_EQUAL(5, table.getSymbolSize());
	CPPUNIT_ASSERT(table.containsSymbol("s1")==true);
	CPPUNIT_ASSERT(table.containsSymbol("s2")==true);
	CPPUNIT_ASSERT(table.containsSymbol("s4")==true);
	CPPUNIT_ASSERT(table.getSymbolIndex("s3")==2);
	CPPUNIT_ASSERT(table.getSymbol(2)=="s3");
}

void TestResultTable::TestInsertVal() {
	ResultTable table;
	table.insertSymbol("s1"); table.insertSymbol("s2"); table.insertSymbol("s3");
	string data_1[3] = {"1", "2", "3"};
	string data_2[3] = {"1", "2", "4"};
	string data_3[2] = {"2", "4"};
	string data_4[3] = {"2", "4", "-1"};
	string data_5[3] = {"1", "2", "3"};
	vector<string> row_1(&data_1[0], &data_1[0]+3);
	vector<string> row_2(&data_2[0], &data_2[0]+3);
	vector<string> row_3(&data_3[0], &data_3[0]+2);
	vector<string> row_4(&data_4[0], &data_4[0]+3);
	vector<string> row_5(&data_5[0], &data_5[0]+3);
	table.insertValRow(row_1);
	table.insertValRow(row_2);
	table.insertValRow(row_3);
	table.insertValRow(row_4);
	table.insertValRow(row_5);

	CPPUNIT_ASSERT_EQUAL(3, table.getSize());
	vector<string> table_row_3 = table.getValRow(2);
	CPPUNIT_ASSERT(table_row_3[0]=="2");
	CPPUNIT_ASSERT(table_row_3[1]=="4");
}

void TestResultTable::TestDeleteInvalidRow() {
	ResultTable table;
	table.insertSymbol("s1"); table.insertSymbol("s2"); table.insertSymbol("s3");
	string data_1[3] = {"1", "2", "3"};
	string data_2[3] = {"1", "2", "4"};
	string data_3[2] = {"2", "4"};
	string data_4[3] = {"4", "4", "-1"};
	string data_5[3] = {"1", "2", "12"};
	vector<string> row_1(&data_1[0], &data_1[0]+3);
	vector<string> row_2(&data_2[0], &data_2[0]+3);
	vector<string> row_3(&data_3[0], &data_3[0]+2);
	vector<string> row_4(&data_4[0], &data_4[0]+3);
	vector<string> row_5(&data_5[0], &data_5[0]+3);
	table.insertValRow(row_1);
	table.insertValRow(row_2);
	table.insertValRow(row_3);
	table.insertValRow(row_4);
	table.insertValRow(row_5);

	table.deleleInvalidRows();
	CPPUNIT_ASSERT_EQUAL(3, table.getSize());
}

void TestResultTable::TestExtractData() {
	ResultTable table;
	table.insertSymbol("s1"); table.insertSymbol("s2"); table.insertSymbol("s3");
	string data_1[3] = {"1", "2", "3"};
	string data_2[3] = {"1", "2", "4"};
	string data_3[2] = {"2", "4"};
	string data_4[3] = {"4", "4", "-1"};
	string data_5[3] = {"1", "2", "12"};
	vector<string> row_1(&data_1[0], &data_1[0]+3);
	vector<string> row_2(&data_2[0], &data_2[0]+3);
	vector<string> row_3(&data_3[0], &data_3[0]+2);
	vector<string> row_4(&data_4[0], &data_4[0]+3);
	vector<string> row_5(&data_5[0], &data_5[0]+3);
	table.insertValRow(row_1);
	table.insertValRow(row_2);
	table.insertValRow(row_3);
	table.insertValRow(row_4);
	table.insertValRow(row_5);

	vector<string> s; s.push_back("s1");
	ResultTable * table_2 = table.extractData(s);

	CPPUNIT_ASSERT_EQUAL(1, table_2->getSymbolSize());
	CPPUNIT_ASSERT_EQUAL(3, table_2->getSize());
}