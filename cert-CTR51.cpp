//
// CTR51-CPP. Use valid references, pointers, and iterators to reference elements of a container
//

#include <algorithm>
#include <deque>
#include <iterator>

namespace {

void bad(const double* items, std::size_t count)
{
    std::deque<double> d;
    auto pos = d.begin();
    for (std::size_t i = 0; i < count; ++i, ++pos) {
        d.insert(pos, items[i] + 41.0); // undefined behavior!
    }
}

void foo(const double* items, std::size_t count)
{
    std::deque<double> d;
    auto pos = d.begin();
    for (std::size_t i = 0; i < count; ++i, ++pos) {
        pos = d.insert(pos, items[i] + 41.0);
    }
}

void bar(const double* items, std::size_t count)
{
    std::deque<double> d;
    std::transform(items, items + count, std::inserter(d, d.begin()),
                   [](double i) { return i + 41.0; });
}

} // namespace

int main()
{
    constexpr std::size_t SIZE = 3;
    double items[SIZE]{1.2, 1.2, 1.3};
    bad(items, SIZE);
    foo(items, SIZE);
    bar(items, SIZE);
}
