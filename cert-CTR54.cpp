//
// CTR54-CPP. Do not subtract iterators that do not refer to the same container
//

#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>

namespace {

template <typename Ty> bool foo_in_range(const Ty* test, const Ty* r, size_t n)
{
    return 0 < (test - r) && (test - r) < static_cast<std::ptrdiff_t>(n); // undefined behavior
}

void foo()
{
    constexpr std::size_t SIZE = 10;
    double foo[SIZE]{};
    double* x = &foo[0];
    double value{};
    std::cout << std::boolalpha << foo_in_range(&value, x, SIZE) << std::endl;
}

// ===================================

template <typename Ty> bool bar_in_range(const Ty* test, const Ty* r, size_t n)
{
    // NOTE: cppcoreguidelines-pro-type-reinterpret-cast
    return test >= r && test < (r + n); // undefined behavior
}

void bar()
{
    constexpr std::size_t SIZE = 10;
    double foo[SIZE]{};
    double* x = &foo[0];
    double value{};
    std::cout << std::boolalpha << bar_in_range(&value, x, SIZE) << std::endl;
}

// ===================================

template <typename RandIter>
bool in_range_impl(RandIter test, RandIter r_begin, RandIter r_end,
                   std::random_access_iterator_tag /*unused*/)
{
    return test >= r_begin && test < r_end; // unspecified behavior
}

template <typename Iter> bool bad_in_range(Iter test, Iter r_begin, Iter r_end)
{
    typename std::iterator_traits<Iter>::iterator_category cat;
    return in_range_impl(test, r_begin, r_end, cat);
}

void bad()
{
    std::vector<double> foo(10);
    std::vector<double> value(1);
    std::cout << std::boolalpha << bad_in_range(value.begin(), foo.begin(), foo.end()) << std::endl;
}

// ===================================

template <typename Ty> bool fun_in_range(const Ty* test, const Ty* r, size_t n)
{
    std::less<const Ty*> less;
    // NOTE: cppcoreguidelines-pro-type-reinterpret-cast
    return !less(test, r) && less(test, r + n); // undefined behavior
}

void fun()
{
    constexpr std::size_t SIZE = 10;
    double foo[SIZE]{};
    double* x = &foo[0];
    double value{};
    std::cout << std::boolalpha << fun_in_range(&value, x, SIZE) << std::endl;
}

// ===================================

// This compliant solution demonstrates a fully portable, but likely inefficient, implementation of
// in_range() that compares test against each possible address in the range [r, n].
// TODO: A compliant solution that is both efficient and fully portable is currently unknown.
template <typename Ty> bool hack_in_range(const Ty* test, const Ty* r, size_t n)
{
    // NOTE: cppcoreguidelines-pro-type-reinterpret-cast
    const auto* cur = reinterpret_cast<const unsigned char*>(r);
    const auto* end = reinterpret_cast<const unsigned char*>(r + n);
    const auto* testPtr = reinterpret_cast<const unsigned char*>(test);

    for (; cur != end; ++cur) { // NOTE: cppcoreguidelines-pro-bounds-pointer-arithmetic
        if (cur == testPtr) {
            return true;
        }
    }
    return false;
}

int hack()
{
    constexpr std::size_t SIZE = 10;
    double foo[SIZE]{};
    double* x = &foo[0];
    double value{};
    auto result = hack_in_range(&value, x, SIZE);
    std::cout << value << " found in: " << std::boolalpha << result << std::endl;
    for (const auto& e : foo) {
        std::cout << e << ", " << std::endl;
    }

    return result;
}

} // namespace

int main()
{
    fun();
    foo();
    bar();
    bad();

    int OK = hack();
    return !OK;
}
