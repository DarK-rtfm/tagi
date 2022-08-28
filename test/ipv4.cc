#include <cppunit/extensions/HelperMacros.h>
#include "ip/v4/ip.hpp"
#include "exceptions.hh"

using namespace CppUnit;

class IPv4T : public TestFixture
{
    CPPUNIT_TEST_SUITE(IPv4T);
    CPPUNIT_TEST(toString);
    CPPUNIT_TEST(constructor_string);
    CPPUNIT_TEST_SUITE_END();

    void toString()
    {
        IP::IP4 ip(3232235776);
        CPPUNIT_ASSERT_EQUAL(std::string("192.168.1.0"), ip.toString());
        CPPUNIT_ASSERT_EQUAL(std::string("192.168.1.0"), ip.toString(IP::IP4_STR::DOTTED));
        CPPUNIT_ASSERT_EQUAL(std::string("3232235776"), ip.toString(IP::IP4_STR::DEC));
        CPPUNIT_ASSERT_EQUAL(std::string("0xc0a80100"), ip.toString(IP::IP4_STR::HEX));
        CPPUNIT_ASSERT_EQUAL(std::string("030052000400"), ip.toString(IP::IP4_STR::OCT));
        CPPUNIT_ASSERT_EQUAL(std::string("192.168.  1.  0"), ip.toString(IP::IP4_STR::DOTTED | IP::IP4_STR::PAD));
        CPPUNIT_ASSERT_EQUAL(std::string("192.168.001.000"), ip.toString(IP::IP4_STR::DOTTED | IP::IP4_STR::PAD | IP::IP4_STR::FILL0));
    }

    void constructor_string()
    {
        IP::IP4 ip("192.168.1.0");
        CPPUNIT_ASSERT_EQUAL(ip.toString(), std::string("192.168.1.0"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(IPv4T);
