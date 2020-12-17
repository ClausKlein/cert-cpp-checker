//
// see https://en.wikipedia.org/wiki/Look-and-say_sequence
// and https://en.wikipedia.org/wiki/Modified_Huffman_coding
//
#include <iostream>
#include <sstream>
#include <string>

namespace {

/// To generate a member of the sequence from the previous member, read off the digits of the previous
/// member, counting the number of digits in groups of the same digit.
std::string lookAndSay(const std::string& s)
{
    std::ostringstream r;

    for (std::size_t i = 0; i != s.length();) {
        auto new_i = s.find_first_not_of(s[i], i + 1);

        if (new_i == std::string::npos) {
            new_i = s.length();
        }

        r << new_i - i << s[i];
        i = new_i;
    }
    return r.str();
}
} // namespace

int main()
{
    std::string laf = "1Qay:-)";

    std::cout << laf << '\n';
    for (int i = 0; i < 7; ++i) {
        laf = lookAndSay(laf);
        std::cout << laf << '\n';
    }
}
