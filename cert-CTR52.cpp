//
// CTR52-CPP. Guarantee that library functions do not overflow
//

#include <algorithm>
#include <vector>

namespace {

void foo(const std::vector<int>& src)
{
    std::vector<int> dest;
    std::copy(src.begin(), src.end(), dest.begin()); // diagnostic required
    // ...
}

void good(const std::vector<int>& src)
{
    std::vector<int> dest;
    std::copy(src.begin(), src.end(), std::back_inserter(dest));
    // ...
}

void bar()
{
    std::vector<int> v;
    std::fill_n(v.begin(), 10, 0x42); // diagnostic required
}

void better()
{
    constexpr size_t SIZE = 10;
    std::vector<int> v(SIZE);
    std::fill_n(v.begin(), SIZE, 0x42);
}

void perfect(const std::vector<int>& src)
{
    std::vector<int> s(src);
    std::replace(s.begin(), s.end(), 8, 88);
    // ...
}

} // namespace

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
    foo(v);
    bar();
    good(v);
    better();
    perfect(v);
}
