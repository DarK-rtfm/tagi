#include<cppunit/extensions/HelperMacros.h>
#include "../src/include/ip.hh"

using namespace CppUnit;

class IPv4T : public TestFixture {
    CPPUNIT_TEST_SUITE(IPv4T);
    CPPUNIT_TEST(createString);
    CPPUNIT_TEST(createInt);
    CPPUNIT_TEST_SUITE_END();

    void createString(){
        ip::addr4 ip = ip::addr4("192.168.10.1");
        CPPUNIT_ASSERT_EQUAL(3232238081, (long)ip.value);
        CPPUNIT_ASSERT_EQUAL(std::string("192.168.10.1"), ip.strDD());
        std::stringstream stream;
        stream << std::hex << 3232238081;
        CPPUNIT_ASSERT_EQUAL("0x"+stream.str(), ip.strHEX());        
    }

    void createInt(){
        ip::addr4 ip = ip::addr4(0);
        CPPUNIT_ASSERT_EQUAL((uint32_t)0,ip.value);
        CPPUNIT_ASSERT_EQUAL(std::string("0.0.0.0"), ip.strDD());
        CPPUNIT_ASSERT_EQUAL(std::string("0x0"), ip.strHEX());
    }
    //TODO:More tests? (balint)
};

CPPUNIT_TEST_SUITE_REGISTRATION(IPv4T);
