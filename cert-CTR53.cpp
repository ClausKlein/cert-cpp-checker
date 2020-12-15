//
// CTR53-CPP. Use valid iterator ranges
//

#include <algorithm>
#include <iostream>
#include <vector>

namespace {

void bar(const std::vector<int>& c)
{
    std::for_each(c.end(), c.begin(), [](int i) { std::cout << i; }); // undefined behavior!
}

void foo(const std::vector<int>& c)
{
    std::vector<int>::const_iterator e; // undefined behavior!
    std::for_each(c.begin(), e, [](int i) { std::cout << i << ", "; });
}

void right(const std::vector<int>& c)
{
    std::for_each(c.begin(), c.end(), [](int i) { std::cout << i << ", "; });
}

} // namespace

int main()
{
    std::vector<int> c(7);
    foo(c);
    bar(c);
    right(c);
}
