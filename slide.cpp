#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <span>
#include <string>

// The example uses std::span to implement some algorithms on contiguous ranges.

template <class T, std::size_t N>
[[nodiscard]] constexpr auto slide(std::span<T, N> s, std::size_t offset, std::size_t width)
{
    return s.subspan(offset, offset + width <= s.size() ? width : 0U);
}

void print(const auto& seq)
{
    for (const auto& elem : seq) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void test()
{
    constexpr int a[]{0, 1, 2, 3, 4, 5, 6, 7, 8};
    // unused constexpr int b[] { 8, 7, 6 };

    for (std::size_t offset{};; ++offset) {
        constexpr std::size_t width{6};
        auto s = slide(std::span{a}, offset, width);
        if (s.empty()) {
            break;
        }
        print(s);
    }
}

int main()
{
    // construction uses aggregate initialization
    std::array<int, 3> a1{{1, 2, 3}}; // double-braces required in C++11 prior to
                                      // the CWG 1270 revision (not needed in C++11
                                      // after the revision and in C++14 and beyond)

    std::array<int, 3> a2 = {1, 2, 3}; // double braces never required after =

    std::array<std::string, 2> a3 = {std::string("a"), "b"};

    // container operations are supported
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';

    // ranged for loop is supported
    for (const auto& s : a3) {
        std::cout << s << ' ';
    }

    // deduction guide for array creation (since C++17)
    std::array a4{3.0, 1.0, 4.0}; // -> std::array<double, 3>
    print(a4);
}
