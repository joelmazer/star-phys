// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJETTREEENTRYMAKERTEST_HH
#define STJETTREEENTRYMAKERTEST_HH

#include <cppunit/extensions/HelperMacros.h>

class StJetTreeEntryMakerTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( StJetTreeEntryMakerTest );
  CPPUNIT_TEST( testMake );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testMake();

private:

};

#endif // STJETTREEENTRYMAKERTEST_HH