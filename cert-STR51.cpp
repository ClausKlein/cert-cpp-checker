//
// STR51-CPP. Do not attempt to create a std::string from a null pointer
//

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

void bad()
{
    std::string tmp(std::getenv("TMP")); // diagnositc required
    if (!tmp.empty()) {
        // ...
    }
}

void good()
{
    const char* tmpPtrVal = std::getenv("TMPDIR");
    std::string tmp(tmpPtrVal != nullptr ? tmpPtrVal : "");
    if (!tmp.empty()) {
        std::cout << tmp << std::endl;
        // ...
    }
}

} // namespace

int main()
{
    good();
    bad();
}
