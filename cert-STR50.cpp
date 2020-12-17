//
// STR50-CPP. Guarantee that storage for strings has sufficient space for character data and the null
// terminator
//

#include <iostream>
#include <sstream>
#include <string>

namespace {
void foo(std::istream& in)
{
    char buf[12];
    in >> buf; // diagnositc required
}

void bar(std::istream& in)
{
    constexpr size_t SIZE = 12;
    char bufOne[SIZE];
    char bufTwo[SIZE];
    in.width(SIZE); // NOTE: should be (SIZE-1)! CK
    in >> bufOne;   // diagnositc required
    in >> bufTwo;   // diagnositc required
}

void bad(std::istream& in)
{
    char buffer[32];
    try {
        in.read(buffer, sizeof(buffer)); // NOTE: should be (SIZE-1)! CK
    } catch (std::ios_base::failure& e) {
        // Handle error
    }

    std::string str(buffer); // diagnositc required
    // ...
    std::cout << str << std::endl;
}

} // namespace

int main()
{
    std::istringstream ss("1111111111111 2222222222222 3333333333333 4444444444444444444444444444444");
    foo(ss);
    bar(ss);
    bad(ss);
}
