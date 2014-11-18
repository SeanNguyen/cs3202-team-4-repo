#include "TestAffects.h"
#include "PKB.h"

TestAffects::TestAffects(void)
{
}


TestAffects::~TestAffects(void)
{
}

void TestAffects::setUp() {
}

void TestAffects::tearDown() {

}

CPPUNIT_TEST_SUITE_REGISTRATION( TestAffects );

void TestAffects::TestisAffect() {

	PKB pkb;

	//bool insert1 = pkb.inserNext(1, 2);
	//bool insert2 = pkb.inserNext(2, 3); //branch
	//bool insert3 = pkb.inserNext(2, 4);
	//bool insert4 = pkb.inserNext(3, 6);
	//bool insert5 = pkb.inserNext(4, 5);
	//bool insert6 = pkb.inserNext(6, 7);//join branch
	//bool insert7 = pkb.inserNext(5, 7);

	//test for isAffects (1, 4)
	bool insertMod1 = pkb.insertModifies(1, 2);
	bool insertUse1 = pkb.insertUses(4, 2);

	//test for isAffects (2, 5)
	insertMod1 = pkb.insertModifies(2, 2);
	insertUse1 = pkb.insertUses(5, 2);

	CPPUNIT_ASSERT(pkb.isAffect(1, 4));
	CPPUNIT_ASSERT(pkb.isAffect(2, 5));

}

void TestAffects::TestIsAffectStar() {

}

void TestAffects::TestgetAffected() {
	PKB pkb;

	//bool insert1 = pkb.inserNext(1, 2);
	//bool insert2 = pkb.inserNext(2, 3); //branch
	//bool insert3 = pkb.inserNext(2, 4);
	//bool insert4 = pkb.inserNext(3, 6);
	//bool insert5 = pkb.inserNext(4, 5);
	//bool insert6 = pkb.inserNext(6, 7);//join branch
	//bool insert7 = pkb.inserNext(5, 7);

	//test for isAffects (1, 4)
	bool insertMod1 = pkb.insertModifies(1, 2);
	bool insertUse1 = pkb.insertUses(4, 2);

	//test for isAffects (2, 5)
	insertMod1 = pkb.insertModifies(2, 2);
	insertUse1 = pkb.insertUses(5, 2);

	CPPUNIT_ASSERT(pkb.getAffected(1).empty());
	CPPUNIT_ASSERT(pkb.getAffected(2).empty());
}

void TestAffects::TestgetAffecting() {
	PKB pkb;

	//bool insert1 = pkb.inserNext(1, 2);
	//bool insert2 = pkb.inserNext(2, 3); //branch
	//bool insert3 = pkb.inserNext(2, 4);
	//bool insert4 = pkb.inserNext(3, 6);
	//bool insert5 = pkb.inserNext(4, 5);
	//bool insert6 = pkb.inserNext(6, 7);//join branch
	//bool insert7 = pkb.inserNext(5, 7);

	//test for isAffects (1, 4)
	bool insertMod1 = pkb.insertModifies(1, 2);
	bool insertUse1 = pkb.insertUses(4, 2);

	//test for isAffects (2, 5)
	insertMod1 = pkb.insertModifies(2, 2);
	insertUse1 = pkb.insertUses(5, 2);

	/*CPPUNIT_ASSERT(pkb.getAffecting(4, 4, true).empty());
	CPPUNIT_ASSERT(pkb.getAffecting(5, 5, true).empty());*/
}

void TestAffects::TestgetAffectingStar() {
	
}