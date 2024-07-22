#include <gtest/gtest.h>
#include <uuid.h>
#include <sstream>
#include <random>

TEST(UUID, UuidTest) {
    uuid_t dest;
    char uuidHex[48];
    uuid_generate(dest);
    uuid_unparse(dest, uuidHex);
    std::cout << dest << std::endl;
    std::cout << uuidHex << std::endl;
    std::string uuid(uuidHex);
    std::cout << uuid << std::endl;
}

TEST(UUID, UuidFileNameTest) {
    uuid_t dest;
    char uuidHex[48];
    uuid_generate(dest);
    uuid_unparse(dest, uuidHex);
    std::cout << dest << std::endl;
    std::cout << uuidHex << std::endl;
    std::string uuid(uuidHex);
    std::cout << uuid << std::endl;
    std::ostringstream os;
    os << ((char)(rand()%26 + 'a'));
    os << rand()%10;
    os << '/';
    os << uuid;
    std::cout << os.str()  << std::endl;
}


TEST(UUID, UuidFileNameSuffixTest) {
    std::string filename = "hello.txt";
    std::cout << filename.substr(filename.find_last_of('.')) << std::endl;
}