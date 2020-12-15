//
// CTR55-CPP. Do not use an additive operator on an iterator if the result would overflow
//

#include <algorithm>
#include <iostream>
#include <vector>

namespace {

void bad(const std::vector<int>& c)
{
    constexpr size_t maxSize = 20;
    for (auto i = c.begin(), e = i + maxSize; i != e; ++i) {
        std::cout << *i << ", "; // diagnostic required
    }
    std::cout << std::endl;
}

void good(const std::vector<int>& c)
{
    constexpr std::vector<int>::size_type maxSize = 20;
    for (auto i = c.begin(), e = i + std::min(maxSize, c.size()); i != e; ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl;
}

void perfect(const std::vector<int>& c)
{
    for (const auto& i : c) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

} // namespace

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    bad(v);
    good(v);
    perfect(v);
}
