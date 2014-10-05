//#include "MapTableTest.h"
//#include "MapTable.h"
//
//
//MapTableTest::MapTableTest(void)
//{
//}
//
//
//MapTableTest::~MapTableTest(void)
//{
//}
//
//void MapTableTest::setUp() {
//}
//
//void MapTableTest::tearDown() {
//
//}
//
//CPPUNIT_TEST_SUITE_REGISTRATION( MapTableTest );
//
//void MapTableTest::TestInsert() {
//	int key1 = 10;
//	int key2 = 20;
//	int value1 = 100;
//	int value2 = 200;
//
//	MapTable<int> mapTable;
//	mapTable.insert (key1, value1);
//	mapTable.insert (key2, value2);
//
//	int expectedSize = 2;
//	int actualSize = mapTable.getSize();
//	CPPUNIT_ASSERT_EQUAL (expectedSize, actualSize);
//}
//
//void MapTableTest::TestIsMapped() {
//	int key1 = 10;
//	int key2 = 20;
//	int value1 = 100;
//	int value2 = 200;
//
//	MapTable<int> mapTable;
//	mapTable.insert (key1, value1);
//	mapTable.insert (key2, value2);
//
//	CPPUNIT_ASSERT_EQUAL (true, mapTable.isMapped (key1, value1));
//	CPPUNIT_ASSERT_EQUAL (false, mapTable.isMapped (key1, value2));
//}
//
//void MapTableTest::TestIsMappedStar() {
//	int key1 = 10;
//	int key2 = 20;
//	int key3 = 30;
//	int key4 = 40;
//
//	MapTable<int> mapTable;
//	mapTable.insert (key1, key2);
//	mapTable.insert (key2, key1);
//	mapTable.insert (key2, key3);
//
//	CPPUNIT_ASSERT_EQUAL (true, mapTable.isMappedStar(key1, key3, true));
//	CPPUNIT_ASSERT_EQUAL (false, mapTable.isMappedStar(key1, key4, true));
//}
//
//void MapTableTest::TestGetValues() {
//	int key1 = 10;
//	int key2 = 20;
//	int key3 = 30;
//	int key4 = 40;
//
//	MapTable<int> mapTable;
//	mapTable.insert (key1, key2);
//	mapTable.insert (key2, key1);
//	mapTable.insert (key2, key3);
//
//	int expectedResultSize = 2;
//	int actualResultSize = mapTable.getValues(key2).size();
//	CPPUNIT_ASSERT_EQUAL (expectedResultSize, actualResultSize);
//}
//
//void MapTableTest::TestGetValuesStar() {
//	int key1 = 10;
//	int key2 = 20;
//	int key3 = 30;
//	int key4 = 40;
//
//	MapTable<int> mapTable;
//	mapTable.insert (key1, key2);
//	mapTable.insert (key2, key1);
//	mapTable.insert (key2, key3);
//
//	int expectedResultSize = 3;
//	int actualResultSize = mapTable.getValuesStar(key1, true).size();
//	CPPUNIT_ASSERT_EQUAL (expectedResultSize, actualResultSize);
//}