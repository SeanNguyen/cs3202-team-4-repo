#include "ListTableTest.h"
#include "ListTable.h"


ListTableTest::ListTableTest(void)
{
}

ListTableTest::~ListTableTest(void)
{
}

void ListTableTest::setUp() {
}

void ListTableTest::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION( ListTableTest );

void ListTableTest::TestInsert() {
	ListTable <string> listTable;
	string element1 = "a";
	string element2 = "b";
	listTable.insert (element1);
	listTable.insert (element2);
	int expectedSize = 2;
	int actualSize = listTable.getSize();
	CPPUNIT_ASSERT_EQUAL (expectedSize, actualSize);
}

void ListTableTest::TestGetValue() {
	ListTable <string> listTable;
	string element1 = "a";
	string element2 = "b";
	listTable.insert (element1);
	listTable.insert (element2);
	
	CPPUNIT_ASSERT_EQUAL (listTable.getValue(0), element1);
	CPPUNIT_ASSERT_EQUAL (listTable.getValue(1), element2);
}

void ListTableTest::TestGetIndexes() {
	ListTable <string> listTable;
	string element1 = "a";
	string element2 = "b";
	string element3 = element1;
	listTable.insert (element1);
	listTable.insert (element2);
	listTable.insert (element3);

	int expectedResultSize = 2;
	int actualResultSize = listTable.getIndexes(element1).size();

	CPPUNIT_ASSERT_EQUAL (expectedResultSize, actualResultSize);
}
