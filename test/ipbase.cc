#include "exceptions.hh"
#include "ip/v4/ip.hpp"
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class IPbaseT : public TestFixture {
  CPPUNIT_TEST_SUITE(IPbaseT);
  CPPUNIT_TEST(operator_compares);
  CPPUNIT_TEST(operator_plus_int);
  CPPUNIT_TEST_SUITE_END();

  void operator_compares() {
    IP::IP4 ip1(124);
    IP::IP4 ip2(464);
    IP::IP4 ip3(124);

    CPPUNIT_ASSERT(ip1 == ip1);
    CPPUNIT_ASSERT(ip2 == ip2);
    CPPUNIT_ASSERT(ip3 == ip3);
    CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT(ip1 == ip2));

    CPPUNIT_ASSERT(ip1 < ip2);
    CPPUNIT_ASSERT(ip2 > ip1);
  }

  void operator_plus_int() {
    IP::IP4 base(100);
    IP::IP4 added = base + (uint32_t)256;
    CPPUNIT_ASSERT_EQUAL(IP::IP4(356).getValue(), added.getValue());
  }
  // TODO:More tests? (balint)
  //: NOTE: yes.
};

CPPUNIT_TEST_SUITE_REGISTRATION(IPbaseT);
