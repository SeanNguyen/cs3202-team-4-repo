#include "ResultManagerTest.h"

void ResultManagerTest::setUp() {
}

void ResultManagerTest::tearDown() {
}

CPPUNIT_TEST_SUITE_REGISTRATION( ResultManagerTest );

void ResultManagerTest::testInsertTable() {
	ResultManager rm;
	ResultTable * t1 = populateData(Case1);
	ResultTable * t2 = populateData(Case2);
	ResultTable * t3 = populateData(Case3);
	rm.insertTable(t1); rm.insertTable(t2); rm.insertTable(t3);

	CPPUNIT_ASSERT_EQUAL(2, rm.getSize());
	ResultTable * table1 = rm.getTable(0);
	ResultTable * table2 = rm.getTable(1);
	CPPUNIT_ASSERT_EQUAL(4, table1->getSymbolSize());
	CPPUNIT_ASSERT_EQUAL(3, table1->getSize());
}

void ResultManagerTest::testMergeTable() {
	ResultManager rm;
	ResultTable * t1 = populateData(Case1);
	ResultTable * t2 = populateData(Case2);

	ResultTable * mt = rm.mergeTables(t1, t2);
	CPPUNIT_ASSERT_EQUAL(4, mt->getSymbolSize());
	CPPUNIT_ASSERT_EQUAL(3, mt->getSize());
	vector<int> row1; vector<int> row2; vector<int> row3; 
	row1.push_back(1); row1.push_back(2); row1.push_back(1); row1.push_back(4);
	row2.push_back(1); row2.push_back(2); row2.push_back(1); row2.push_back(7);
	row3.push_back(1); row3.push_back(2); row3.push_back(1); row3.push_back(10);
	CPPUNIT_ASSERT_EQUAL(true, mt->containsValRow(row1));
	CPPUNIT_ASSERT_EQUAL(true, mt->containsValRow(row2));
	CPPUNIT_ASSERT_EQUAL(true, mt->containsValRow(row3));
} 

void ResultManagerTest::testExtractTable() {
	ResultManager rm;
	ResultTable * t1 = populateData(Case1);
	ResultTable * t2 = populateData(Case2);
	ResultTable * t3 = populateData(Case3);
	rm.insertTable(t1); rm.insertTable(t2); rm.insertTable(t3);

	vector<string> s1;
	s1.push_back("s1"); s1.push_back("s2"); 
	ResultTable * et1 = rm.extractTable(s1);

	CPPUNIT_ASSERT_EQUAL(2, et1->getSymbolSize());
	CPPUNIT_ASSERT_EQUAL(1, et1->getSize());
}

ResultTable * ResultManagerTest::populateData(Case caseNum) {
	ResultTable * table = new ResultTable();
	switch(caseNum) {
	case Case1:
		{
			table->insertSymbol("s1"); table->insertSymbol("s2"); table->insertSymbol("p");
			vector<int> row1;
			row1.push_back(1); row1.push_back(2); row1.push_back(1); 
			table->insertValRow(row1);
			vector<int> row2;
			row2.push_back(1); row2.push_back(3); row2.push_back(1); 
			table->insertValRow(row2);
			vector<int> row3;
			row3.push_back(1); row3.push_back(4); row3.push_back(3);
			table->insertValRow(row3);
			vector<int> row4;
			row4.push_back(2); row4.push_back(3); row4.push_back(1);
			table->insertValRow(row4);
			vector<int> row5;
			row5.push_back(2); row5.push_back(10); row5.push_back(1);
			table->insertValRow(row5);
			break;
		}
	case Case2:
		{
			table->insertSymbol("s2"); table->insertSymbol("s3"); table->insertSymbol("p");
			vector<int> row1;
			row1.push_back(1); row1.push_back(4); row1.push_back(1); 
			table->insertValRow(row1);
			vector<int> row2;
			row2.push_back(1); row2.push_back(5); row2.push_back(1); 
			table->insertValRow(row2);
			vector<int> row3;
			row3.push_back(2); row3.push_back(4); row3.push_back(1);
			table->insertValRow(row3);
			vector<int> row4;
			row4.push_back(2); row4.push_back(7); row4.push_back(1);
			table->insertValRow(row4);
			vector<int> row5;
			row5.push_back(2); row5.push_back(10); row5.push_back(1);
			table->insertValRow(row5);
			break;
		}
	case Case3:
		{
			table->insertSymbol("s4"); table->insertSymbol("v");
			vector<int> row1;
			row1.push_back(1); row1.push_back(2); 
			table->insertValRow(row1);
			vector<int> row2;
			row2.push_back(1); row2.push_back(3);
			table->insertValRow(row2);
			vector<int> row3;
			row3.push_back(1); row3.push_back(4); 
			table->insertValRow(row3);
			vector<int> row4;
			row4.push_back(2); row4.push_back(3); 
			table->insertValRow(row4);
			vector<int> row5;
			row5.push_back(2); row5.push_back(10); 
			table->insertValRow(row5);
			break;
		}
	default:
		break;
	}

	return table;
}