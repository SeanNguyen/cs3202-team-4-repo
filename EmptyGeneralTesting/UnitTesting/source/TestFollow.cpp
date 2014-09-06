//
//#include <cppunit/config/SourcePrefix.h>
//#include "Follow.h"
//#include "TestFollow.h"
//
//#include <iostream>
//#include <vector>
//
//void
//FollowTest::setUp()
//{
//}
//
//void 
//FollowTest::tearDown()
//{
//}
//
//// Registers the fixture into the 'registry'
//CPPUNIT_TEST_SUITE_REGISTRATION( FollowTest ); // Note 4 
//
//
//void FollowTest::testInsert(){
//
//	Follow followObj;
//	
//	// verify that the insertion is correct - Note 7
//	int result1 = followObj.insertFollows(1,2);
//	int result2 = followObj.insertFollows(2,3);
//
//	CPPUNIT_ASSERT_EQUAL(99, result1);
//	CPPUNIT_ASSERT_EQUAL(99, result2);
//
//	int result3 = followObj.insertFollows(1, 2);
//
//	// attempt to insert a pair which already exists
//	CPPUNIT_ASSERT_EQUAL(-1, result3);
//
//	return;
//}
//
//void FollowTest::testisFollow(){
//
//	Follow followObj;
//
//	//insert a few pairs first
//	int res1 = followObj.insertFollows(1, 2);
//	int res2 = followObj.insertFollows(2, 3);
//
//	//for(int i=0;i<followObj.followTable.size(); i++) {
// //     for (int j=0;j<followObj.followTable[i].size(); j++)
//  //      std::cout << followObj.followTable[1][2] << " "; 
//		//std::cout <<res1;
//   //   std::cout << std::endl;
//   //}
//	
//	// verify that the pair exists - Note 7
//	CPPUNIT_ASSERT_EQUAL(true, followObj.isFollows(1, 2));
//	CPPUNIT_ASSERT_EQUAL(true, followObj.isFollows(2, 3));
//
//	// attempt to check a pair which does not exists
//	CPPUNIT_ASSERT_EQUAL(false, followObj.isFollows(5, 6));
//
//	//std::cout << followObj.isFollows(1, 2);
//	//std::cout << followObj.isFollows(2,3);
//	//std::cout << followObj.isFollows(5,6);
//
//
//	//for(int i=0;i<followObj.followTable.size(); i++) {
// //     for (int j=0;j<followObj.followTable[i].size(); j++)
// //       std::cout << followObj.followTable[i][j] << " "; 
// //     std::cout << std::endl;
// //  }
//
//	return;
//}
//
//void FollowTest::testisFollowStar()
//{
//	Follow followObj;
//	followObj.insertFollows(1, 2);
//	followObj.insertFollows(2, 3);
//	followObj.insertFollows(3, 4);
//
//	CPPUNIT_ASSERT_EQUAL(false, followObj.isFollowsStar(4, 5));
//	CPPUNIT_ASSERT_EQUAL(false, followObj.isFollowsStar(2, 1));
//	CPPUNIT_ASSERT_EQUAL(true, followObj.isFollowsStar(1, 4));
//
//	return;
//}
//
//void FollowTest::testgetFollowing(){
//
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 3);
//	int result2 = followObj.insertFollows(5, 6);
//
//	
//	// verify that the pair exists - Note 7
//	CPPUNIT_ASSERT_EQUAL(2, followObj.getFollowingStmt(1));
//	CPPUNIT_ASSERT_EQUAL(3, followObj.getFollowingStmt(2));
//	CPPUNIT_ASSERT_EQUAL(6, followObj.getFollowingStmt(5));
//
//
//	// attempt to get one which does not exist
//	CPPUNIT_ASSERT_EQUAL(-1, followObj.getFollowingStmt(7));
//
//	return;
//}
//
//void FollowTest::testgetFollowed(){
//
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 3);
//	int result2 = followObj.insertFollows(5, 6);
//
//	
//	// verify that the pair exists - Note 7
//	CPPUNIT_ASSERT_EQUAL(1, followObj.getFollowedStmt(2));
//	CPPUNIT_ASSERT_EQUAL(2, followObj.getFollowedStmt(3));
//	CPPUNIT_ASSERT_EQUAL(5, followObj.getFollowedStmt(6));
//
//
//	// attempt to get one which does not exist
//	CPPUNIT_ASSERT_EQUAL(-1, followObj.getFollowedStmt(7));
//
//	return;
//}
////
////void FollowTest::testgetSize(){
////
////	Follow followObj;
////
////	// attempt to get one which does not exist
////	CPPUNIT_ASSERT_EQUAL(0, followObj.getSize());
////
////	//insert a few pairs first
////	int result = followObj.insertFollows(1, 2);
////	int result1 = followObj.insertFollows(2, 3);
////	int result2 = followObj.insertFollows(5, 6);
////
////	
////	// verify - Note 7
////	CPPUNIT_ASSERT_EQUAL(3, followObj.getSize());
////
////
////
////	return;
////}
////
//void FollowTest::testgetFollowingStarStmt(){
//	
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 3);
//	int result2 = followObj.insertFollows(3, 9);
//	int result3 = followObj.insertFollows(9, 6);
//
//	std::vector<int> actual = followObj.getFollowingStarStmt(2);
//
//	//int myints[] = { 3, 9, 6 };
//	//std::vector<int> expected (myints, myints + sizeof(myints) / sizeof(int) );
//	//
//	//CPPUNIT_ASSERT_EQUAL(expected, actual);
//
//	std::cout<<"getFollowingStar";
//	
//	for(std::size_t i = 0; i < actual.size(); i++){
//		std::cout << actual[i] << std::endl;
//	}
//
//
//	return;
//}
//
//void FollowTest::testgetFollowedStarStmt(){
//	
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 4);
//	int result2 = followObj.insertFollows(4, 8);
//	int result3 = followObj.insertFollows(8, 10);
//
//	std::vector<int> actual = followObj.getFollowedStarStmt(10);
//
//	//int myints[] = { 3, 9, 6 };
//	//std::vector<int> expected (myints, myints + sizeof(myints) / sizeof(int) );
//	//
//	//CPPUNIT_ASSERT_EQUAL(expected, actual);
//
//	std::cout<<"getFollowedStar";
//	
//	for(std::size_t i = 0; i < actual.size(); i++){
//		std::cout << actual[i] << std::endl;
//	 }
//
//
//	return;
//}
//
//void FollowTest::testgetAllFollowingStmt(){
//	
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 6);
//	int result2 = followObj.insertFollows(4, 5);
//	int result3 = followObj.insertFollows(5, 8);
//
//	std::vector<int> actual = followObj.getAllFollowingStmt();
//
//	//int myints[] = { 3, 9, 6 };
//	//std::vector<int> expected (myints, myints + sizeof(myints) / sizeof(int) );
//	//
//	//CPPUNIT_ASSERT_EQUAL(expected, actual);
//
//	std::cout<<"getAllFollowing";
//	
//	for(std::size_t i = 0; i < actual.size(); i++){
//		std::cout << actual[i] << std::endl;
//	 }
//
//
//	return;
//}
//
//void FollowTest::testgetAllFollowedStmt(){
//	
//	Follow followObj;
//
//	//insert a few pairs first
//	int result = followObj.insertFollows(1, 2);
//	int result1 = followObj.insertFollows(2, 6);
//	int result2 = followObj.insertFollows(4, 5);
//	int result3 = followObj.insertFollows(5, 8);
//
//	std::vector<int> actual = followObj.getAllFollowedStmt();
//
//	//int myints[] = { 3, 9, 6 };
//	//std::vector<int> expected (myints, myints + sizeof(myints) / sizeof(int) );
//	//
//	//CPPUNIT_ASSERT_EQUAL(expected, actual);
//
//	std::cout<<"getAllFollowed";
//	
//	for(std::size_t i = 0; i < actual.size(); i++){
//		std::cout << actual[i] << std::endl;
//	 }
//
//
//	return;
//}
//
//		
//		
//
