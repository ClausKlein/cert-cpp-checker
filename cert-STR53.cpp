//
// STR53-CPP. Range check element access
//

#include <cstdlib>
#include <exception>
#include <locale>
#include <string>

namespace {

void bad()
{
    std::string s("01234567");
    s[rand()] = '1'; // undefined behavior!
}

void good()
{
    std::string s("01234567");
    try {
        s.at(rand()) = '1';
    } catch (std::out_of_range&) {
        // Handle error
    }
}

void capitalize(std::string& s)
{
    // TODO if (s.empty()) { return; }
    std::locale loc;
    s.front() = std::use_facet<std::ctype<char>>(loc).toupper(s.front()); // undefined behavior!
}

} // namespace

int main()
{
    std::string s;
    capitalize(s);
    good();
    bad();
}
