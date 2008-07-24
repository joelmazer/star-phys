// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJETTREEENTRYCOORDINATORTEST_HH
#define STJETTREEENTRYCOORDINATORTEST_HH

#include <cppunit/extensions/HelperMacros.h>

class StJetTreeEntryCoordinatorTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( StJetTreeEntryCoordinatorTest );
  CPPUNIT_TEST( testMake );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testMake();

private:

};

#endif // STJETTREEENTRYCOORDINATORTEST_HH