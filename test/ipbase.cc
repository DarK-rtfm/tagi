#include <cppunit/extensions/HelperMacros.h>
#include "ip/base/ip_t.hpp"
#include "exceptions.hh"

using namespace CppUnit;

class IPbaseT : public TestFixture
{
    CPPUNIT_TEST_SUITE(IPbaseT);
    CPPUNIT_TEST(toString);
    CPPUNIT_TEST(constructor_string);
    CPPUNIT_TEST(operator_compares);
    CPPUNIT_TEST(operator_plus_int);
    CPPUNIT_TEST_SUITE_END();

    void toString()
    {
        IP::IP ip(3232235776);
        CPPUNIT_ASSERT_THROW(ip.toString(), E_NoSpec);
    }

    void constructor_string()
    {
        CPPUNIT_ASSERT_THROW(IP::IP<int>(std::string("192.168.1.0")), E_NoSpec);
    }

    void operator_compares()
    {
        IP::IP ip1(124);
        IP::IP ip2(464);
        IP::IP ip3(124);

        CPPUNIT_ASSERT(ip1 == ip1);
        CPPUNIT_ASSERT(ip2 == ip2);
        CPPUNIT_ASSERT(ip3 == ip3);
        CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT(ip1 == ip2));

        CPPUNIT_ASSERT(ip1 < ip2);
        CPPUNIT_ASSERT(ip2 > ip1);
    }

    void operator_plus_int()
    {
        IP::IP base(100);
        IP::IP added = base + 256;
        CPPUNIT_ASSERT_EQUAL(IP::IP(356).getValue(), added.getValue());
    }
    // TODO:More tests? (balint)
    //: NOTE: yes.
};

CPPUNIT_TEST_SUITE_REGISTRATION(IPbaseT);
