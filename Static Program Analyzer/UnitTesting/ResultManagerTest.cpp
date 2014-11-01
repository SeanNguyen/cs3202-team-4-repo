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

	CPPUNIT_ASSERT_EQUAL(3, rm.getSize());
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