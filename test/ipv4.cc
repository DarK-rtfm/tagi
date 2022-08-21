#include <cppunit/extensions/HelperMacros.h>
#include "../src/include/ip.hh"

using namespace CppUnit;

class IPv4T : public TestFixture
{
    CPPUNIT_TEST_SUITE(IPv4T);
    CPPUNIT_TEST(constructor_string);
    CPPUNIT_TEST(constructor_int);
    CPPUNIT_TEST(constructor_parts);
    CPPUNIT_TEST(method_toString);
    CPPUNIT_TEST(operator_equals);
    CPPUNIT_TEST(operator_plus_int);
    CPPUNIT_TEST_SUITE_END();

    void constructor_string()
    {
        ip::addr4 ip("192.168.10.1");
        CPPUNIT_ASSERT_EQUAL((uint32_t)3232238081, ip.toUInt32());
    }

    void constructor_int()
    {
        ip::addr4 ip(1234);
        CPPUNIT_ASSERT_EQUAL((uint32_t)1234, ip.toUInt32());
    }

    void constructor_parts()
    {
        ip::addr4 ip(192, 168, 10, 1);
        CPPUNIT_ASSERT_EQUAL((uint32_t)3232238081, ip.toUInt32());
    }

    void method_toString()
    {
        std::string fromString("123.111.222.69");
        ip::addr4 ip(fromString);
        CPPUNIT_ASSERT_EQUAL(fromString, ip.toString());
    }

    void operator_equals()
    {
        ip::addr4 ip1(124);
        ip::addr4 ip2(464);
        ip::addr4 ip3(124);

        CPPUNIT_ASSERT(ip1 == ip1);
        CPPUNIT_ASSERT(ip2 == ip2);
        CPPUNIT_ASSERT(ip3 == ip3);
        CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT(ip1 == ip2));
    }

    void operator_plus_int()
    {
        ip::addr4 base("10.0.0.0");
        ip::addr4 added = base + 256;
        CPPUNIT_ASSERT_EQUAL(ip::addr4("10.0.1.0").toUInt32(), added.toUInt32());
    }
    // TODO:More tests? (balint)
    //: NOTE: yes.
};

CPPUNIT_TEST_SUITE_REGISTRATION(IPv4T);
